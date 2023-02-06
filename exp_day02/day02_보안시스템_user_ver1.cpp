/*
 * day02_보안시스템_user_ver1.cpp
 *
 *  Created on: 2022. 12. 6.
 *      Author: bw
 */

/*
 11_보안 시스템_user_ver01
 */
const int LM = 920;
int N, entry[LM + 5];

int popCount(int val) {
  int pc = 0;
  while (val) {
    pc += val & 1;
    val /= 2;
  }
  return pc;
}

int ffs(int bit) {
  for (int i = 0; i < 12; ++i) {
    if ((bit >> i) & 1)
      return i + 1;
  }
  return 0;
}

int encoding(int x, int y) {
  // 1인 비트가 6개인 수들을 구하기
  for (int i = 63; N < LM; ++i) {
    if (popCount(i) == 6)
      entry[++N] = i;
  }
  int rv = ffs((entry[x] ^ entry[y]) & entry[x]);
  return rv;
}

char answer(int p, int k) {
  if ((entry[p] >> (k - 1)) & 1)
    return 'x';
  return 'y';
}

