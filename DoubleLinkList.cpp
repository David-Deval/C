#include<stdio.h>
#include<stdlib.h>

struct tnode {
    int x;
    struct tnode *next;
    struct tnode *prev;
} *head, *tail, *curr;

void push_front(int value) {
    struct tnode *node = (struct tnode*)malloc(sizeof(struct tnode));
    node->x = value;
    
    if (head == NULL) {
        head = tail = node;
        node->next = node->prev = NULL;
    } else {
        node->next = head;
        head->prev = node;
        head = node;
        head->prev = NULL;
    }
}

void push_back(int value) {
    struct tnode *node = (struct tnode*)malloc(sizeof(struct tnode));
    node->x = value;
    
    if (head == NULL) {
        head = tail = node;
        node->next = node->prev = NULL;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
        tail->next = NULL;
    }
}

void push_mid(int value, int searchKey) {
    struct tnode *node = (struct tnode*)malloc(sizeof(struct tnode));
    node->x = value;
    
    if (head == NULL) {
        head = tail = node;
        node->next = node->prev = NULL;
    } else {
        struct tnode *curr = head;
        while (curr != NULL) {
            if (curr->x == searchKey) {
                if (curr == tail) {
                    push_back(value);
                } else {
                    node->next = curr->next;
                    node->prev = curr;
                    curr->next->prev = node;
                    curr->next = node;
                }
                return;
            }
            curr = curr->next;
        }
        printf("Data %d is not found\n", searchKey);
        free(node);
    }
}

void delete_front() {
    if (head == NULL) {
        printf("There is no data\n");
    } else {
        struct tnode *del = head;
        if (head == tail) {
            head = tail = NULL;
        } else {
            head = head->next;
            head->prev = NULL;
        }
        free(del);
    }
}

void delete_back() {
    if (head == NULL) {
        printf("There is no data\n");
    } else {
        struct tnode *del = tail;
        if (head == tail) {
            head = tail = NULL;
        } else {
            tail = tail->prev;
            tail->next = NULL;
        }
        free(del);
    }
}

void delete_mid(int searchKey) {
    if (head == NULL) {
        printf("There is no data\n");
        return;
    }
    
    struct tnode *curr = head;
    while (curr != NULL) {
        if (curr->x == searchKey) {
            if (curr == head) {
                delete_front();
            } else if (curr == tail) {
                delete_back();
            } else {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                free(curr);
            }
            return;
        }
        curr = curr->next;
    }
    printf("Data %d is not found\n", searchKey);
}

void printList() {
    curr = head;
    while (curr != NULL) {
        printf("%d ", curr->x);
        curr = curr->next;
    }
    printf("\n");
}

int main() {
    printf("Linked List\n");
    
    push_front(76);
    push_front(90);
    push_front(45);
    push_back(20);
    push_back(12);
    push_mid(33, 90);
    printList();
    
    delete_back();
    printList();
    
    delete_front();
    printList();
    
    delete_mid(33);
    printList();
    
    return 0;
}

