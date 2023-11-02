#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a Huffman node
typedef struct HuffNode {
    char data;
    int frequency;
    struct HuffNode *left;
    struct HuffNode *right;
} HuffNode;

HuffNode *createHuffNode(char data, int frequency) {
    HuffNode *node = (HuffNode *)malloc(sizeof(HuffNode));
    if (node) {
        node->data = data;
        node->frequency = frequency;
        node->left = node->right = NULL;
    }
    return node;
}

HuffNode *buildHuffmanTree(char data[], int frequency[], int n) {
    HuffNode *nodes[n];
    for (int i = 0; i < n; i++) {
        nodes[i] = createHuffNode(data[i], frequency[i]);
    }

    while (n > 1) {
        int min1 = 0, min2 = 1;
        if (nodes[min1]->frequency > nodes[min2]->frequency) {
            int temp = min1;
            min1 = min2;
            min2 = temp;
        }

        for (int i = 2; i < n; i++) {
            if (nodes[i]->frequency < nodes[min1]->frequency) {
                min2 = min1;
                min1 = i;
            } else if (nodes[i]->frequency < nodes[min2]->frequency) {
                min2 = i;
            }
        }

        HuffNode *newNode = createHuffNode('$', nodes[min1]->frequency + nodes[min2]->frequency);
        newNode->left = nodes[min1];
        newNode->right = nodes[min2];

        nodes[min1] = newNode;

        for (int i = min2 + 1; i < n; i++) {
            nodes[i - 1] = nodes[i];
        }

        n--;
    }

    return nodes[0]; // The root of the Huffman tree
}

void printHuffmanTree(HuffNode *root, int level) {
    if (root) {
        printHuffmanTree(root->right, level + 1);
        for (int i = 0; i < level; i++) {
            printf("    ");
        }
        if (root->data == '$') {
            printf("[$%d]\n", root->frequency);
        } else {
            printf("%c [%d]\n", root->data, root->frequency);
        }
        printHuffmanTree(root->left, level + 1);
    }
}

void assignHuffmanCodes(HuffNode *root, char code[], int top) {
    static char huffmanCodes[256][100]; // Assuming 256 ASCII characters and a maximum code length of 100
    if (root->left) {
        code[top] = '0';
        assignHuffmanCodes(root->left, code, top + 1);
    }
    if (root->right) {
        code[top] = '1';
        assignHuffmanCodes(root->right, code, top + 1);
    }
    if (root->data != '$') {
        code[top] = '\0';
        strcpy(huffmanCodes[(int)(root->data)], code);
        printf("%c: %s\n", root->data, code);
    }
}

int main() {
    char data[] = { 'a', 'b', 'c', 'd' };
    int frequency[] = { 5, 1, 6, 3 };
    int n = sizeof(data) / sizeof(data[0]);

    HuffNode *root = buildHuffmanTree(data, frequency, n);

    printf("Huffman Tree Visualization:\n");
    printHuffmanTree(root, 0);

    char code[100];
    printf("\nHuffman Codes:\n");
    assignHuffmanCodes(root, code, 0);

    return 0;
}
