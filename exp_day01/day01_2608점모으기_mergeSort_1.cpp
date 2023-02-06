/*
 * day01_2608점모으기_mergeSort_1.cpp
 *
 *  Created on: 2023. 1. 1.
 *      Author: bw
 */

#include <cstdio>
const int LM = 100005;
int N, M, ans;
int col[LM], row[LM], tmp[LM];
void print() {
  for (int nn = 0; nn <= M; nn++) {
    printf("[%02d] %2d, %2d\n", nn, row[nn], col[nn]);
  }
  puts("");

}
void input() {
  scanf("%d %d", &N, &M);
  for (int nn = 1; nn <= M; nn++) {
    scanf("%d %d", row + nn, col + nn);
  }
}
void mergeSort(int *arr, const int s, const int e) {
  // base condition
  if (s >= e) {
    return;
  }

  // divide and conquer
  int m = (e - s) / 2 + s;
  mergeSort(arr, s, m);
  mergeSort(arr, m + 1, e);

  // merge
  int left = s, right = m + 1;
  int k = s;
  while (left <= m && right <= e) {
    if (arr[left] < arr[right]) {
      tmp[k++] = arr[left++];
    } else {
      tmp[k++] = arr[right++];
    }
  }
  while (left <= m) {
    tmp[k++] = arr[left++];
  }
  while (right <= e) {
    tmp[k++] = arr[right++];
  }
  // copy
  for (int nn = s; nn <= e; nn++) {
    arr[nn] = tmp[nn];
  }
}

inline int abs(int a) {
  return a > 0 ? a : -a;
}
void getDistance() {
  ans = 0;
  int mr = row[(M + 1) / 2];
  int mc = col[(M + 1) / 2];
  for (int nn = 1; nn <= M; nn++) {
    ans += abs(mr - row[nn]);
    ans += abs(mc - col[nn]);
  }
}

int main() {
  input();
//  print();
  mergeSort(row, 1, M);
//  print();
  mergeSort(col, 1, M);
//  print();
  getDistance();

  printf("%d\n", ans);
  return 0;
}
