/*
 * day03_데이터압축1_user_ver2_2.cpp
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

  int x = 0, y = 0, j = 0;
  for (int i = 0; i < BLM; i += 3) {
    // 8*3 =24 bits, data  꺼내서, 6*4개 쓰자. freq에
    int k = 0;
    k = (((int) bitMap[i]) << 16) | (((int) bitMap[i + 1]) << 8)
        | (((int) bitMap[i + 2]));

    // 180도 회전(상하좌우반전), 하여 6bit 4개로 나누어 처리하기.
    // 1. 6000 x 6000 으로 만들어 행번호, 열번호 구하기
    //    y = (i*8)/6000, x = (i*8)/6000
    // 2. 180도 회전하기
    //    y = 5999 - y, x = 5999 - x
    // 3. 1000 x 1000으로 만들기
    //    y = y / 6, x = x / 6
    // 4. 1000 x 1000을 일차원으로 index만들기
    //    idx = 1000*y + x
    y = (i * 8) / 6000, x = (i * 8) % 6000; // bit 단위, byte에서 x8 했으니까
                                            // 4,500,000 x 8 = 36,000,000
    y = 5999 - y, x = 5999 - x;             // 180도 회전.
    y /= 6, x /= 6;
    const int idx = 1000 * y + x;
    freq[idx - 0] += popcnt[(k >> 18) & 63];
    freq[idx - 1] += popcnt[(k >> 12) & 63];
    freq[idx - 2] += popcnt[(k >> 06) & 63];
    freq[idx - 3] += popcnt[(k >> 00) & 63];

  }

}

void compress(unsigned char *comp, const unsigned char *freq) {

  int i = 0, j = 0, k = 0;
  const int c3737 = 37 * 37;
  for (i = 0; i < FLM - 1; i += 3) {
    const int num = (freq[i] - 'J') * c3737 + (freq[i + 1] - 'J') * 37
        + (freq[i + 2] - 'J');
    comp[k++] = num >> 8;
    comp[k++] = num & 255;
  }
  comp[k] = freq[i];
//  printf("comp, %d, %d\n", k, i);
}

void decompress(unsigned char *freq, const unsigned char *comp) {
  int i = 0, j = 0, k = 0;
  for (i = 0; i < CLM; i += 2) {
    int cn = comp[i] << 8 | comp[i + 1];
    freq[k + 2] = 'J' + (cn % 37), cn /= 37;
    freq[k + 1] = 'J' + (cn % 37), cn /= 37;
    freq[k + 0] = 'J' + (cn % 37);
    k += 3;
  }
  freq[k] = comp[i];
//  printf("decomp, %d, %d\n", k, i);
}
/*
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * */
