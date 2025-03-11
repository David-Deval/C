#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 26 // Sesuai jumlah alfabet

struct node {
    char data[100];
    struct node *next;
} *hashTable[TABLE_SIZE], *curr;

int collisionHandlingType;

int getHashKey(char data[]) {
    char firstChar = tolower(data[0]); // Ambil huruf pertama, abaikan case-sensitive
    if (firstChar < 'a' || firstChar > 'z') return -1; // Jika bukan huruf, abaikan
    return firstChar - 'a'; // Index 0 untuk 'a', 1 untuk 'b', dst.
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
        printf("Hash Table Index [%c]: ", 'a' + i);
        curr = hashTable[i];
        while (curr != NULL) {
            printf("%s -> ", curr->data);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}

int main() {
    printf("Pilih Collision Handling:\n");
    printf("1. Linear Probing\n2. Chaining\n");
    printf("Masukkan pilihan: ");
    scanf("%d", &collisionHandlingType);
    
    char data[100];
    while (1) {
        printf("Input Data (ketik 'exit' untuk keluar): ");
        scanf("%s", data);
        if (strcmp(data, "exit") == 0) break;
        int hashKey = getHashKey(data);
        if (hashKey == -1) {
            printf("Data hanya boleh diawali huruf!\n");
            continue;
        }
        insertData(hashKey, data);
    }
    
    viewHashTable();
    return 0;
}

