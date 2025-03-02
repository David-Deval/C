#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode {
    char data[100];
    struct tnode* next;
};

struct Stack {
    struct tnode* top;
};

void initStack(struct Stack* s) {
    s->top = NULL;
}

void push(struct Stack* s, char* value) {
    struct tnode* newNode = (struct tnode*)malloc(sizeof(struct tnode));
    strcpy(newNode->data, value);
    newNode->next = s->top;
    s->top = newNode;
}

void pop(struct Stack* s, char* result) {
    if (s->top == NULL) return;
    struct tnode* temp = s->top;
    strcpy(result, temp->data);
    s->top = temp->next; 
    free(temp);
}

int isEmpty(struct Stack* s) {
    return s->top == NULL;
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void infixToPostfix(char* infix, char* postfix) {
    struct Stack s;
    initStack(&s);
    int j = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        if ((infix[i] >= '0' && infix[i] <= '9') || (infix[i] >= 'A' && infix[i] <= 'Z') || (infix[i] >= 'a' && infix[i] <= 'z')) {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            char str[2] = "(";
            push(&s, str);
        } else if (infix[i] == ')') {
            while (!isEmpty(&s) && s.top->data[0] != '(') {
                postfix[j++] = s.top->data[0];
                pop(&s, s.top->data);
            }
            pop(&s, s.top->data);
        } else {
            while (!isEmpty(&s) && precedence(s.top->data[0]) >= precedence(infix[i])) {
                postfix[j++] = s.top->data[0];
                pop(&s, s.top->data);
            }
            char str[2] = {infix[i], '\0'};
            push(&s, str);
        }
    }
    while (!isEmpty(&s)) {
        postfix[j++] = s.top->data[0];
        pop(&s, s.top->data);
    }
    postfix[j] = '\0';
}

void postfixToInfix(char* postfix, char* infix) {
    struct Stack s;
    initStack(&s);
    char op1[100], op2[100], temp[100];
    
    for (int i = 0; postfix[i] != '\0'; i++) {
        if ((postfix[i] >= '0' && postfix[i] <= '9') || (postfix[i] >= 'A' && postfix[i] <= 'Z') || (postfix[i] >= 'a' && postfix[i] <= 'z')) {
            char str[2] = {postfix[i], '\0'};
            push(&s, str);
        } else {
            pop(&s, op2);
            pop(&s, op1);
            sprintf(temp, "(%s%c%s)", op1, postfix[i], op2);
            push(&s, temp);
        }
    }
    pop(&s, infix);
}

int main() {
    char infix[100], postfix[100], result[100];
    
    printf("Input infix : ");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    printf("Versi postfix : %s\n", postfix);
    
    postfixToInfix(postfix, result);
    printf("Konversi kembali ke Infix: %s\n", result);
    
    return 0;
}

