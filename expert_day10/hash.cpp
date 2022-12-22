/*
 * hash.cpp
 *
 *  Created on: 2022. 12. 22.
 *      Author: bw.jung
 */

typedef unsigned long long ull;
const int SIZE = 1 << 18; //2^18
const int LM = 1 << 10;

struct Hash {
  ull key;
  int value;
  Hash *next;

  Hash* alloc(ull _key, int _value, Hash *_next) {
    key = _key, value = _value, next = _next;
    return this;
  }

} hbuf[LM], *htab[SIZE];
int hcnt;

Hash* probing(ull key) {
  int hidx = key % SIZE;
  for (Hash *p = htab[hidx]; p->next != 0; p = p->next) {
    if (p->key == key)
      return p;
  }

  htab[hidx] = hbuf[hcnt++].alloc(key, 0, htab[hidx]);
  return htab[hidx];

}
