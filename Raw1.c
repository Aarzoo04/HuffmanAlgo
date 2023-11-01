#include <stdio.h>
#include <stdlib.h>

// Define the Node structure for the min-heap
struct Node {
    char character;
    int freq;
};

// Helper function to swap two Node elements in the min-heap
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

int main() {
    FILE *fP;
    unsigned int arr[58] = {0};
    fP = fopen("abc.txt", "r");
    char ch;

    // Create an array of Node structures to use as a min-heap
    struct Node min_heap[58];

    // Initialize the size of the min-heap
    int heap_size = 0;

    char alpha[58] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '.',' ', ',', '$', '!', '&', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    while (1) {
        ch = fgetc(fP);
        if (ch == EOF) {
            break;
        }

        // Check if the character is in the 'alpha' array
        int index = -1;
        for (int i = 0; i < 58; i++) {
            if (alpha[i] == ch) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            arr[index]++;
        } else {
            printf("\nNot a valid character:%c\n",ch);
        }
    }

    // Now, populate the min-heap with the character frequencies
    for (int i = 0; i < 58; i++) {
        if (arr[i] > 0) {
            struct Node new_node;
            new_node.character = alpha[i];
            new_node.freq = arr[i];
            insert(min_heap, &heap_size, new_node);
        }
    }

    // At this point, 'min_heap' contains the character frequencies as a min-heap

    printf("Character  |  Frequency\n");
    printf("***************************\n");
    for (int i = 0; i < heap_size; i++) {
        printf("%c   %14d\n", min_heap[i].character, min_heap[i].freq);
    }
    printf("\n");

    fclose(fP);
    return 0;
}
