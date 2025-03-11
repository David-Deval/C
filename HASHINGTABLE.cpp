#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 10

struct node {
    char data[100];
    struct node *next;
} *hashTable[TABLE_SIZE], *curr;

int hashFunctionType;
int collisionHandlingType;

// Hash Functions
int midSquareHash(int key) {
    key = key * key;
    return (key / 100) % TABLE_SIZE;
}

int divHash(int key) {
    return key % TABLE_SIZE;
}

int foldingHash(int key) {
    int part1 = key / 1000;
    int part2 = key % 1000;
    return (part1 + part2) % TABLE_SIZE;
}

int digitExtractionHash(int key) {
    return (key / 10) % TABLE_SIZE;
}

int rotationHash(int key) {
    int lastDigit = key % 10;
    key = (key / 10) + (lastDigit * 10000);
    return key % TABLE_SIZE;
}

int hashFunction(char data[]) {
    int key = 0;
    for (int i = 0; data[i] != '\0'; i++) {
        key += data[i];
    }
    
    switch (hashFunctionType) {
        case 1: return midSquareHash(key);
        case 2: return divHash(key);
        case 3: return foldingHash(key);
        case 4: return digitExtractionHash(key);
        case 5: return rotationHash(key);
        default: return divHash(key);
    }
}

void linearProbingInsert(int hashKey, char data[]);
void chainingInsert(int hashKey, char data[]);

void insertData(int hashKey, char data[]) {
    switch (collisionHandlingType) {
        case 1: linearProbingInsert(hashKey, data); break;
        case 2: chainingInsert(hashKey, data); break;
        default: chainingInsert(hashKey, data);
    }
}

void linearProbingInsert(int hashKey, char data[]) {
    int originalKey = hashKey;
    while (hashTable[hashKey] != NULL) {
        hashKey = (hashKey + 1) % TABLE_SIZE;
        if (hashKey == originalKey) {
            printf("Table is full!\n");
            return;
        }
    }
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    strcpy(newNode->data, data);
    newNode->next = NULL;
    hashTable[hashKey] = newNode;
}

void chainingInsert(int hashKey, char data[]) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    strcpy(newNode->data, data);
    newNode->next = hashTable[hashKey];
    hashTable[hashKey] = newNode;
}

void viewHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Hash Table Index [%d]: ", i);
        curr = hashTable[i];
        while (curr != NULL) {
            printf("%s -> ", curr->data);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}

int main() {
    printf("Pilih Hash Function:\n");
    printf("1. Mid-Square\n2. Division\n3. Folding\n4. Digit Extraction\n5. Rotation\n");
    printf("Masukkan pilihan: ");
    scanf("%d", &hashFunctionType);
    
    printf("Pilih Collision Handling:\n");
    printf("1. Linear Probing\n2. Chaining\n");
    printf("Masukkan pilihan: ");
    scanf("%d", &collisionHandlingType);
    
    char data[100];
    while (1) {
        printf("Input Data (ketik 'exit' untuk keluar): ");
        scanf("%s", data);
        if (strcmp(data, "exit") == 0) break;
        insertData(hashFunction(data), data);
    }
    
    viewHashTable();
    return 0;
}

