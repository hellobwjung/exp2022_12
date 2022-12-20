/*
 * day01_minecraft1_1.cpp
 *
 *  Created on: 2022. 12. 5.
 *      Author: bw
 */

#include <cstdio>

const int LM = 500 * 500 + 10;
int N, M, NM;
int B;
int A[LM];
int ansTime = 1 << 30, ansHeight;

int check(int tgH) {

  int timeCost = 0, inven = B;

  for (int i = 0; i < NM; ++i) {
    if (A[i] < tgH) {
      const int diff = tgH - A[i];
      inven -= diff;
      timeCost += diff;
    } else {
      const int diff = A[i] - tgH;
      inven += diff;
      timeCost += diff * 2;
    }

    if (inver < 0) {
      return 1;
    }
    if (timeCost <= anstime) {
      ansTime = timeCost;
      ansHeight = tgH;
    }

  }

  return 0;
}

int main() {

  scanf("%d %d %d", &N, &M, &B);
  NM = N * M;

  for (int i = 0; i < NM; ++i)
    scanf("%d", A + i);  // &A[i]

  for (int h = 0; h < 257; ++h) {
    if (check(h))
      break;
  }

  printf("%d %d\n", ansTime, ansHeight);
  return 0;
}

