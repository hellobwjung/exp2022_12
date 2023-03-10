/*
 * day10_EX_8퍼즐B_main.cpp
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
extern void test(const int srcPuz[][3], const int destPuz[][3]);

using ULL = unsigned long long;
static ULL seed;
static ULL SCORE;

static inline unsigned short myRand(void) {
  seed = seed * 0x5DEECE66Dull + 11ull;
  return (unsigned short) (seed >> 16);
}

static int srcPuz[3][3], destPuz[3][3], ans[3][3], r, c;
static int dr[] = { -1, 1, 0, 0 }, dc[] = { 0, 0, -1, 1 };

void move(int dir) {
  int nr = r + dr[dir], nc = c + dc[dir];
  if (nr < 0 || nr > 2 || nc < 0 || nc > 2) {
    return;
  }
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
    for (int j = 0; j < 3; ++j)
      ans[i][j] = destPuz[i][j] = srcPuz[i][j];
  }
}

static void shuffle(int cnt) {
  for (int i = 0; i < cnt; ++i) {
    move(rand() % 4);
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
  int sd = 123455;
  //freopen("input.txt", "r", stdin);
  //scanf("%d %d", &sd, &TC);

  seed = sd;
  SCORE = 0;
  makeData();

  for (int tc = 0; tc < TC; tc++) {
    shuffle(1000);
    copyPuz();
    for (int i = 0; i < 10000; ++i) {
      shuffle(500);
      chrono::system_clock::time_point st = chrono::system_clock::now();
      test(srcPuz, destPuz);

      if (validate() == false)
        SCORE += 100000000;

      if (SCORE >= INF)
        break;
      chrono::system_clock::time_point et = chrono::system_clock::now();
      chrono::microseconds micro = chrono::duration_cast<chrono::microseconds>(
          et - st);

      SCORE += micro.count();
    }
  }

  printf("%lld\n", SCORE);

  if (SCORE < 100000)
    puts("PASS");
  else
    puts("FAIL");
  return 0;
}
