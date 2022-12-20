/*
 * day02_비밀편지.cpp
 *
 *  Created on: 2022. 12. 6.
 *      Author: bw
 */

#include <cstdio>

char S[10000];

int code[] = { 0, 0x0f, 0b010011, 0b011100, 0b100110, 0b101001, 0b110101,
    0b111010 };
char ans[12];

int getChar(int d) {

  for (int n = 0; n < 8; n++) {
    int bit = code[n] ^ d;
    if ((bit & (bit - 1)) == 0) {
      return n;
    }

  }

  return -1;

}

int main() {

  int N, i, j, d, a;
  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    d = 0;
    for (int j = 0; j < 6; j++) {
      scanf("%1d", &a);
      d = d * 2 + a;
    }
    int rv = getChar(d);
    if (rv < 0) {
      printf("%d\n", i + 1);
      return 0;
    }
    ans[i] = rv + 'A';
  }

  puts(ans);
  return 0;

}
