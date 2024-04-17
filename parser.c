#include <stdio.h>
#include <string.h>
#include "stack.h"

int action_tbl[12][6] = {
    {5, 0, 0, 4, 0, 0},
    {0, 6, 0, 0, 0, 999},
    {0, -2, 7, 0, -2, -2},
    {0, -4, -4, 0, -4, -4},
    {5, 0, 0, 4, 0, 0},
    {0, -6, -6, 0, -6, -6},
    {5, 0, 0, 4, 0, 0},
    {5, 0, 0, 4, 0, 0},
    {0, 6, 0, 0, 11, 0},
    {0, -1, 7, 0, -1, -1},
    {0, -3, -3, 0, -3, -3},
    {0, -5, -5, 0, -5, -5}};

int goto_tbl[12][4] = {
    {0, 1, 2, 3},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 8, 2, 3},
    {0, 0, 0, 0},
    {0, 0, 9, 3},
    {0, 0, 0, 10},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}};
char lhs[] = {' ', 'E', 'E', 'T', 'T', 'F', 'F'}; // dummy in 0 index
int rhs_len[] = {0, 3, 1, 3, 1, 3, 1};            // rhs length: 0 for dummy rule
char token[] = {'d', '+', '*', '(', ')', '$'};
char NT[] = {' ', 'E', 'T', 'F'}; // non-terminals: dummy in 0 index
Stack s;


int findTokenIDX(char target){      // 토큰의 인덱스를 찾는 함수
    for(int i = 0; i<6; i++){
        if(target == token[i])
            return i;
    }
    return -1;
}

int findNonterminalIDX(char target){    // 논터미널의 인덱스를 찾는 함수
    for(int i=0; i<4; i++){
        if(NT[i] == target){
            return i;
        }
    }
    return -1;
}

void printInput(Stack* s, char input[], int index){   // 현재처리중인 index부터 끝까지 출력하는 함수
    printf("\t");
    for(int i = index; i<strlen(input); i++){
        printf("%c", input[i]);
    }
}


void LR_Parser(char input[]){
    int length = strlen(input);
    int state = 0;  // 현재 상태를 나타내는 변수
    int index = 0;  // 문자열 인덱스 처리용 변수
    int phase = 1;  // 연산의 단계 표현해주는 변수

    push(&s, state+'0');
    printf("(%d) initial : ", phase);
    printStack(&s, phase);
    printf("\t");
    printInput(&s, input, index);
    printf("\n");

    phase++;

    while(index < length){
        char token = input[index];
        if(findTokenIDX(token) == -1){
            printf("(%d) Invalid Token (%c) error\n", phase, token);   // 토큰 예외처리
            state = 0;
            index = 0;
            phase = 0;
            clearStack(&s);
            break;
        }
        int action = action_tbl[state][findTokenIDX(token)];
        
        if(action > 0){ // SHIFT 연산수행
        
            state = action;     // state변경하고
            if(action == 999){
                printf("(%d) accept\n", phase);
                state = 0;
                index = 0;
                phase = 0;
                clearStack(&s);
                break;
            }
            push(&s, token);
            push(&s, state+'0');

            printf("(%d) shift %d: ",phase, state);
            index++;        
            phase++;
            printStack(&s, phase);
            printInput(&s, input, index);
            printf("\n");
            
        }

        else if(action < 0){    // REDUCE 연산수행
            int rule_num = -action;
            int rhs_length = rhs_len[rule_num];

            for(int i=0; i<rhs_length * 2; i++){    // 스택에서 rhs_length*2만큼 pop
                pop(&s);
            }
            char lhs_symbol = lhs[rule_num];
            state = goto_tbl[peek(&s) - '0'][findNonterminalIDX(lhs_symbol)];
            
            push(&s, lhs_symbol);
            push(&s, state+'0');

            printf("(%d) reduce %d: ",phase, rule_num);
            phase++;
            printStack(&s, phase);
            printInput(&s, input, index);
            printf("\n");
            
        }
    
        
        else{
            printf("(%d) error\n", phase); 
            state = 0;
            index = 0;
            phase = 0;
            clearStack(&s);
            break;
        }
    }
}

int main(){
    char input[MAX];
    
    initStack(&s);
    while (1)
    {
        printf("\nInput: ");
        scanf("%s", input);
        if (input[0] == '$')
            break;
        LR_Parser(input);
    }
}
