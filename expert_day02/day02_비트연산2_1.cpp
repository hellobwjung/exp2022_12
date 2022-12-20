/*
 * day02_비트연산2.cpp
 *
 *  Created on: 2022. 12. 6.
 *      Author: bw
 */

#include <cstdio>

int N;
int A[100000 + 100];
unsigned long long ans;
int cnt[32];

const int div = 1000000000 + 7;

int main() {
  scanf("%d", &N);
  for (int nn = 0; nn < N; nn++) {
    scanf("%d", &A[nn]);

    for (int b = 0; b < 32; b++) {
      if ((A[nn] >> b) & 1)
        cnt[b]++;
    }
  }

  for (int b = 0; b < 32; b++) {
    ans += ((long long) cnt[b] * (N - cnt[b]) * 2);
  }

  printf("%llu\n", ans % div);

  return 0;
}

