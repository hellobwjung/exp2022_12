/*
 * day02_보안시스템_main.cpp
 *
 *  Created on: 2022. 12. 6.
 *      Author: bw
 */

/*
 Template Code
 */

/// *** manager.cpp ***
#include <stdio.h>

extern int encoding(int x, int y);
extern char answer(int q, int h);

static int score() {
  int krr[5] = { 0 }, max_k = 0;
  int scoreTable[] = { 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
      100, 100, 75, 60, 50, 42, 34, 33, 30, 27, 0 };

  krr[0] = encoding(1, 2);
  if (krr[0] <= 0)
    return 0;
  if (answer(1, krr[0]) != 'x')
    return 0;

  krr[1] = encoding(4, 5);
  if (krr[1] <= 0)
    return 0;

  if (answer(2, krr[0]) != 'y')
    return 0;

  if (answer(4, krr[1]) != 'x')
    return 0;

  krr[2] = encoding(5, 2);
  if (krr[2] <= 0)
    return 0;

  if (answer(2, krr[2]) != 'y')
    return 0;

  for (int i = 0; i < 3; ++i) {
    if (max_k < krr[i])
      max_k = krr[i];
  }

  if (max_k >= 21)
    max_k = 21;
  return scoreTable[max_k];
}

int main() {
  printf("%d", score());
  return 0;
}

