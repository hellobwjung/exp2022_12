/*
 * day04_기수정렬_radixSort_user.cpp
 *
 *  Created on: 2022. 12. 8.
 *      Author: bw
 */

/// ***** user.cpp *****
/// 배열 A와 원소의 개수 N을 전달받아 초기화한다.
const int LM = 25e6 + 10;
const int MSB = 1 << 31;
const int BASE = 8;
const int MOD = 1 << BASE;
const int MASK = MOD - 1;

#define rint register int

int sortedArr[LM];
int cnt[MOD];
void initUser(int nSize, int *arr) {
  rint N = nSize;
  rint nn, kk;
  int *ap = sortedArr, *t;
  int *bp = arr;

  // MSB flip
  for (nn = 0; nn < N; nn++) {
    ap[nn] = bp[nn] ^ MSB;
  }

  // radix sort;
  for (int nn = 0; nn < 32; nn += 8) {
    // 0. init;
    for (int kk = 0; kk < MOD; kk++) {
      cnt[kk] = 0;
    }

    // 1. count
    for (int kk = 0; kk < N; kk++) {
      cnt[(ap[kk] >> nn) & MASK]++;
    }

    // 2. accumulate
    for (int kk = 1; kk < MOD; kk++) {
      cnt[kk] += cnt[kk - 1];
    }

    // 3. sort
    for (int kk = N - 1; kk >= 0; kk--) {
      bp[--cnt[(ap[kk] >> nn) & MASK]] = ap[kk];
    }
    t = ap, ap = bp, bp = t;

  }

}

/// " A 배열을 오름차순 정렬했을때 idx번째 값은 얼마인가? "
/// 라는 질의에 실시간으로 답하는 함수이다.
int query(int idx) {
  return sortedArr[idx - 1] ^ MSB;
}
