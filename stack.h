#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100
typedef struct Stack{
    char data[MAX];
    int top;
}Stack;

void initStack(Stack *s){
    s->top = -1;
}

int isEmpty(Stack *s){
    return s->top == -1;
}

int isFull(Stack *s){
    return s->top == MAX-1;
}

// 스택에 데이터 삽입
void push(Stack *s, char data) {
  if (isFull(s)) {
    printf("Stack Overflow!\n");
    return;
  }
  s->data[++s->top] = data;
}

// 스택에서 데이터 추출
char pop(Stack *s) {
  if (isEmpty(s)) {
    printf("Stack Underflow!\n");
    return -1;
  }
  return s->data[s->top--];
}

// 스택 최상단 데이터 확인
char peek(Stack *s) {
  if (isEmpty(s)) {
    printf("Stack Underflow!\n");
    return -1;
  }
  return s->data[s->top];
}

// 스택의 특정인덱스에 접근
char accessIDX(Stack *s ,int index){
  return s->data[index];
}

// 스택에서 인덱스까지 출력
void printStack(Stack *s, int index){
  for(int i = 0; i<=index; i++){
    printf("%d", accessIDX(s, i));
  }
}
