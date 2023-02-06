/*
 * day02_비밀편지_2.cpp
 *
 *  Created on: 2023. 1. 14.
 *      Author: bw
 */

#include <cstdio>

/*
 A 000000​
 B 001111
 C 010011
 D 011100
 E 100110
 F 101001
 G 110101
 H 111010
 */

int binary[10] = { 0b000000/*A*/, 0b001111/*B*/, 0b010011/*C*/, 0b011100/*D*/,
    0b100110/*E*/, 0b101001/*F*/, 0b110101/*G*/, 0b111010 /*H*/};
char letter[] = "ABCDEFGH";

const int LM = 10 + 2;
int N;
int mystr[LM];
char num2char[64];

void input() {
  scanf("%d", &N);
  for (int nn = 0; nn < N; nn++) {
    int mychar = 0;
    for (int kk = 0; kk < 6; kk++) {
      int bit = 0;
      scanf("%1d", &bit);
      mychar = mychar * 2 + bit;
    }
    mystr[nn] = mychar;
  }

  for (int nn = 0; nn < 64; nn++) {
    num2char[nn] = 'x';
  }
  for (int nn = 0; nn < 8; nn++) {
    printf("%c%d ", letter[nn], binary[nn]);
    num2char[binary[nn]] = letter[nn];
  }
  printf("num2char = %s\n", num2char);

}

char pstr[16];
void print() {

  int nn = 0;
  for (nn = 0; nn < N; nn++) {
    int b = mystr[nn];
    printf("b=%d,  ", b);
    if (num2char[b] == 'x') {
      printf("%d\n", nn + 1);
      return;
    }

    pstr[nn] = num2char[b];
  }
//  puts("");
  pstr[nn] = 0;
  printf("%s\n", pstr);
//  for (nn = 0; nn < N; nn++) {
//
//  }
}

int main() {
  input();
  print();

  return 0;
}

