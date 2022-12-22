/*
 * day07_is_there_user.cpp
 *
 *  Created on: 2022. 12. 13.
 *      Author: bw.jung
 */
#include <cstdio>
/// *** user.cpp ***
extern int countSameNumber(int guess[]);

const int LM = 1000050;

int maxP;

int guess[LM];
int entry[LM];
void consistOf(int N, int K) {
    // 1 22 3333 44444444 (1,2,4,8)개
    // 1 -> 1
//    printf(">> N: %d, K:%d\n", N, K);

    // find minimum power of 2 number
    maxP = 0;
    while ((1 << (maxP + 1)) - 1 <= K)
        maxP++;
//    printf(">>>>%d, %d, %d\n", maxP, 1 << maxP, K);

    for (int nn = 1; nn <= N; nn += maxP) {
        int idx = 0;
        for (int kk = 0; kk < maxP; kk++) {
            const int rep = 1 << kk;
            const int val = nn + kk;
            for (int rr = 1; rr <= rep; rr++) {

//                printf("%d, %d\n", idx, val);
                guess[idx++] = val;
            }
        }
        int ret = countSameNumber(guess);

        for (int kk = 0; kk < maxP; kk++) {
            entry[nn + kk] = (ret >> kk) & 1;
        }

    }

}

int isEntryNumber(int num) {

    return entry[num];
}
