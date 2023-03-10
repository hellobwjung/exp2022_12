/*
 * day10_EX_8퍼즐F_main.cpp
 *
 *  Created on: 2022. 12. 16.
 *      Author: bw
 */

/// ***** main.cpp *****
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include  <stdio.h>
#include  <string.h>
#include  <time.h>
#include  <chrono>
using namespace std;

const int INF = 100000000;
extern int test(const int srcPuz[][3], const int destPuz[][3]);

using ULL = unsigned long long;
static ULL seed;
static ULL SCORE;
static int moveCnt;

static inline unsigned short myRand(void) {
  seed = seed * 0x5DEECE66Dull + 11ull;
  return (unsigned short) (seed >> 16);
}

static int srcPuz[3][3] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
static int destPuz[3][3], ans[3][3], r, c;
static int dr[] = { -1, 1, 0, 0 }, dc[] = { 0, 0, -1, 1 };

void move(int dir) {
  if (moveCnt < 0)
    return;
  int nr = r + dr[dir], nc = c + dc[dir];
  if (nr < 0 || nr > 2 || nc < 0 || nc > 2) {
    moveCnt = -2;
    return;
  }
  moveCnt++;
  srcPuz[r][c] = srcPuz[nr][nc];
  srcPuz[r = nr][c = nc] = 0;
}

static void makeData() {
  for (int i = 0; i < 9; ++i) {
    srcPuz[i / 3][i % 3] = i;
  }
  r = c = 0;
}

static void copyPuz() {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      ans[i][j] = destPuz[i][j] = srcPuz[i][j];
    }
  }
}

static void shuffle(int cnt) {
  for (int i = 0; i < cnt; ++i) {
    int a = myRand() % 9, r = a / 3, c = a % 3;
    int b = myRand() % 9, nr = b / 3, nc = b % 3;
    int t = srcPuz[r][c];
    srcPuz[r][c] = srcPuz[nr][nc];
    srcPuz[nr][nc] = t;
  }
}

void findZero() {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (srcPuz[i][j] == 0) {
        r = i, c = j;
        return;
      }
    }
  }
}

static bool validate() {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (srcPuz[i][j] != ans[i][j])
        return false;
    }
  }
  return true;
}

int main() {
  int TC = 10;
  int sd = 10101;
  // freopen("input.txt", "r", stdin);
  // scanf("%d %d", &TC, &sd);

  seed = sd;
  SCORE = 0;

  long long userAns = 0;
  for (int tc = 0; tc < TC; tc++) {
    for (int i = 0; i < 10000; ++i) {
      shuffle(50);
      copyPuz();
      shuffle(50);

      findZero();
      moveCnt = 0;

      chrono::system_clock::time_point st = chrono::system_clock::now();
      int res = test(srcPuz, destPuz);
      if (res < 0)
        res = -1;

      if (res >= 0) {
        if (res != moveCnt || validate() == false)
          SCORE = 100000000;
        else
          userAns += res;
      }

      if (SCORE >= INF)
        break;
      chrono::system_clock::time_point et = chrono::system_clock::now();
      chrono::microseconds micro = chrono::duration_cast<chrono::microseconds>(
          et - st);

      SCORE += micro.count();
    }
  }

  long long ans = 727217;
  //scanf("%lld", &ans);

  if (ans != userAns)
    SCORE = 100000000;

  //printf("%lld\n", userAns);
  //printf("%lld\n", SCORE);

  if (SCORE < 500000)
    puts("PASS");
  else
    puts("FAIL");
  return 0;
}
