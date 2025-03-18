#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct book{
	char genre[100];
	char code[50];
	char name[1000];
	struct book *next;
}*head,*curr;

struct book* createnode(char *genre, char *code, char *name){
	struct book* newnode = (struct book*)malloc(sizeof(struct book));
	strcpy(newnode->genre,genre);
	strcpy(newnode->code,code);
	strcpy(newnode->name,name);
	newnode->next = NULL;
	return newnode;
}

void insertsort(char *genre, char *code, char *name){
	struct book *newnode = createnode(genre, code, name);
	
	if(head == NULL || strcmp(head->name,name)>0){
		newnode->next = head;
		head = newnode;
		return;
	}
	
	curr = head;
	while(curr->next != NULL && strcmp(curr->next->name,name) < 0){
		curr = curr->next;
	}
	newnode->next = curr->next;
	curr->next = newnode;
}

void deletebykey(char *key, char *type){
	struct book *temp = head;
	struct book *prev = NULL;
	
	while(temp != NULL){
		int match = 0;
		if(strcmp(type,"Genre") == 0 && strcmp(temp->genre,key) == 0 )match = 1;
		else if(strcmp(type,"Code") == 0 && strcmp(temp->code,key) == 0 )match = 1;
		else if(strcmp(type,"Name") == 0 && strcmp(temp->name,key) == 0 )match = 1;
		
		if(match){
			if(prev == NULL){
				head = temp->next;
			}else{
			prev->next = temp->next;
		}free(temp);
		
		temp = (prev == NULL) ? head : prev->next;
        } else {
            prev = temp;
            temp = temp->next;
		}
    }
}

void printList() {
    curr = head;
    while (curr != NULL) {
        printf("%s %s %s\n", curr->genre, curr->code, curr->name);
        curr = curr->next;
    }
}

int main(){
	int N;
	scanf("%d",&N);
	
	char deletedata[20];
	scanf("%s",deletedata);
	printf("\n");
	
	char genre[100];
	char code[50];
	char name[1000];
	for(int i=0;i<N;i++){
		scanf("%s %s %[^\n]",genre,code,name);
		insertsort(genre,code,name);
	}
	
	printf("Data awal :\n");
	printList();
    printf("\n");

	char keytodelete[1000];
	scanf(" %[^\n]",keytodelete);
	deletebykey(keytodelete, deletedata);
	printf("Data yang sudah didelete :\n");
	printList();
}
