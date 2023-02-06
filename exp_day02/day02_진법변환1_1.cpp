/*
 * day02_진법변환1_1.cpp
 *
 *  Created on: 2022. 12. 6.
 *      Author: bw
 */

#include <cstdio>

int A, B;
char S[100];
using LL = long long;

char toChar(int d) {
  if (d < 10)
    return d + '0';
  return d + 'A' - 10;

}

void dToB(LL d) {
  //base cond.
  if (d < B) {
    printf("%c", toChar(d));
    return;
  }

  // normal cond.
  dToB(d / B);
  printf("%c", toChar(d % B));
}

int main() {

  while (scanf("%d %s %d", &A, S, &B) && A) {
    // A to decimal
    LL d = 0;
    for (int i = 0; S[i]; i++) {
      if (S[i] < 'A') {
        d = d * A + (S[i] - '0');
      } else {
        d = d * A + (S[i] - 'A' + 10);
      }
    }

    // decimal to B
    dToB(d);
    puts("");
  }

  return 0;
}
