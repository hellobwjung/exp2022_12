/*
 * day02_Bit_ImageMap3_user_ver1_1.cpp
 *
 *  Created on: 2023. 2. 6.
 *      Author: bw
 */

#define rint register int
using UI = unsigned int;

void write(char *str, int idx, int val) {
  *((UI*) (str + (idx / 8))) |= val << (idx & 7);
}

int read(char *str, int idx, int bitLen) {
  UI tg = *((UI*) (str + (idx / 8))) >> (idx & 7);
  const int mask = (1 << bitLen) - 1;
  return tg & mask;
}

/// ***** user.cppp *****

int encode(char *enc_str, char *str, int STRN) {

  int swCnt = 0;
  int sentenceWords[16384] = { 0 };
  int dcnt = 0;
  int dwLen[1025] = { 0 };
  long long dicWords[1025] = { 0 };
  rint idx = 0; // byte index
  rint wlen = 0;
  long long word = 0;
  rint i = 0, j = 0;
  // 1. 문장의 단어 갯수, 단어장의 갯수 구하기
  //    단어장을 만들자.

  for (i = 0; str[i]; i++) {
    if (str[i] == ' ') { // 단어가 완성 되었으면 !!!
      // 단어가 이미 들어가 있는 놈인지 linear search
      for (j = 0; j < dcnt; j++) {
        if (dicWords[j] == word) {
          break;
        }
      }
      if (j == dcnt) { // 없는 단어다. 등록하자
        dicWords[dcnt] = word;
        dwLen[dcnt++] = wlen;
      }
      sentenceWords[swCnt++] = j; // 문장의 단어 수 하나 증가.
      wlen = 0, word = 0;  // 단어, 단어의 길이 초기
    } else {
      word = word * 32 + str[i] - 96;
      wlen++;
    }
  }
  // 문장의 길이, 단어장의 길이 쓰자.
  idx = 0;
  write(enc_str, idx, dcnt), idx += 10;
  write(enc_str, idx, swCnt), idx += 14;

  // 2. 단어장 기록, (단어길이, 단)
  for (i = 0; i < dcnt; ++i) {
    long long w = dicWords[i];
    write(enc_str, idx, dwLen[i]), idx += 3; // 단어의 길이 ~ [1, 7]
    for (j = 0; j < dwLen[i]; ++j) {
      write(enc_str, idx, w % 32), idx += 5; // long long의 단어, 26 고바기,7, --> 32      x  8
      w /= 32;
    }
  }

  // 3. 문장의 단어를 단어장의 index로 저장
  for (i = 0; i < swCnt; i++) {
    write(enc_str, idx, sentenceWords[i]), idx += 10; //단어의 갯수, 최대 1024개 ~ 10bits

  }

  return (idx + 7) / 8;
}

void decode(char *dec_str, char *enc_str, int encn) {

  rint idx = 0, i = 0, j = 0;
  // 1. 단어장 길이, 단어의 갯수
  int dicSize = -1, senSize = -1;
  dicSize = read(enc_str, idx, 10), idx += 10;
  senSize = read(enc_str, idx, 14), idx += 14;

  // 2. 단어장 원복하자
  char dicStr[1025][8] = { 0 };
  int dicLen[1025];
  for (i = 0; i < dicSize; i++) {
    dicLen[i] = read(enc_str, idx, 3), idx += 3;

    for (j = dicLen[i] - 1; j >= 0; j--) {
      const int cidx = read(enc_str, idx, 5);
      idx += 5;
      const char c = cidx + 96;
      dicStr[i][j] = c;
    }
  }

  // 3. 단어 원복
  rint k = 0;
  for (i = 0; i < senSize; i++) {
    const int didx = read(enc_str, idx, 10);
    idx += 10;
    for (j = 0; j < dicStr[didx][j]; j++) {
      dec_str[k++] = dicStr[didx][j];
    }
    dec_str[k++] = ' ';
  }

}

