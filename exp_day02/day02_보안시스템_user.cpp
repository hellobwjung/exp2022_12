/*
 * day02_보안시스템_user.cpp
 *
 *  Created on: 2022. 12. 6.
 *      Author: bw
 */

/// *** mysolution.cpp ***
int ffs(int bit) {

  for (int i = 0; i < 12; i++) {

    if ((bit >> i) & 1) {
      return i + 1;
    }
  }
  return 0;
}
int table[1000];
int count1(int d) {
  int cnt = 0;
  for (int nn = 0; nn < 12; nn++) {
    if ((d >> nn) & 1)
      cnt++;
  }
  return cnt;
}
void makeTable() {

  int idx = 0;
  for (int nn = 0; nn < 1024 * 4; nn++) {
    if (count1(nn) == 6) {
      table[idx++] = nn;
    }
  }

}

int encoding(int x, int y) {
  static int first = 0;
  if (first == 0) {
    makeTable();
    first = 1;
  }

  int xx = table[x];
  int yy = table[y];

  return ffs((xx ^ yy) & xx);

}
char answer(int p, int k) {
  int pp = table[p];

  if ((pp >> (k - 1)) & 1)
    return 'x';

  return 'y';
}

