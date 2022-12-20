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

const int div = 1000000000 + 7;

int main() {
  scanf("%d", &N);
  for (int nn = 0; nn < N; nn++) {
    scanf("%d", &A[nn]);
  }

  for (int b = 0; b < 32; b++) {
    int cnt1 = 0;
    int cnt0 = 0;

    for (int nn = 0; nn < N; nn++) {
      if ((A[nn] >> b) & 1)
        cnt1++;
    }
    cnt0 = N - cnt1;
    ans += ((long long) cnt0 * cnt1 * 2);
  }

  printf("%llu\n", ans % div);
//  printf("done done\n");

  return 0;
}

