/*
 * day05_구간의_최대값_ver3.cpp
 *
 *  Created on: 2022. 12. 9.
 *      Author: bw
 */

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
 20_구간의 최대값1_ver03
 segment tree
 */
#include <cstdio>

const int LM = 50005;
const int TLM = 1 << 17; // 131072

int N, Q;
int tree[TLM];

int max(int a, int b) {
  return a > b ? a : b;
}
void build(int node, int s, int e) {
  if (s >= e) {  // leaf node
    scanf("%d", &tree[node]);
    return;
  }
  int m = (s + e) / 2, lch = node * 2, rch = lch + 1;
  build(lch, s, m);
  build(rch, m + 1, e);
  tree[node] = max(tree[lch], tree[rch]);
}

int query(int node, int s, int e, int qs, int qe) {
  if (e < qs || qe < s)
    return -1;           // 겹치는 구간이 없는 경우
  if (qs <= s && e <= qe)
    return tree[node]; // 트리구간 <= 쿼리구간
  int m = (s + e) / 2, lch = node * 2, rch = lch + 1;
  int leftMax = query(lch, s, m, qs, qe);
  int rightMax = query(rch, m + 1, e, qs, qe);
  return max(leftMax, rightMax);
}

int main() {
#ifdef _WIN32
    freopen("20.txt", "r", stdin);
#endif // _WIN32
  scanf("%d %d", &N, &Q);
  build(1, 1, N);
  int i, s, e;
  for (i = 0; i < Q; ++i) {
    scanf("%d %d", &s, &e);
    printf("%d\n", query(1, 1, N, s, e));
  }

  return 0;
}
