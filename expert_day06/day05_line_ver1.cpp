/*
 * day05_line_ver1.cpp
 *
 *  Created on: 2022. 12. 9.
 *      Author: bw.jung
 */

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
 21_줄세우기_ver01
 sqrt decomposition
 */
#include <cstdio>

const int LM = 100005;
const int MOD = 256;
int N, H[LM], B[LM / MOD + 1], T[LM], qrr[LM];
int ans[LM];

void mergeSort(int s, int e) {
    if (s + 1 >= e) return;
    int m = (s + e) / 2, i = s, j = m, k = s;
    mergeSort(s, m), mergeSort(m, e);
    while (i < m && j < e) {
        if (H[i] <= H[j]) T[k++] = H[i++];
        else T[k++] = H[j++];
    }
    while (i < m)
        T[k++] = H[i++];
    while (j < e)
        T[k++] = H[j++];
    for (i = s; i < e; ++i)
        H[i] = T[i];
}

void update(int idx) {
    H[idx] = 0, B[idx / MOD]--;
}

int query(int tg) {
    int i = 0;
    for (; B[i] < tg; ++i)
        tg -= B[i];
    i *= MOD;
    for (; tg; ++i) {
        if (H[i]) tg--;
        if (tg == 0) return i;
    }
    return -1;
}

int main() {
#ifdef _WIN32
    freopen("21.txt", "r", stdin);
#endif // _WIN32
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", H + i);
        B[i / MOD]++;
    }

    mergeSort(0, N);

    for (int i = 0; i < N; ++i)
        scanf("%d", qrr + i);

    for (int i = N - 1; i >= 0; --i) {
        int ret = query(qrr[i] + 1);
        ans[i] = H[ret];
        update(ret);
    }

    for (int i = 0; i < N; ++i)
        printf("%d\n", ans[i]);

    return 0;
}
