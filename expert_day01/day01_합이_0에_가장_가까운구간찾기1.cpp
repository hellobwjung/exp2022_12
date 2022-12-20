/*
 * day01_구간의합1.cpp
 *
 *  Created on: 2022. 12. 5.
 *      Author: bw
 */

#include <cstdio>
const int LM = 100000 + 10;
int N;
int arr[LM];
long long sum;

void input() {
  scanf("%d", &N);
  int in;
  for (int i = 1; i <= N; i++) {
    scanf("%d", &in);
    arr[i] = in;
    sum += in;
  }
}

inline long long abs(long long n) {
  return n > 0 ? n : -n;
}
;

int main() {

  input();

  int s = 1, e = N;
  int as = s, ae = e;
  long long ans = sum;

  while (s < e) {

    if (abs(sum) < abs(ans)) {
      ans = sum;
      as = s;
      ae = e;
    }
    if (sum == 0)
      break;
    if (sum < 0)
      sum -= arr[s++];
    else
      sum -= arr[e--];

  }
  printf("%lld\n", ans);
  printf("%d %d\n", as, ae);

  return 0;
}
