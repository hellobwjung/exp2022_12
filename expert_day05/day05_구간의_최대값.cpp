/*
 * day05_구간의_최대값.cpp
 *
 *  Created on: 2022. 12. 9.
 *      Author: bw
 */

#include <cstdio>

const int NMAX = 50000 + 10;
const int QMAX = 200000;
int N, Q;
int A[NMAX], B[NMAX];
int MOD = 256;

inline int max(int a, int b) {
  return a > b ? a : b;
}

inline int min(int a, int b) {
  return a < b ? a : b;
}

int query(int st, int ed) {

  int ret = -1;

  while (st <= ed && (st % MOD)) {
    ret = max(ret, A[st++]);
  }

  while (st <= ed && ((ed + 1) % MOD)) {
    ret = max(ret, A[ed--]);
  }

  for (; st <= ed; st += MOD) {
    ret = max(ret, B[st / MOD]);

  }

  return ret;

}

int main() {
  scanf("%d %d", &N, &Q);

  for (int nn = 0; nn < N; nn++) {
    int val;
    scanf("%d", &val);
    A[nn] = val;
  }

  // make B
  for (int nn = 0; nn < N; nn++) {
    B[nn / MOD] = max(B[nn / MOD], A[nn]);
  }

  int s, e;
  while (scanf("%d %d", &s, &e)) {
    int ret = query(s - 1, e - 1);

    if (ret > 0)
      printf("%d\n", ret);
    else {
      printf("cannot find max val");
      break;
    }
  }

  return 0;
}
