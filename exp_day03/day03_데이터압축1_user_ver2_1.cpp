/*
 * day03_데이터압축1_user_ver1_3.cpp
 *
 *  Created on: 2023. 2. 11.
 *      Author: bw
 */

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
#define rint register int
const int CLM = 666'666;
const int FLM = 1'000'000;
const int BLM = 4'500'000;

void test(unsigned char *freq, const unsigned char *bitMap) {

//  clear(freq);
//  count(freq, bitMap);
//  process1(freq);
//  process2(freq);
//  process3(freq);

  int popcnt[64] = { 0 };
  rint idxb = 0, i = 0, j = 0, k = 0, c = 0;
  for (i = 1; i < 64; i++) { // i 가 가진 1인 비트의 갯수를 저장
    popcnt[i] = popcnt[i >> 1] + (i & 1);
  }

  for (i = 0; i < FLM; i++) {
    freq[i] = 'J'; // freq2생성
  }

  rint x = 0, y = 0;
  for (i = j = 0; i < BLM; i += 3) {
    // 8*3=24비트를 한번에 읽어오기
    rint k = 0;
//    k = ((int) bitMap[i] << 16) | (((int) bitMap[i + 1] << 8))
//        | ((int) bitMap[i + 2]);
    for (rint b = 2; b >= 0; b--) { // 8*3=24 bits
      k |= ((int) bitMap[i + 2 - b] << 8 * b);
    }

    // 180도 회젼 (상하좌우반) 하여 6bit 4개로 나누어 처이하기
    // 6000*6000 으로 만들어 행번호, 열번호 구하기
    // y = (i * 8) / 6000, x = (i * 8) % 6000
    // 180 도 회전하기:        y = 5999 - y, x = 5999- x
    // 1000 * 1000 으로 만들기: y = y / 6,    x = x / 6
    // 1000 * 1000 을 일차원 index로 만들기: idx = 1000 * y + x

    // 1. 6000 x 6000 grid, bit? byte? 단위?
    y = (i * 8) / 6000, x = (i * 8) % 6000;
    // 2. 180도 회전
    y = 5999 - y, x = 5999 - x;
    // 3. 1000 x 1000 grid 로 변환
    y /= 6, x /= 6;

    const rint idx = y * 1000 + x;
    freq[idx - 0] += popcnt[(k >> 18) & 63];
    freq[idx - 1] += popcnt[(k >> 12) & 63];
    freq[idx - 2] += popcnt[(k >> 06) & 63];
    freq[idx - 3] += popcnt[(k >> 00) & 63];
  }

}

void compress(unsigned char *comp, const unsigned char *freq) {
  rint idxc = 0, idxf = 0;
  const int c3737 = 37 * 37;
  for (idxf = 0; idxf < FLM - 1; idxf += 3) {
    rint code = ((freq[idxf] - 'J') * c3737) + ((freq[idxf + 1] - 'J') * 37)
        + (freq[idxf + 2] - 'J');
    comp[idxc++] = code >> 8;
    comp[idxc++] = code & 255;
  }
  comp[idxc] = freq[idxf];

}

void decompress(unsigned char *freq, const unsigned char *comp) {
  rint idxc = 0, idxf = 0;
  for (; idxc < 666666; idxc += 2) {
    rint code = (comp[idxc] << 8) | (comp[idxc + 1] & 255);
    freq[idxf + 2] = (code % 37) + 'J', code /= 37;
    freq[idxf + 1] = (code % 37) + 'J', code /= 37;
    freq[idxf + 0] = (code) + 'J';
    idxf += 3;
  }
  freq[idxf] = comp[idxc];
}

