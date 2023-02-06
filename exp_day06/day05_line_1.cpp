/*
 * day05_line_1.cpp
 *
 *  Created on: 2022. 12. 10.
 *      Author: bw.jung
 */

#include <cstdio>

const int LM = 100000 + 10;
int N;
int H[LM];
int brr[LM];
int A[LM];
int S[LM];
int Next[LM];

void print(int *arr) {
    for (int nn = 0; nn < N; nn++) {
        printf("%03d ", arr[nn]);
    }
    puts("");

}
int input() {
    scanf("%d", &N);
    for (int nn = 0; nn < N; nn++) {
        scanf("%d", (H + nn));
        Next[nn] = nn + 1;
    }
    Next[N - 1] = -1;

    for (int nn = 0; nn < N; nn++) {
        scanf("%d", (S + nn));
    }

}

void mSort(int *arr, int s, int e) {
    // base
    if (s >= e) {
        return;
    }

    // divide
    const int m = (s + e) / 2;
    mSort(arr, s, m);
    mSort(arr, m + 1, e);

    // conquer
    int k = s;
    int l = s, r = m + 1;
    while (l <= m && r <= e) {
//        printf("l: %d, r=%d\n", l, r);
        if (arr[l] < arr[r]) brr[k++] = arr[l++];
        else brr[k++] = arr[r++];
    }
    while (l <= m)
        brr[k++] = arr[l++];
    while (r <= e)
        brr[k++] = arr[r++];

    // copy
    for (int nn = s; nn <= e; nn++) {
        arr[nn] = brr[nn];
    }

}

int SearchIdx(int order) {
    int idx = 0;

    for (int nn = 0; nn < N; nn++) {

        if (Next[idx] > 0) {
            if (order == idx) {
                Next[idx] = -1;
                return idx;
            }
            idx++;
        }

    }
    return -1;
}

void sol1() {

    print(H);
    mSort(H, 0, N - 1);
    print(H);
    print(S);

    for (int nn = N - 1; nn >= 0; nn--) {
        int order = S[nn];

        int idx = 0;
        int kk = 0;
        for (; kk < N; kk++) {
            if (H[kk] > 0) {
//                printf("H[%d]=%d\n", kk, H[kk]);
                idx++;
            }

            printf("%2d] kk=%d, idx=%d, order=%d\n", nn, kk, idx, order);
            if (idx >= order) break;

        }

        printf("H: ");
        print(H);
        int val = H[idx];
        H[idx] = -1;
        A[nn] = val;
        printf("H: ");
        print(H);
        printf("A: ");
        print(A);
//        break;

    }
    print(A);
}

int main() {

//    input();
//
//    sol1();

    printf("hello day05\n");

    return 0;
}

