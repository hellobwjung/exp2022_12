/*
 * day03_데이터압축1_user_ver2_3.cpp
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
    popcnt[i] = popcnt[i >> 1] + (i & 1);
  }

  int y = 0, x = 0, idx = 0, idxf = 0;
  const int mask = (1 << 6) - 1;
  for (int i = 0; i < BLM; i += 3) {
    // idx 구하기 6000 x 6000 bit단위로
    y = (i * 8) / 6000, x = (i * 8) % 6000;
    y = 5999 - y, x = 5999 - x;
    y /= 6, x /= 6;
    idx = 1000 * y + x;

    // 8*3=24bits 개씩 모아서 기록
    int val = ((int) bitMap[i] << 16) | ((int) bitMap[i + 1] << 8)
        | ((int) bitMap[i + 2]);
    // 6 x 4 개씩 나우어 카운팅
    freq[idx - 0] += popcnt[(val >> 18) & (mask)];
    freq[idx - 1] += popcnt[(val >> 12) & (mask)];
    freq[idx - 2] += popcnt[(val >> 06) & (mask)];
    freq[idx - 3] += popcnt[(val >> 00) & (mask)];
  }

}

void compress(unsigned char *comp, const unsigned char *freq) {

// 3개가 2개가 되어야 66.66%
  int idxf = 0, idxc = 0;
  const int c3737 = 37 * 37;
  for (idxf = 0; idxf < FLM - 1; idxf += 3) {
    const int val = ((freq[idxf] - 'J') * c3737) + ((freq[idxf + 1] - 'J') * 37)
        + (freq[idxf + 2] - 'J');
    comp[idxc++] = val >> 8;
    comp[idxc++] = val & 255;
  }
  comp[idxc] = freq[idxf];

//  printf("comp[%d]=%d, freq[%d]=%d\n", idxc, comp[idxc], idxf, freq[idxf]);

}

void decompress(unsigned char *freq, const unsigned char *comp) {
// 2개가 3개가 되어야 복
  int idxf = 0, idxc = 0;
  for (; idxc < CLM; idxc += 2) {
    int val = comp[idxc] << 8 | (comp[idxc + 1] & 255);
    freq[idxf + 2] = 'J' + (val % 37), val /= 37;
    freq[idxf + 1] = 'J' + (val % 37), val /= 37;
    freq[idxf + 0] = 'J' + (val % 37);
    idxf += 3;
  }
  freq[idxf] = comp[idxc];
//  printf("comp[%d]=%d, freq[%d]=%d\n", idxc, comp[idxc], idxf, freq[idxf]);
}

