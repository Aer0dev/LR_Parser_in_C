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



int findTokenIDX(char target){
    for(int i = 0; i<6; i++){
        if(target == token[i])
            return i;
    }
    return -1;
}

int findNonterminalIDX(char target){
    for(int i=0; i<4; i++){
        if(NT[i] == target){
            return i;
        }
    }
    return -1;
}


void LR_Parser(char input[]){
    int length = strlen(input);
    int state = 0;  // 현재 상태를 나타내는 변수
    int index = 0;  // 문자열 인덱스 처리용 변수
    int phase = 1;  // 연산의 단계 표현해주는 변수

    push(&s, state+'0');
    printf("(%d) initial : %c\n", phase, peek(&s));

    phase++;

    while(index <= length){
        char token = input[index];
        if(findTokenIDX(token) == -1){
            printf("Invalid Token (%c) error\n", token);   /// 토큰 예외처리
        }
        int action = action_tbl[state][findTokenIDX(token)];
        
        if(action > 0){ // SHIFT 연산수행
        
            state = action;     // state변경하고
            if(action == 999){
                printf("(%d) accept\n", phase);
                break;
            }
            push(&s, token);
            push(&s, state+'0');
            printf("(%d) push : %c shift %d\n",phase ,token, state);
            index++;
            phase++;
        }

        else if(action < 0){    // REDUCE 연산수행
            int rule_num = -action;
            int rhs_length = rhs_len[rule_num];
            printf("token = %c\n", input[index]);

            for(int i =0; i<rhs_length *2; i++){
                char poped_symbol = peek(&s);
                pop(&s);
            }
            char lhs_symbol = lhs[rule_num];
            state = goto_tbl[peek(&s) - '0'][findNonterminalIDX(lhs_symbol)];
            
            push(&s, lhs_symbol);
            
            printf("goto: %d\n", state);
            push(&s, state+'0');
            printf("(%d) reduce %d, state %d\n",phase, rule_num, state);
            phase++;
        }
    
        
        else{
            
            break;
        }
        
    }
    /*
    if(state == 999){
        printf("Parsing successful!\n");
    }
    else{
        printf("Parsing error!\n");
    }
    */
}

int main(){
    char input[MAX];
    int curr = 0;

    
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
