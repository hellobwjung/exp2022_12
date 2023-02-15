/*
 * day03_데이터압축1_user_ver2_4.cpp
 *
 *  Created on: 2023. 2. 15.
 *      Author: bw
 */
#include <cstdio>

void clear(unsigned char *freq) {
  for (int y = 0; y < 1000; y++)
    for (int x = 0; x < 1000; x++)
      freq[y * 1000 + x] = 0;
}

int sample(const unsigned char *bitMap, int x, int y) {
  unsigned char mask;

  if (((0 <= x) && (x <= 5999)) == 0)
    return -1;
  if (((0 <= y) && (y <= 5999)) == 0)
    return -1;

  mask = 0x80 >> (x % 8);

  x = x / 8;
  y = y * (6000 / 8);

  if ((bitMap[y + x] & mask) == mask)
    return 1;
  else
    return 0;
}

void add(unsigned char *freq, int x, int y) {
  if (((0 <= x) && (x <= 5999)) == 0)
    return;
  if (((0 <= y) && (y <= 5999)) == 0)
    return;

  x = x / 6;
  y = y / 6 * 1000;

  freq[y + x]++;
}

void count(unsigned char *freq, const unsigned char *bitMap) {
  for (int y = 0; y < 6000; y++)
    for (int x = 0; x < 6000; x++)
      if (sample(bitMap, x, y) == 1)
        add(freq, x, y);
}

void process1(unsigned char *freq) {
  for (int y = 0; y < 1000; y++)
    for (int x = 0; x < 500; x++) {
      unsigned char tmp = freq[y * 1000 + x];
      freq[y * 1000 + x] = freq[y * 1000 + (999 - x)];
      freq[y * 1000 + (999 - x)] = tmp;
    }
}

void process2(unsigned char *freq) {
  for (int y = 0; y < 500; y++)
    for (int x = 0; x < 1000; x++) {
      unsigned char tmp = freq[y * 1000 + x];
      freq[y * 1000 + x] = freq[(999 - y) * 1000 + x];
      freq[(999 - y) * 1000 + x] = tmp;
    }
}

void process3(unsigned char *freq) {
  for (int y = 0; y < 1000; y++)
    for (int x = 0; x < 1000; x++)
      freq[y * 1000 + x] += 'J';
}
const int FLM = 1'000'000;
const int BLM = 4'500'000;
const int CLM = 666'666;
void test(unsigned char *freq, const unsigned char *bitMap) {
//  clear(freq);
//  count(freq, bitMap);
//  process1(freq);
//  process2(freq);
//  process3(freq);

  for (int i = 0; i < FLM; i++) {
    freq[i] = 'J';
  }
  int popcnt[64] = { 0 };
  for (int i = 1; i < 64; i++) {
    popcnt[i] = popcnt[i >> 1] + (1 & i);
  }

  int x = 0, y = 0, idx = 0;
  int mask = (1 << 6) - 1;
  for (int i = 0; i < BLM; i += 3) {
    y = (i * 8) / 6000, x = (i * 8) % 6000;
    y = 5999 - y, x = 5999 - x;
    y /= 6, x /= 6;
    idx = y * 1000 + x;

    // 8 x 3 = 24bits씩 압축해서 1인 bit를 6개 단위로 cnt한다.
//    int val = ((int) bitMap[i] << 12) | ((int) bitMap[i + 1] << 6)
//        | ((int) bitMap[i + 2]);
    int val = ((int) bitMap[i] << 16) | ((int) bitMap[i + 1] << 8)
        | ((int) bitMap[i + 2]);

    freq[idx - 0] += popcnt[(val >> 18) & mask];
    freq[idx - 1] += popcnt[(val >> 12) & mask];
    freq[idx - 2] += popcnt[(val >> 06) & mask];
    freq[idx - 3] += popcnt[(val >> 00) & mask];

  }

}

void compress(unsigned char *comp, const unsigned char *freq) {
  const int c3737 = 37 * 37;
  int idxc = 0, idxf = 0;
  for (idxf = 0; idxf < FLM - 1; idxf += 3) {
    int val = ((int) freq[idxf] - 'J') * c3737
        + ((int) freq[idxf + 1] - 'J') * 37 + ((int) freq[idxf + 2] - 'J'); // 16bits max.
    comp[idxc++] = (val >> 8) & 255;
    comp[idxc++] = (val >> 0) & 255;
  }
  comp[idxc] = freq[idxf];
//  printf("%d, %d\n", idxf, idxc);
}

void decompress(unsigned char *freq, const unsigned char *comp) {

  int idxc = 0, idxf = 0;
  for (idxc = 0; idxc < CLM; idxc += 2) {
    int val = (((int) comp[idxc]) << 8) | ((int) (comp[idxc + 1] & 255));
    freq[idxf + 2] = 'J' + val % 37, val /= 37;
    freq[idxf + 1] = 'J' + val % 37, val /= 37;
    freq[idxf + 0] = 'J' + val % 37;
    idxf += 3;
  }

  freq[idxf] = comp[idxc];
//  printf("%d, %d\n", idxf, idxc);
}

/*
 *
 *
 *
 *
 *
 *
 *
 * */
