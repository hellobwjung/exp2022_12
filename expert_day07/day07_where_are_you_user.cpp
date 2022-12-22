/*
 * day07_where_are_you_user.cpp
 *
 *  Created on: 2022. 12. 13.
 *      Author: bw.jung
 */

#include <cstdio>
#if 1
extern int countScore(int guess[]);

const int LM = 256;
//int SEQ[LM];

int *user;
int index[LM];
int entry[LM];

/// ***** user.cpp *****

void getEntry() {
    // find entry
    const int K = 200;
    int bin = 0;
    int idx = 0;
    while ((1 << (bin + 1)) < K) {
        bin++;
    }
    int guess[LM] =
        { 0 };
    for (int nn = 1; nn <= 200; nn += bin) {
        int idx = 0;

        for (int kk = 0; kk < bin; kk++) {
            const int rep = 1 << kk;
            for (int rr = 0; rr < rep; rr++) {
                guess[idx++] = nn + kk;
            }
        }
        const int ret = countScore(guess) % 256; // 존재 유무만 판단.
        for (int kk = 0; kk < bin; kk++) {
            if ((ret >> kk) & 1) { //nn+kk가 entry라면
                entry[idx++] = nn + kk;
            }
//            entry[nn + kk] = (ret >> kk) & 1;

        }

    }
}

//void DAC(int s, int e, int totalCnt) {
//    if (totalCnt == 0) {
//        return;
//    }
//    // base condition
//    if (e - s + 1 == totalCnt) {
//        for (int i = s; i <= e; i++) {
//            user[index[i]] = entry[index[i]];
//            entry[index[i]] = 0;
//        }
//        return;
//    }
//
//    // normal condition
//    register int i, m = (s + e) / 2;
//    int leftEntry[LM] =
//        { 0 };
//    for (i = s; i <= m; i++) {
//        leftEntry[index[i]] = entry[index[i]];
//    }
//    int leftCnt = countScore(leftEntry) / 256;
//    DAC(s, m, leftCnt);
//    DAC(m + 1, e, totalCnt - leftCnt);
//
//}

void DAC(int s, int e, int totalCnt) {
    if (totalCnt == 0) return;   // bounding
    // base condition
    if (totalCnt == e - s + 1) {
        for (int i = s; i <= e; ++i) {
            user[index[i]] = entry[index[i]];    // 자리를 찾은 경우 결과배열에 저장하고
            entry[index[i]] = 0;            // 지우기
        }
        return;
    }
    // normal condition
    int i, m = (s + e) / 2;
    int leftEntry[LM] =
        { 0 };
    for (i = s; i <= m; ++i) {  // 절반만 데이터를 복사하여 확인하기
        leftEntry[index[i]] = entry[index[i]];
    }
    int leftCnt = countScore(leftEntry) / 256;
    DAC(s, m, leftCnt);
    DAC(m + 1, e, totalCnt - leftCnt);
}

void consistOf(int userRet[]) {
    user = userRet;

    getEntry();

    register int i;
    for (i = 0; i < 200; i++) {
        index[i] = i; // 각 entry의 index를 저장.
    }

    int indexCnt = 200; // 처음 200개로 시작.
    while (indexCnt) {

        int totalCnt = countScore(entry) / 256;

        // 1. 자리 확정하기
        DAC(0, indexCnt, totalCnt); // s부터 e까지 totalCnt개 있어.

        // 2. 아직 자리 찾지 못한 위치 구하기
        indexCnt = 0;
        for (i = 0; i < 200; i++) {
            if (entry[i]) index[indexCnt++] = i;
        }

        // 3. 위치를 회전시키기
        register int tmp = entry[index[0]];
        for (i = 0; i < indexCnt - 1; i++) {
            entry[index[i]] = entry[index[i + 1]];
        }
        entry[index[i]] = tmp;

    }

}

#else

/// *** user.cpp ***
/*
 28_어디있니_user
 D&C
 */
extern int countScore(int guess[]);

#define rint  register int
const int LM = 256;
int *ret;
int entry[LM]; // 200 entry
int index[LM]; // remain index array

void getEntry() {
    rint i, j, p, x, cnt = 0;  // N=255로, K=200으로 고정 따라서 bin = 7로 고정
    int guess[LM] =
        { 0 };
    for (i = 1; i <= 255; i += 7) {
        int p = 0, x;
        for (j = 0; j < 7; ++j) {
            int len = 1 << j;  // 1, 2, 4, 8, 16, .., 32768
            for (x = 0; x < len; ++x) {
                guess[p++] = i + j;
            }
        }
        int ret = countScore(guess) % 256;  // 존재유무만 판단
        for (j = 0; j < 7; ++j) {
            if ((ret >> j) & 1)  // i + j가 entry라면
            entry[cnt++] = i + j;
        }
    }
}

void DAC(int s, int e, int totalCnt) {
    if (totalCnt == 0) return;   // bounding
    // base condition
    if (totalCnt == e - s + 1) {
        for (int i = s; i <= e; ++i) {
            ret[index[i]] = entry[index[i]];    // 자리를 찾은 경우 결과배열에 저장하고
            entry[index[i]] = 0;            // 지우기
        }
        return;
    }
    // normal condition
    rint i, m = (s + e) / 2;
    int leftEntry[LM] =
        { 0 };
    for (i = s; i <= m; ++i) {  // 절반만 데이터를 복사하여 확인하기
        leftEntry[index[i]] = entry[index[i]];
    }
    int leftCnt = countScore(leftEntry) / 256;
    DAC(s, m, leftCnt);
    DAC(m + 1, e, totalCnt - leftCnt);
}

void consistOf(int userRet[]) {
//    printf("%s\n", __func__);
    ret = userRet;
    getEntry();
    int indexCnt = 200;
    rint i;
    for (i = 0; i < 200; ++i)
        index[i] = i;

    while (indexCnt) {
        int totalCnt = countScore(entry) / 256; // 자리를 찾은 개수 구하기

        // 1. 자리를 확정하기
        DAC(0, indexCnt, totalCnt);

        // 2. 아직 자리를 찾지 못한 위치 구하기
        indexCnt = 0;
        for (i = 0; i < 200; ++i) {
            if (entry[i]) index[indexCnt++] = i;
        }

        // 3. 위치를 회전시키기
        rint t = entry[index[0]];
        for (i = 0; i < indexCnt - 1; ++i) {
            entry[index[i]] = entry[index[i + 1]];
        }
        entry[index[i]] = t;
    }
}

#endif
