/*
 * day02_const구간의합구하기2D_1.cpp
 *
 *  Created on: 2023. 1. 12.
 *      Author: bw
 */

#include <cstdio>
int N;
const int LM = 1'000 + 10;
long long ans;
int arr[LM][LM];
long long acc[LM][LM];

//template<typename T>
//void print(T *a[LM]) {
void print() {
  for (int yy = 1; yy <= N; yy++) {
    for (int xx = 1; xx <= N; xx++) {
      printf("%2d ", arr[yy][xx]);
    }
    puts("");
  }
  printf("\n\n");
}

void print2() {
  for (int yy = 1; yy <= N; yy++) {
    for (int xx = 1; xx <= N; xx++) {
      printf("%2lld ", acc[yy][xx]);
    }
    puts("");
  }
  printf("\n\n");
}

void input() {
  int num;
  scanf("%d", &N);
  for (int yy = 1; yy <= N; yy++) {
    for (int xx = 1; xx <= N; xx++) {
      scanf("%d", &num);
      arr[yy][xx] = num;
      acc[yy][xx] = num + acc[yy][xx - 1] + acc[yy - 1][xx]
          - acc[yy - 1][xx - 1];
    }
  }
}

void sol() {
  int nQ = 0;
  scanf("%d", &nQ);
  int sy = 0, sx = 0, ey = 0, ex = 0;
  for (int nn = 0; nn < nQ; nn++) {
    scanf("%d %d %d %d", &sy, &sx, &ey, &ex);
    const long long ans = acc[ey][ex] - acc[ey][sx - 1] - acc[sy - 1][ex]
        + acc[sy - 1][sx - 1];

    printf("%lld\n", ans);

  }

}

int main() {

  input();
//  print();
//  print2();

  sol();

  return 0;
}

