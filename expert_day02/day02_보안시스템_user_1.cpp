/*
 * day02_보안시스템_user_1.cpp
 *
 *  Created on: 2022. 12. 6.
 *      Author: bw
 */

int table[4096];
int LM;

int ffs(int num) {
  for (int nn = 0; nn < 12; nn++) {
    if ((num >> nn) & 1)
      return nn + 1;

  }
  return 0;
}

int count1(int num) {
  int cnt = 0;
  for (int nn = 0; nn < 12; nn++) {
    if ((num >> nn) & 1)
      cnt++;
  }
  return cnt;

}

int encoding(int x, int y) {

  for (int nn = 0; nn < 4096, LM < 1; nn++) {

  }

  int k = (x ^ y) & x;
  return k + 1;
}
char answer(int p, int k) {

}
