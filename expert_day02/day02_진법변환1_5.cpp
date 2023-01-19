/*
 * day02_진법변환1_5.cpp
 *
 *  Created on: 2023. 1. 14.
 *      Author: bw
 */

#include <cstdio>
using LL = long long;
int A, B;
char SA[128], BA[128];

int toNum(char c) {
  if (c >= 'A')
    return c - 'A' + 10;
  return c - '0';
}

LL toDec(char *SA, int A) {
  LL dec = 0;
  for (int nn = 0; SA[nn]; nn++) {
    dec = dec * A + toNum(SA[nn]);
  }
  return dec;
}

char str[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
void dec2B(LL dec, int base) {
  int len = 0;

  int nn = 0;
  while (1) {
    int mod = dec % base;
    if (dec == 0 && mod == 0) {

      break;
    }
    BA[nn++] = str[mod];
    dec /= base;
  }
  BA[nn] = 0;

}

int main() {
  while (scanf("%d %s %d", &A, SA, &B) && A) {
    LL dec = toDec(SA, A);
    dec2B(dec, B);
    printf("%s\n", BA);
  }

  return 0;
}
