#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

#define MAX 16
#define MAX_BUFFER_SIZE 1024

// Structure for tree nodes
struct Node
{
    char character;
    int freq;
    struct Node *l, *r;
};

// Structure for min heap
struct Min_Heap
{
    int size;
    struct Node **array;
};

// Structure to store codes in compressed file
typedef struct code
{
    char k;
    int l;
    int code_arr[MAX];
    struct code *p;
} code;

// Structure for Huffman tree
typedef struct Tree
{
    char g;
    int len;
    int dec;
    struct Tree *f;
    struct Tree *r;
} Tree;

// Global variables for the linked list of codes
code *front, *rear;

// Global variable for the Huffman tree
struct Tree *tree, *t, *tree_temp;

// Function to create new node
struct Node *newNode(char character, int freq)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->character = character;
    temp->freq = freq;
    temp->l = temp->r = NULL;
    return temp;
}
// Function to heapify a subtree rooted with a given node
void heapify(struct Min_Heap *minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx)
    {
        struct Node *temp = minHeap->array[idx];
        minHeap->array[idx] = minHeap->array[smallest];
        minHeap->array[smallest] = temp;

        heapify(minHeap, smallest);
    }
}

// Function to create min heap
struct Min_Heap *createAndBuildMin_Heap(char arr[], int freq[], int unique_size)
{
    int i;

    // Initializing heap
    struct Min_Heap *minHeap = (struct Min_Heap *)malloc(sizeof(struct Min_Heap));
    minHeap->size = unique_size;
    minHeap->array = (struct Node **)malloc(minHeap->size * sizeof(struct Node *));

    // Initializing the array of pointers in the min heap.
    // Pointers pointing to new nodes of character and their frequency
    for (i = 0; i < unique_size; ++i)
    {
        minHeap->array[i] = newNode(arr[i], freq[i]);
    }

    int n = minHeap->size - 1;
    for (i = (n - 1) / 2; i >= 0; --i)
    {
        heapify(minHeap, i);
    }

    return minHeap;
}


// Function to check if the size of the min heap is 1
int isSizeOne(struct Min_Heap *minHeap)
{
    return (minHeap->size == 1);
}

// Function to extract the minimum value node from the min heap
struct Node *extractMin(struct Min_Heap *minHeap)
{
    struct Node *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    heapify(minHeap, 0);
    return temp;
}

// Function to insert a new node into the min heap
void insertIntoMin_Heap(struct Min_Heap *minHeap, struct Node *node)
{
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i > 0 && node->freq < minHeap->array[(i - 1) / 2]->freq)
    {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = node;
}

// Function to build Huffman Tree
struct Node *buildHuffmanTree(struct Min_Heap *Min_Heap)
{
    struct Node *l, *r, *top;
    while (!isSizeOne(Min_Heap))
    {
        l = extractMin(Min_Heap);
        r = extractMin(Min_Heap);
        top = newNode('$', l->freq + r->freq);
        top->l = l;
        top->r = r;
        insertIntoMin_Heap(Min_Heap, top);
    }
    return extractMin(Min_Heap);
}

// Function to convert decimal to binary
void convertDecimalToBinary(int bin[], int n, int len)
{
    for (int i = len - 1; i >= 0; i--)
    {
        bin[i] = n % 2;
        n /= 2;
    }
}

// Function to convert binary to decimal
int convertBinaryToDecimal(int bin[], int len)
{
    int decimal = 0;
    for (int i = 0; i < len; i++)
    {
        decimal = decimal * 2 + bin[i];
    }
    return decimal;
}

// Function to check if a node is a leaf
int isLeaf(struct Node *node)
{
    return !(node->l) && !(node->r);
}

// Function to print codes into file
void printCodesIntoFile(int fd2, struct Node *root, int t[], int top)
{
    int i;
    if (root->l)
    {
        t[top] = 0;
        printCodesIntoFile(fd2, root->l, t, top + 1);
    }

    if (root->r)
    {
        t[top] = 1;
        printCodesIntoFile(fd2, root->r, t, top + 1);
    }

    if (isLeaf(root))
    {
        code *data = (code *)malloc(sizeof(code));
        Tree *tree = (Tree *)malloc(sizeof(Tree));
        data->p = NULL;
        data->k = root->character;
        write(fd2, &tree->g, sizeof(char));
        for (i = 0; i < top; i++)
        {
            data->code_arr[i] = t[i];
        }
        tree->len = top;
        write(fd2, &tree->len, sizeof(int));
        tree->dec = convertBinaryToDecimal(data->code_arr, top);
        write(fd2, &tree->dec, sizeof(int));
        data->l = top;
        data->p = NULL;
        if (!front)
        {
            front = rear = data;
        }
        else
        {
            rear->p = data;
            rear = rear->p;
        }
    }
}

// Function to compress file
void compressFile(int fd1, int fd2, unsigned char a)
{
    char n;
    int h = 0, i;

    // Codes are written into the file in bit by bit format
    while (read(fd1, &n, sizeof(char)) != 0)
    {
        rear = front;
        while (rear->k != n && rear->p != NULL)
        {
            rear = rear->p;
        }
        if (rear->k == n)
        {
            for (i = 0; i < rear->l; i++)
            {
                if (h < 7)
                {
                    if (rear->code_arr[i] == 1)
                    {
                        a++;
                        a = a << 1;
                        h++;
                    }
                    else if (rear->code_arr[i] == 0)
                    {
                        a = a << 1;
                        h++;
                    }
                }
                else if (h == 7)
                {
                    if (rear->code_arr[i] == 1)
                    {
                        a++;
                        h = 0;
                    }
                    else
                    {
                        h = 0;
                    }
                    write(fd2, &a, sizeof(char));
                    a = 0;
                }
            }
        }
    }
    for (i = 0; i < 7 - h; i++)
    {
        a = a << 1;
    }
    write(fd2, &a, sizeof(char));
}

int calculateUniqueSize(int fd1) {
    int char_count[256] = {0};  // Assuming ASCII characters, adjust for other character sets
    char buffer[MAX_BUFFER_SIZE];
    ssize_t bytesRead;

    lseek(fd1, 0, SEEK_SET);  // Move the file pointer to the beginning

    // Read the file and count unique characters
    while ((bytesRead = read(fd1, buffer, MAX_BUFFER_SIZE)) > 0) {
        for (ssize_t i = 0; i < bytesRead; i++) {
            char_count[(unsigned char)buffer[i]] = 1;
        }
    }

    int unique_size = 0;
    for (int i = 0; i < 256; i++) {
        if (char_count[i] > 0) {
            unique_size++;
        }
    }

    return unique_size;
}


int main()
{
    // Open input file in read only mode
    int fd1 = open("sample.txt", O_RDONLY);
    if (fd1 == -1)
    {
        perror("Open failed");
        exit(1);
    }

    int fd2 = open("compressed.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd2 == -1)
    {
        perror("Open Failed");
        exit(1);
    }

    // You need to define and initialize arr and freq arrays for the characters and their frequencies
    int unique_size = calculateUniqueSize(fd1);

    // Now you can use unique_size in your code
    printf("Unique size: %d\n", unique_size);

    char arr[unique_size]; // Replace with your array of characters
    int freq[unique_size]; // Replace with your array of frequencies

    struct Min_Heap *minHeap = createAndBuildMin_Heap(arr, freq, unique_size);

    struct Node *root = buildHuffmanTree(minHeap);

    // Print Huffman codes into the file
    int t[MAX];
    printCodesIntoFile(fd2, root, t, 0);

    // Reset the file pointer to the beginning of the compressed file
    lseek(fd1, 0, SEEK_SET);

    // Compress the file and write the compressed data into the output file
    unsigned char a = 0; // Bitwise operations will be performed on this variable
    compressFile(fd1, fd2, a); 

    // Close file descriptors
    close(fd1);
    close(fd2);
    

    return 0;
}
