/*
 * day01_합이_0에_가장_가까운구간찾기1_1.cpp
 *
 *  Created on: 2023. 1. 4.
 *      Author: bw
 */

#include<cstdio>

const int LM = 100'000 + 10;
int N;
int arr[LM], acc[LM];
long long sum;

void input() {
  scanf("%d", &N);
  int num = -1;
  for (int nn = 1; nn <= N; nn++) {

    scanf("%d", &num);
    sum += num;
    arr[nn] = num;
    acc[nn] = acc[nn - 1] + num;
  }

}

inline int abs(int x) {
  return x > 0 ? x : -x;
}

int main() {
  input();
  register int s = 1, e = N;
  long long ans = sum;
  int as = s, ae = e;
  while (s < e) {
    if (abs(ans) > abs(sum)) {
      ans = sum;
      as = s;
      ae = e;
    }

    if (sum == 0) {
      break;
    }

    if (sum > 0) {
      sum -= arr[e--];
    } else {
      sum -= arr[s++];
    }

  }

  printf("%lld\n%d %d", ans, as, ae);

  return 0;
}
