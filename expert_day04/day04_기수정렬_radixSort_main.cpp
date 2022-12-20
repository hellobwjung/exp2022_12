/*
 * day04_기수정렬_radixSort_main.cpp
 *
 *  Created on: 2022. 12. 8.
 *      Author: bw
 */

/// ***** main.cpp *****
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

const int NMAX = (int) 25e6;
const int QMAX = 10000;

static int N, A[NMAX + 1];
static int M, Q[QMAX + 1];
static int ans[QMAX + 1];

extern void initUser(int, int*);
extern int query(int);

static void input() {
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", A + i);
  }

  scanf("%d", &M);

  for (int i = 0; i < M; ++i) {
    scanf("%d", Q + i);
  }

  for (int i = 0; i < M; ++i) {
    scanf("%d", ans + i);
  }
}

static bool process() {
  initUser(N, A);

  for (int i = 0; i < M; ++i) {
    int result = query(Q[i]);
    if (result != ans[i])
      return 0;
  }
  return 1;
}

int main() {
  freopen("input.txt", "r", stdin);
  input();
  if (process())
    puts("100");
  else
    puts("0");
  return 0;
}
