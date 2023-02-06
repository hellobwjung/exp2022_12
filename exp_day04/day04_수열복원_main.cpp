/*
 * day04_수열복원_main.cpp
 *
 *  Created on: 2022. 12. 8.
 *      Author: bw
 */

///====== main.cpp =====

#include <stdio.h>
#define MAXSIZE 100000

static int org[MAXSIZE], dat[MAXSIZE];
static int arrCount, QueryCount;

extern void array_restore(int arrCount, int dat[]);

// ISO9899
static unsigned long int next = 1;
int rand(void) // RAND_MAX assumed to be 65535
    {
  next = next * 1103515245 + 12345;
  return (unsigned int) (next >> 16) & 65535;
}

int orderCheck(int left, int right) {
  QueryCount++;
  if (left < 0 || left >= arrCount)
    return 1;
  if (right < 0 || right >= arrCount)
    return 1;
  if (org[left] < org[right])
    return 1;
  else
    return 0;
}

inline void Swap(int &a, int &b) {
  int t = a;
  a = b;
  b = t;
}

static void init(int t) {
  int i, j;
  QueryCount = 0;
  arrCount = (t * 2000 - 1000) + rand() % 1000;
  for (i = 0; i < arrCount; i++) {
    org[i] = i + 1;
    dat[i] = 0;
  }
  for (i = 0; i < arrCount; i++) {
    j = (int) ((long long) rand() * rand() % arrCount);
    Swap(org[i], org[j]);
  }
}

static int arr_comp() {
  if (QueryCount >= arrCount * 20)
    return MAXSIZE * 100;
  for (int i = 0; i < arrCount; i++) {
    if (org[i] != dat[i])
      return MAXSIZE * 100;
  }
  return QueryCount;
}

int main(void) {
  for (int tc = 1; tc <= 50; tc++) {
    init(tc);
    array_restore(arrCount, dat);
    printf("#%d %d %d\n", tc, arrCount, arr_comp());
  }

  return 0;
}
