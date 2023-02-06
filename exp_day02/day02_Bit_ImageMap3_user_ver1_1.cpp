/*
 * day02_Bit_ImageMap3_user_ver1_1.cpp
 *
 *  Created on: 2023. 2. 6.
 *      Author: bw
 */

#define rint register int
using UI = unsigned int;

void write(char *str, int idx, int val) {
  *((UI*) str + (idx / 8)) |= val << (idx & 7);
}

int read(char *str, int idx, int bitLen) {
  UI tg = *((UI*) str + (idx / 8)) >> (idx & 7);
  const int mask = (1 << bitLen) - 1;
  return tg & mask;
}

/// ***** user.cppp *****
int encode(char *enc_str, char *str, int STRN) {
  rint idx;
  int senSize = 0;
  long long senStr[16384] = { 0 };
  int dicSize = 0;
  int dicLen[1025] = { 0 };
  char dicStr[1025][8] { 0 };
  // 1. 단어의 갯수, 단어장의 갯수 구하기
  for () {

  }

  // 2. 단어장 만들기, (단어길이, 단)

  // 3. 문장의 단어를 단어장의 index로 저장

  return 0;
}
void decode(char *dec_str, char *enc_str, int encn) {

}

