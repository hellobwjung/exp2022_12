/*
 * day01_구간업데이트2D_눈내리는겨울밤2_2.cpp
 *
 *  Created on: 2023. 1. 13.
 *      Author: bw
 */

#include <cstdio>

const int LMN = 1'000 + 10;
const int LMQ = 1'000'000 + 10;
using LL = long long;
LL A[LMN][LMN], S[LMN][LMN];
int N, Q;
int sy, ey, sx, ex, val;

void input() {
  scanf("%d %d", &N, &Q);
  for (int nn = 0; nn < Q; nn++) {
    scanf("%d %d %d %d %d", &sy, &sx, &ey, &ex, &val);
    A[sy][sx] += val;
    A[ey + 1][ex + 1] += val;
    A[sy][ex + 1] -= val;
    A[ey + 1][sx] -= val;
  }
  for (int yy = 1; yy <= N; yy++) {
    for (int xx = 1; xx <= N; xx++) {
      S[yy][xx] = A[yy][xx] + S[yy][xx - 1] + S[yy - 1][xx] - S[yy - 1][xx - 1];
    }
  }

}

void output() {
  for (int yy = 1; yy <= N; yy++) {
    for (int xx = 1; xx <= N; xx++) {
      printf("%lld ", S[yy][xx]);
    }
    printf("\n");
  }
  printf("\n");
}
int main() {
  input();
  output();
  return 0;
}
