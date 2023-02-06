/*
 * day08_calculator2.cpp
 *
 *  Created on: 2022. 12. 14.
 *      Author: bw.jung
 */

#include <cstdio>

#define LL  long long
const int LM = 210;
char exp[LM];

char opStk[LM];
LL numStk[LM];
int opTop, numTop;

void calc() {
    char op = opStk[opTop];
    if (op == '+') numStk[numTop - 1] += numStk[numTop];
    else if (op == '-') numStk[numTop - 1] -= numStk[numTop];
    else if (op == '*') numStk[numTop - 1] *= numStk[numTop];
    else if (op == '/') numStk[numTop - 1] /= numStk[numTop];
    else return;

    opTop--, numTop--;

}

int main() {
    scanf("%s", exp);
    for (int i = 0; exp[i];) {
        if (exp[i] > 47) { // 숫자 라면.
            LL d = 0;
            for (; exp[i] > 47; i++) {
                d = d * 10 + exp[i] - '0';
            }
            numStk[++numTop] = d;
            if (opStk[opTop] == '*' || opStk[opTop] == '/') calc();
        }
        else { // 연산자 라면,
            if (exp[i] == '+' || exp[i] == '-') {
                calc(); //+/- 우선순위가 낮으므로 앞에꺼 계산시켜
                opStk[++opTop] = exp[i]; // 그리고 op를 opStk에 넣어
            }
            else if (exp[i] == ')') { // 우선 순위 높으므로 에꺼 연산 시키면 됨.
                calc();
                printf("opPop: %c\n", opStk[opTop]);
                opTop--; // '('지우기, --------->반드시 '('이겠군?
                if (opStk[opTop] == '*' || opStk[opTop] == '/') calc();

            }
            else { // '(', '*', '/' 는 단순히 연산자 스택에 추가하면 된다.
                opStk[++opTop] = exp[i];
            }
            i++;
        }
    }
    calc(); // 남은것 있으면 계산
    printf("%lld\n", numStk[numTop]);

    return 0;
}

