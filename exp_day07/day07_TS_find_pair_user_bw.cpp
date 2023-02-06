/*
 * day07_TS_find_pair_user_bw.cpp
 *
 *  Created on: 2022. 12. 13.
 *      Author: bw.jung
 */

/*** user.cpp ***/
extern bool checkCards(int indexA, int indexB, int diff);

const int LM = 50005;
int NN, listOfDiff[LM][4], listLen[LM];

void playGame(int N) {

    // 0. init
    for (int nn = 0; nn < N; nn++) {
        listLen[nn] = 0;
    }

    //1. 데이터 차이로 분류하기.
    //   -- 0번 index에 있는 값과, 1~2N-1번 index에 있는 값들의 차이를 구해,
    //      차이 값을 listOfDiff에 넣어,
    int i;
    for (i = 1; i < NN; i++) {
        int s = 0, e = N - 1, m = -1, diff = 0;
        while (s <= e) {
            m = (s + e) / 2;
            bool ret = checkCards(0, i, m);
            if (ret) e = m - 1, diff = m;
            else s = m + 1;
        }
        listOfDiff[diff][listLen[diff]++] = i;
    }

    // 2. 짝을 정하기

    for (i = 1; listLen[i] == 4; i++) {
    if (checkCards())
}

}
