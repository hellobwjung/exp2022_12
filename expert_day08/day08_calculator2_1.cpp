/*
 * day08_calculator2_1.cpp
 *
 *  Created on: 2022. 12. 14.
 *      Author: bw.jung
 */

#include <cstdio>

using LL = long long;

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
    else return; // '(', ')' 이면 그냥 return, 계산 못함.
    opTop--, numTop--;
}

int main() {

    scanf("%s", exp);
    for (int i = 0; exp[i];) {

        if (exp[i] > 47) { // 숫자이면, stack에 넣어둬.

            LL d = 0;
            for (; exp[i] > 47; i++) {
                d = d * 10 + exp[i] - '0';
            }
            numStk[++numTop] = d;
            if (opStk[opTop]=='*' || opStk[opTop]=='/') calc();
        }
        else { // operation이면,

            if (exp[i] == '+' || exp[i] == '-') {
                // 현재 op +/-가 우선순위가 낮으므로,
                // 이전 op로 연산 하면 된다.
                calc();
                opStk[++opTop] = exp[i];
            }
            else if (exp[i] == ')') { //괄호가 닫혔다, 밀린 계산 해라.
                calc();
                opTop--; // pop '('
                if (opStk[opTop] == '*' || opStk[opTop] == '/') {
                    calc(); // '('괄호 벗겨 냇으니, 그 다음 연산이
                            // 우선순위가 높은 '*', '/' 이면 연산시켜,
                            // 아니면, +, -,
                            // 또다른 (
                }
            }
            else { // '(', '*', '/', 걍 stack에 추가
                opStk[++opTop] = exp[i];
            }
            i++;

        }

    }
    calc();

    printf("%lld\n", numStk[numTop]);

    return 0;
}

