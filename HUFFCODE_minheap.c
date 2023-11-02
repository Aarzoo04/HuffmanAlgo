#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Node structure for the min-heap
struct Node {
    char character;
    int freq;
    struct Node *left;
    struct Node *right;
};

// Function to SWAP two Node elements in the min-heap
void swap(struct Node *x, struct Node *y) {
    struct Node temp = *y;
    *y = *x;
    *x = temp;
}

// Min-heapify function to maintain the min-heap property
void min_heapify(struct Node arr[], int size, int i) {
    int smallest = i;
    int leftchild = 2 * i + 1;
    int rightchild = 2 * i + 2;

    if (leftchild < size && arr[leftchild].freq < arr[smallest].freq) {
        smallest = leftchild;
    }

    if (rightchild < size && arr[rightchild].freq < arr[smallest].freq) {
        smallest = rightchild;
    }

    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        min_heapify(arr, size, smallest);
    }
}

// Function to insert a Node into the min-heap
void insert(struct Node arr[], int *size, struct Node new_node) {
    int i = *size;
    *size = *size + 1;
    arr[i] = new_node;

    while (i > 0 && arr[(i - 1) / 2].freq > arr[i].freq) {
        swap(&arr[i], &arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Function to build the Huffman tree
struct Node buildHuffmanTree(struct Node arr[], int size) {
    while (size > 1) {
        struct Node left = arr[0];
        arr[0] = arr[size - 1];
        size--;
        min_heapify(arr, size, 0);

        struct Node right = arr[0];
        arr[0] = arr[size - 1];
        size--;
        min_heapify(arr, size, 0);

        struct Node newNode;
        newNode.character = '$'; // Internal node marker
        newNode.freq = left.freq + right.freq;
        newNode.left = malloc(sizeof(struct Node));
        *newNode.left = left;
        newNode.right = malloc(sizeof(struct Node));
        *newNode.right = right;

        insert(arr, &size, newNode);
    }

    return arr[0];
}

// Function to print the Huffman tree
void printHuffmanTree(struct Node *root, int level) {
    if (root) {
        printHuffmanTree(root->right, level + 1);
        for (int i = 0; i < level; i++) {
            printf("    ");
        }
        if (root->character == '$') {
            printf("[$%d]\n", root->freq);
        } else {
            printf("%c [%d]\n", root->character, root->freq);
        }
        printHuffmanTree(root->left, level + 1);
    }
}

// Function to generate Huffman codes
void generateHuffmanCodes(struct Node *root, int code[], int top) {
    if (root->left) {
        code[top] = 0;
        generateHuffmanCodes(root->left, code, top + 1);
    }
    if (root->right) {
        code[top] = 1;
        generateHuffmanCodes(root->right, code, top + 1);
    }
    if (!root->left && !root->right) {
        printf("%c: ", root->character);
        for (int i = 0; i < top; i++) {
            printf("%d", code[i]);
        }
        printf("\n");
    }
}

int main() {
    FILE *fP;
    unsigned int arr[128] = {0};
    fP = fopen("abc.txt", "r");
    char ch;

    struct Node min_heap[128];
    int heap_size = 0;

    while (1) {
        ch = fgetc(fP);
        if (ch == EOF) {
            break;
        }

        arr[ch]++;
    }

    for (int i = 0; i < 128; i++) {
        if (arr[i] > 0) {
            struct Node new_node;
            new_node.character = (char)i;
            new_node.freq = arr[i];
            new_node.left = NULL;
            new_node.right = NULL;
            insert(min_heap, &heap_size, new_node);
        }
    }

    printf("Character  |  Frequency\n");
    printf("***************************\n");
    for (int i = 0; i < heap_size; i++) {
        printf("%c   %14d\n", min_heap[i].character, min_heap[i].freq);
    }

    // Build Huffman Tree
    struct Node root = buildHuffmanTree(min_heap, heap_size);

    printf("\nHuffman Tree Visualization:\n");
    printHuffmanTree(&root, 0);

    int code[128];
    printf("\nHuffman Codes:\n");
    generateHuffmanCodes(&root, code, 0);

    fclose(fP);

    return 0;
}
