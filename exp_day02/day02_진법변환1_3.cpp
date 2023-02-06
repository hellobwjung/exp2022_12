/*
 * day02_진법변환1_3.cpp
 *
 *  Created on: 2022. 12. 6.
 *      Author: bw
 */

#include <cstdio>

int A, B;
char S[100];

char toChar(int d) {
  if (d < 10) {
    return d + '0';
  }
  return 'A' + d - 10;

}

void dec2B(int d) {
  if (d / B == 0) {
    printf("%c", toChar(d % B));
    return;
  }

  dec2B(d / B);
  printf("%c", toChar(d % B));
}

int main() {

  while (scanf("%d %s %d", &A, S, &B) && A) {
    // A to decimal
    int d = 0;
    for (int nn = 0; S[nn]; nn++) {
      if (S[nn] < 'A')
        d = d * A + (S[nn] - '0');
      else
        d = d * A + (S[nn] - 'A') + 10;
    }
    // decimal to B
    dec2B(d);
    puts("");

  }

  return 0;
}
