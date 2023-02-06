/*
 * day04_계수정렬_countingSort_user2.cpp
 *
 *  Created on: 2022. 12. 8.
 *      Author: bw
 */

/// *** user.cpp ***
const int LM = 1 << 20; //1048576
const int BIAS = 1 << 15;
const int CLM = 1 << 16;

int N;
int cnt[CLM];
int sortedArr[LM];
void countingSort(int arraySize, int *arr) {

  N = arraySize;
  int i, j;
  // 0. init cnt array
  for (int nn = 0; nn < CLM; nn++) {
    cnt[nn] = 0;
  }

  // 1.counting
  for (int nn = 0; nn < N; nn++) {
    cnt[arr[nn] += BIAS]++;
  }

  // 2. accumulate
  for (int nn = 1; nn < CLM; nn++) {
    cnt[nn] += cnt[nn - 1];
  }

  // 3. sort
  for (int nn = N - 1; nn >= 0; nn--) {
    sortedArr[--cnt[arr[nn]]] = arr[nn];

  }

}

int query(int idx) {
  return sortedArr[idx] - BIAS;
}
