/*
 * day02_비트연산1.cpp
 *
 *  Created on: 2022. 12. 6.
 *      Author: bw
 */

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
 08_비트연산1
 */
#include <stdio.h>

char op[7][4] = { "?", "~", "&", "|", "^", "<<", ">>" };

int main() {
  printf("%s\n", op[2]);                   /// (1)
  printf("%s%s\n", op[1], op[2]);          /// (2)
  printf("%s\n", op[5]);                   /// (3)
  printf("%s%s%s\n", op[6], op[2], op[5]); /// (4)
  printf("%s%s%s\n", op[4], op[4], op[4]); /// (5)
  printf("%s%s\n", op[6], op[2]);          /// (6)
  printf("%s%s%s\n", op[2], op[1], op[5]); /// (7)
  printf("%s%s\n", op[4], op[5]);          /// (8)
  printf("%s\n", op[2]);                   /// (9)
  printf("%s%s\n", op[4], op[2]);          /// (10)

  return 0;
}

