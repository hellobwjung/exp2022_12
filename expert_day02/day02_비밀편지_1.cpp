/*
 * day02_비밀편지_1.cpp
 *
 *  Created on: 2022. 12. 6.
 *      Author: bw
 */

#include <cstdio>

char S[10000];

int code[] = { 0, 0x0f, 0b010011, 0b011100, 0b100110, 0b101001, 0b110101,
    0b111010 };
char ans[12];

int getLetter(int letter) {

  for (int nn = 0; nn < 8; nn++) {
    int bit = letter ^ code[nn];
    if ((bit & (bit - 1)) == 0)
      return nn;
  }
  return -1;
}

int main() {

  int N;
  scanf("%d", &N);
  for (int nn = 0; nn < N; nn++) {

    int letter = 0;
    for (int kk = 0; kk < 6; kk++) {
      int d;
      scanf("%1d", &d);
      letter = letter * 2 + d;
    }

    int rv = getLetter(letter);
    if (rv < 0) {
      printf("%d\n", nn + 1);
      return 0;
    }
    ans[nn] = rv + 'A';

  }
  puts(ans);

  return 0;
}
