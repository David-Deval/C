#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int newid = 1;

struct tnode{
	int ID;
	int deadline;
	char task[100];
	struct tnode *next;
	struct tnode *prev;
}*head,*tail,*curr;

struct tnode *createnode(int deadline, char task[]){
	struct tnode *newnode = (struct tnode*)malloc(sizeof(struct tnode));
	newnode->ID = newid++;
	newnode->deadline = deadline;
	strcpy(newnode->task, task);
	newnode->next = newnode->prev = NULL;
	return newnode;
};

void sortedone(){
	if(head == NULL){
		return;
	}
	struct tnode *i,*j;
	int temp;
	char temp_task[100];
	for(i = head; i != NULL; i= i->next){
		for(j=i->next;j!=NULL;j=j->next){
			if(i->deadline > j->deadline){
				temp = i->deadline;
				i->deadline = j->deadline;
				j->deadline = temp;
				
				strcpy(temp_task, i->task);
				strcpy(i->task, j->task);
				strcpy(j->task, temp_task);
			}
		}
	}
}

void push_front(int deadline, char task[]){
	struct tnode *node = createnode(deadline, task);
	if(head == NULL){
		head = tail = node;
	}else{
		node->next = head;
		head->prev = node;
		head = node;
		head->prev = NULL;
	}
}
// kek delete mid ?
void removeid(int id){
	if(head == NULL){
		printf("There is no data to be print\n");
	}
	struct tnode *curr = head;
	
	while(curr != NULL && curr->ID != id){
		curr = curr ->next;
	}
	
	if (curr == head && curr == tail) {
        head = tail = NULL;
    } else if (curr == head) {
        head = head->next;
        head->prev = NULL;
    } else if (curr == tail) {
        tail = tail->prev;
        tail->next = NULL;
    } else {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }

    free(curr);
}
	

void printlist(){
	struct tnode *curr =head;
	while(curr != NULL){
		printf("deadline : %d\n", curr->deadline);
		printf("task : %s\n", curr->task);
		printf("ID : %d\n",curr->ID);
		curr = curr->next;
	}
}
// buat finsihtask ?
void delete_front(){
	if(head == NULL){
		printf("There is no data to be deleted\n");
	}
	struct tnode *del = head;
	if(head == tail){
		head = tail = NULL;
	}else{
	head = head->next;
	head->prev = NULL;
	}
	free(del);
}

int main(){
	int numtask;
	int numop;
	char ofop[100];
	int deadline;
	char task[100];
	scanf("%d %d",&numtask, &numop);
	getchar();
	
	for(int i =0;i<numtask;i++){
		scanf("%d %[^\n]", &deadline, task);
		push_front(deadline, task);
	}
	sortedone();
	
	for(int i =0;i<numop;i++){
		scanf("%[^\n]",ofop);
		getchar();
		if(strcmp(ofop,"finishtask")== 0){
			delete_front();
		}else {
			int ID;
			sscanf(ofop,"removeID %d", &ID);
			removeid(ID);
		}	
	}
	printlist();
}
