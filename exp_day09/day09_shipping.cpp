/*
 * day09_shipping.cpp
 *
 *  Created on: 2022. 12. 15.
 *      Author: bw.jung
 */

#include <cstdio>

const int LM = 3010;
int N;
int tcost, hcost;
int a[LM], t[LM], sum[LM], D[LM];

void msort(int *arr, int s, int e) {
    if (s >= e) return;

    // divide
    int m = (s + e) / 2;
    msort(arr, s, m);
    msort(arr, m + 1, e);

    // conquer
    int left = s, right = m + 1;
    int k = s;
    while (left <= m && right <= e) {
        if (arr[left] < arr[right]) t[k++] = arr[left++];
        else t[k++] = arr[right++];
    }

    // merge
    while (left <= m)
        t[k++] = arr[left++];
    while (right <= e)
        t[k++] = arr[right++];

    // copy
    for (int nn = s; nn <= e; nn++) {
        arr[nn] = t[nn];
    }

}
void print(int s, int e) {
    for (int nn = s; nn <= e; nn++) {
        printf("%d ", a[nn]);
    }
    puts("");
}

inline int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d", &N);
    for (int nn = 1; nn <= N; nn++) {
        scanf("%d", &a[nn]);
    }
    scanf("%d %d", &tcost, &hcost);
    printf("%d %d\n", tcost, hcost);

    msort(a, 1, N);
    // get prefix sum;
    for (int i = 1; i <= N; i++) {
        sum[i] = sum[i - 1] + a[i];
    }

    // DP
    for (int ed = 1; ed <= N; ed++) {
        // a는 오름차순, 그냥 이동거리만 중요.
        // 가장 가까운 지점부터 구해,

        // 이전 지점 cost  + truck으로 본사부터 이동지점까지 이동
        D[ed] = D[ed - 1] + a[ed] * tcost;
        for (int st = 1; st <= ed; st++) {

        }
    }
    return 0;
}
