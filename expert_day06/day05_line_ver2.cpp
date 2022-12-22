/*
 * day05_line_ver2.cpp
 *
 *  Created on: 2022. 12. 9.
 *      Author: bw.jung
 */

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
 21_줄세우기_ver02
 segment tree
 */
#include <cstdio>

const int LM = 100005;
const int TLM = 1 << 18; // 262144
int N, H[LM], T[LM], tree[TLM], qrr[LM];
int ans[LM];

void mergeSort(int s, int e) {
    if (s >= e) return;
    int m = (s + e) / 2, i = s, j = m + 1, k = s;
    mergeSort(s, m), mergeSort(m + 1, e);
    while (i <= m && j <= e) {
        if (H[i] <= H[j]) T[k++] = H[i++];
        else T[k++] = H[j++];
    }
    while (i <= m)
        T[k++] = H[i++];
    while (j <= e)
        T[k++] = H[j++];
    for (i = s; i <= e; ++i)
        H[i] = T[i];
}

void build(int node, int s, int e) {
    if (s == e) {
        tree[node] = 1;
        return;
    }
    int lch = node * 2, rch = lch + 1, m = (s + e) / 2;
    build(lch, s, m);
    build(rch, m + 1, e);
    tree[node] = tree[lch] + tree[rch];
}

void update(int node, int s, int e, int cnt, int ansIdx) {
    tree[node]--;
    if (s == e) {
        ans[ansIdx] = H[s];
        return;
    }
    int lch = node * 2, rch = lch + 1, m = (s + e) / 2;
    if (tree[lch] > cnt) update(lch, s, m, cnt, ansIdx);
    else update(rch, m + 1, e, cnt - tree[lch], ansIdx);
}

int main() {
#ifdef _WIN32
    freopen("21.txt", "r", stdin);
#endif // _WIN32
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i)
        scanf("%d", H + i);
    for (int i = 1; i <= N; ++i)
        scanf("%d", qrr + i);

    mergeSort(1, N);

    build(1, 1, N);

    for (int i = N; i > 0; --i)
        update(1, 1, N, qrr[i], i);

    for (int i = 1; i <= N; ++i)
        printf("%d\n", ans[i]);

    return 0;
}
