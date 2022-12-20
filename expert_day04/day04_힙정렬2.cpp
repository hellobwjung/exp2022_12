/*
 * day04_힙정렬2.cpp
 *
 *  Created on: 2022. 12. 8.
 *      Author: bw
 */

#include <cstdio>

int N;
int heap[500000 + 100];
int hn;

inline void swap(int &a, int &b) {
  int t = a;
  a = b;
  b = t;
}

void push_heap(int num) {
  heap[++hn] = num;

  for (int c = hn; c > 1; c /= 2) {
    if (heap[c] > heap[c / 2]) {
      swap(heap[c], heap[c / 2]);
    } else {
      break;
    }

  }
}

int pop_heap() {
  int val = heap[1];
  swap(heap[1], heap[hn--]);
  for (int c = 2; c <= hn; c *= 2) {
    if (c < hn && heap[c + 1] > heap[c])
      c++;

    if (heap[c] > heap[c / 2]) {
      swap(heap[c], heap[c / 2]);
    } else
      break;
  }

  return val;
}

int main() {

  scanf("%d", &N);
//  printf("%d\n", N);
  for (int nn = 0; nn < N; nn++) {
    int num;
    scanf("%d", &num);
    push_heap(num);
  }
  for (int nn = 1; nn <= N; nn++) {
    printf("%d ", heap[nn]);
  }
  printf("\n");
  for (int nn = 0; nn < N; nn++) {
    pop_heap();
  }

  for (int nn = 1; nn <= N; nn++) {
    printf("%d ", heap[nn]);
  }

//  printf("done done");

  return 0;
}
