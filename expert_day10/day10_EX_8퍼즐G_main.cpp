/*
 * day10_EX_8퍼즐G_main.cpp
 *
 *  Created on: 2022. 12. 16.
 *      Author: bw
 */

ng.h>
#include <chrono>

static int puzzle[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
static int zeroRowIndex = 2;
static int zeroColIndex = 2;

//////////////////////////////////////////////////
extern void test(const int puzzle[3][3]);
//////////////////////////////////////////////////

static unsigned long long seed = 55;
static int userMoveCnt;

static inline int myRand(void) {
  seed = seed * 25214903917ULL + 11ULL;
  return (seed >> 16) & 0x7fffffff;
}

void move(int dir) {
  switch (dir) {
  case 0: // from top to bottom
    if (zeroRowIndex != 0) {
      puzzle[zeroRowIndex][zeroColIndex] =
          puzzle[zeroRowIndex - 1][zeroColIndex];
      zeroRowIndex--;
      puzzle[zeroRowIndex][zeroColIndex] = 0;
      userMoveCnt++;
    }
    return;
  case 1: // from bottom to top
    if (zeroRowIndex != 2) {
      puzzle[zeroRowIndex][zeroColIndex] =
          puzzle[zeroRowIndex + 1][zeroColIndex];
      zeroRowIndex++;
      puzzle[zeroRowIndex][zeroColIndex] = 0;
      userMoveCnt++;
    }
    return;
  case 2: // from left to right
    if (zeroColIndex != 0) {
      puzzle[zeroRowIndex][zeroColIndex] =
          puzzle[zeroRowIndex][zeroColIndex - 1];
      zeroColIndex--;
      puzzle[zeroRowIndex][zeroColIndex] = 0;
    }
    return;
  case 3: // from right to left
    if (zeroColIndex != 2) {
      puzzle[zeroRowIndex][zeroColIndex] =
          puzzle[zeroRowIndex][zeroColIndex + 1];
      zeroColIndex++;
      puzzle[zeroRowIndex][zeroColIndex] = 0;
      userMoveCnt++;
    }
    return;
  }
}

int main() {
//#ifdef _WIN32
//    freopen("input.txt", "r", stdin);
//#endif // _WIN32

  int sd = 555;
  //scanf("%d", &sd);
  seed = sd;

  unsigned long long SCORE = 0;
  for (int tc = 0; tc < 10000; tc++) {
    for (int c = 0; c < 500; c++) {
      move(myRand() % 4);
    }

    std::chrono::system_clock::time_point start =
        std::chrono::system_clock::now();
    test (puzzle);
    std::chrono::system_clock::time_point end =
        std::chrono::system_clock::now();
    SCORE += (int) std::chrono::duration_cast<std::chrono::microseconds>(
        end - start).count();

    int num = 1;
    for (int r = 0; r < 3; r++) {
      for (int c = 0; c < 3; c++) {
        if (puzzle[r][c] != num++) {
          SCORE += 100000000;
          tc = 10000;
        }
        if (num == 9) {
          num = 0;
        }
      }
    }
  }

  int ansMoveCnt = 2663898;
  //scanf("%d", &ansMoveCnt);
  if (userMoveCnt != ansMoveCnt)
    SCORE += 100000000;

  //printf("%d\n", userMoveCnt);
  //printf("SCORE: %lld\n", SCORE);

  if (SCORE < 1500000)
    puts("PASS");
  else
    puts("FAIL");

  return 0;
}

