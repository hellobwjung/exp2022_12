/*
 * day01_구간업데이트2D_눈내리는겨울밤2.cpp
 *
 *  Created on: 2022. 12. 5.
 *      Author: bw
 */

#include <cstdio>
const int LM = 1000 + 10;
int arr[LM][LM];
long long sum[LM][LM];
int N, Q;
int sy, sx, ey, ex;
int val;

int main() {
  scanf("%d %d", &N, &Q);
//  printf("%d %d\n", N, Q);

  for (int i = 0; i < Q; i++) {
    scanf("%d %d %d %d %d", &sy, &sx, &ey, &ex, &val);
//    printf("%d %d %d %d %d\n", sy, sx, ey, ex, val);
    ++ey, ++ex;
    arr[sy][sx] += val;
    arr[ey][ex] += val;

    arr[sy][ex] -= val;
    arr[ey][sx] -= val;
  }

  for (int yy = 1; yy <= N; yy++) {
    for (int xx = 1; xx <= N; xx++) {
      sum[yy][xx] = sum[yy - 1][xx] + sum[yy][xx - 1] - sum[yy - 1][xx - 1]
          + arr[yy][xx];
    }
  }

  for (int yy = 1; yy <= N; yy++) {
    for (int xx = 1; xx <= N; xx++) {
      printf("%lld ", sum[yy][xx]);
    }
    printf("\n");

  }
  return 0;
}

