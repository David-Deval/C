#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode {
    int value;
    struct tnode *next;
    struct tnode *prev;
} *head = NULL, *tail = NULL;

struct tnode* createnode(int value) {
    struct tnode *newnode = (struct tnode*)malloc(sizeof(struct tnode));
    if (!newnode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newnode->value = value;
    newnode->next = NULL;
    newnode->prev = NULL;
    return newnode;
}

void push_front(int value) {
    struct tnode *node = createnode(value);
    
    if (head == NULL) {
        head = tail = node;
    } else {
        node->next = head;
        head->prev = node;
        head = node;
    }
}

void push_back(int value) {
    struct tnode *node = createnode(value);
    
    if (head == NULL) {
        head = tail = node;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
}

void push_mid(int value, int key) {
    struct tnode *node = createnode(value);

    if (head == NULL) {
        head = tail = node;
    } else {
        struct tnode *curr = head;
        while (curr != NULL && curr->value != key) {
            curr = curr->next;
        }
        if (curr != NULL) {
            if (curr == tail) {
                push_back(value);
            } else if (curr == head) {
                push_front(value);
            } else {
                node->next = curr->next;
                node->prev = curr;
                curr->next->prev = node;
                curr->next = node;
            }
        } else {
            printf("Key tidak ditemukan!\n");
        }
    }
}

void delete_front(){
	if(head == NULL){
		printf("Tidak ada data yg tersimpan\n");
	}else{
		struct tnode *del = head;
		if(head == tail){
			head = tail = NULL;
		}else{
		head = head->next;
		head->prev = NULL;
		}
		free(del);
	}
}

void delete_back(){
	if(head == NULL){
		printf("Data tidak ditemukan\n");
	}else{
		struct tnode *del = tail;
		if(tail == head){
			tail = head = NULL;
		}else{
			tail = tail->prev;
			tail->next = NULL; 
		}
		free(del);
	}
}

void delete_mid(int location){
	if(head == NULL){
		printf("Data tidak ada\n");
	}
	
	struct tnode *curr = head;
	while (curr != NULL) {
        if (curr->value == location) {
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
	}

void printlist() {
    struct tnode *curr = head;
    while (curr != NULL) {
		printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("\n");
}

void sort_list() {
    if (head == NULL) return; // List kosong atau hanya 1 elemen

    int swapped;
    struct tnode *curr;
    struct tnode *last = NULL;

    do {
        swapped = 0;
        curr = head;

        while (curr->next != last) {
            if (curr->value > curr->next->value) {
                // Swap nilai (bukan node)
                int temp = curr->value;
                curr->value = curr->next->value;
                curr->next->value = temp;
                swapped = 1;
            }
            curr = curr->next;
        }
        last = curr; // Optimasi: elemen terakhir sudah terurut
    } while (swapped);
}

void sort_data() {
    if (head == NULL) return; // Jika kosong atau hanya 1 elemen, tidak perlu sorting

    struct tnode *i, *j;
    int temp;

    for (i = head; i != NULL; i = i->next) { 
        for (j = i->next; j != NULL; j = j->next) {
            if (i->value > j->value) {
                temp = i->value;
                i->value = j->value;
                j->value = temp;
            }
        }
    }
}

int main() {
    int pilihan, nilai, lokasi;

    while (1) {
        printf("\nSilakan pilih tipe operasi yang diinginkan:\n");
        printf("1. Push Front\n");
        printf("2. Push Back\n");
        printf("3. Push Mid\n");
        printf("4. Delete Front\n");
        printf("5. Delete Back\n");
        printf("6. Delete Mid\n");
        printf("7. Sort List\n");
        printf("8. Sort Data\n");
        printf("9. Exit\n");
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &pilihan);

        if (pilihan == 9) {
            printf("Keluar dari program.\n");
            break;
        }

        if (pilihan == 1 || pilihan == 2) {
            printf("Masukkan Angka: ");
            scanf("%d", &nilai);
        } else if (pilihan == 3 ) {
            printf("Masukkan angka dan posisi: ");
            scanf("%d %d", &nilai, &lokasi);
        } else if( pilihan == 6){
        	printf("Masukan angka yg ingin dihapus : ");
        	scanf("%d",&lokasi);
        	printf("\n");
		}

        switch (pilihan) {
            case 1:
                push_front(nilai);
                printf("Data : ");
                printlist();
                break;
            case 2:
                push_back(nilai);
                printlist();
                break;
            case 3:
                push_mid(nilai, lokasi);
                printlist();
                break;
            case 4:
            	delete_front();
            	printlist();
            	break;
            case 5:
            	delete_back();
            	printlist();
            	break;
            case 6:
            	delete_mid(lokasi);
            	printlist();
            case 7:
            	sort_list();
    			printf("List setelah sorting: ");
   	 			printlist();
    			break;
    		case 8:
    			sort_data();
    			printf("Data yg terurut adalah : ");
    			printlist();
    			break;
            default:
                printf("Pilihan tidak tersedia.\n");
        }
    }
    return 0;
}

