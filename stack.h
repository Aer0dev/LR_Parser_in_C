#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100
typedef struct Stack{
    char data[MAX];
    int top;
}Stack;

void initStack(Stack *s);

int isEmpty(Stack *s);

int isFull(Stack *s);

// 스택에 데이터 삽입
void push(Stack *s, char data);

// 스택에서 데이터 추출
char pop(Stack *s);

// 스택 최상단 데이터 확인
char peek(Stack *s);

// 스택의 특정인덱스에 접근
char accessIDX(Stack *s ,int index);

// 스택에서 인덱스까지 출력
void printStack(Stack *s, int index);

// 스택초기화
void clearStack(Stack *s);
