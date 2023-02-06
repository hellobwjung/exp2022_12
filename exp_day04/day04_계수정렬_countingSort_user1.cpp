/*
 * day04_계수정렬_countingSort_user.cpp
 *
 *  Created on: 2022. 12. 8.
 *      Author: bw
 */

/// *** user.cpp ***
const int LM = 1 << 20;
const int CLM = 1 << 16;
const int BIAS = 1 << 15;
int N, cnt[CLM], sorted[LM];

void countingSort(int arraySize, int *arr) {
  int N = arraySize;

  // COUNT
  for (int nn = 0; nn < N; nn++) {
    cnt[arr[nn] + BIAS]++;
  }

  // SORT
  for (int nn = 0, kk = 0; nn < CLM; nn++) {
    while (cnt[nn]--) {
      sorted[kk++] = nn;
    }
  }
}

int query(int idx) {
  return sorted[idx] - BIAS;
}
