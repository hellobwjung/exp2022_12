/*
 * day02_진법변환1_4.cpp
 *
 *  Created on: 2023. 1. 14.
 *      Author: bw
 */
#include <cstdio>
using LL = long long;
char AS[128], BS[128];
LL A, B;
LL num;

int toNum(char c) {
  if (c >= 'A') {
    return c - 'A' + 10;
  }

  return c - '0';

}

LL toDec(char *as, int base) {
  LL dec = 0;
  for (int nn = 0; as[nn] != 0 && nn < 64; nn++) {
    int num = toNum(as[nn]);
//    printf("%c, %d\n", as[nn], num);
    dec = dec * base + num;
  }
//  puts("");

  return dec;

}
char str[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
void toB(LL dec, int base) {
  int nn = 0;
  while (dec) {
    const int mod = dec % base;
    BS[nn++] = str[mod];
    dec /= base;
  }
}

void strrev(char *str) {
  int len = 0;
  while (char c = str[len++])
    ;
//  printf("len = %d\n", len);
  len--;
  char t;
  for (int nn = 0; nn < len / 2; nn++) {
    t = str[nn];
    str[nn] = str[len - nn - 1];
    str[len - nn - 1] = t;
  }
  str[len] = 0;
}

int main() {
  while (1) {
    for (int nn = 0; nn < 128; nn++) {
      AS[nn] = 0;
      BS[nn] = 0;
    }
    scanf("%lld", &A);
    if (A == 0) {
      break;
    }
    scanf("%s %lld", AS, &B);
//    printf("AS = %s\n", AS);
    if (AS[0] == 0) {

    }

    if (AS[0] == '0') {
      printf("0\n");
      continue;
    }

    LL dec = toDec(AS, A);

    toB(dec, B);

    strrev(BS);
    printf("%s\n", BS);

  }

  return 0;
}

