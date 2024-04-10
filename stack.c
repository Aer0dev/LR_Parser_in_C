#include "stack.h"

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
  s->data[s->top] = '\0';       // 데이터 삭제
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
  int temp = 0;
  for(int i = 0; i<=index; i++){
    if(accessIDX(s, i) == ':') {
      temp = 10;
      printf("%d", temp);
    }
    else if(accessIDX(s, i) == ';') {
      temp = 11;
      printf("%d", temp);
    }
    
    else
      printf("%c", accessIDX(s, i));
  }
}

void clearStack(Stack *s){
  while(!isEmpty(s)){
    pop(s);
  }
}
