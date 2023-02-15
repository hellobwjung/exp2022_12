/*
 * day03_데이터압축1_user_ver1_2.cpp
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

void test(unsigned char *freq, const unsigned char *bitMap) {
  clear(freq);
  count(freq, bitMap);
  process1(freq);
  process2(freq);
  process3(freq);
}

#define rint register int
using UC = unsigned char;
const int LM = 1'000'000;
#if 1
void compress(unsigned char *comp, const unsigned char *freq) {
  rint idxf = 0, idxc = 0;
  const int c3737 = 37 * 37;
  for (idxf = 0; idxf < LM - 1; idxf += 3) {
    rint code = ((freq[idxf] - 'J') * c3737) + ((freq[idxf + 1] - 'J') * 37)
        + (freq[idxf + 2] - 'J');
    comp[idxc++] = code >> 8;
    comp[idxc++] = code & 255;
  }
  comp[idxc] = freq[idxf];
}
#else
void compress(unsigned char *comp, const unsigned char *freq) {
  rint i = 0;  // freq의 인덱스
  rint j = 0;  // comp의 인덱스
  for (; i < LM - 1; i += 3) {
    // 연속한 3개의 freq[]를 하나의 묶음으로 만들기
    rint code = (freq[i] - 74) * 37 * 37 + (freq[i + 1] - 74) * 37
        + (freq[i + 2] - 74);

    // 8비트씩 나누어 저장하기
    comp[j++] = code >> 8;
    comp[j++] = code % 256;
  }
  // 마지막 남은 1개는 그대로 담는다.
  comp[j] = freq[i];
}
#endif

#if 1
void decompress(unsigned char *freq, const unsigned char *comp) {
  rint idxf = 0, idxc = 0;
  for (; idxc < LM / 3 * 2; idxc += 2) {
    rint code = (comp[idxc] << 8) | (comp[idxc + 1]);
    freq[idxf + 2] = ((code % 37) + 'J'), code /= 37;
    freq[idxf + 1] = ((code % 37) + 'J'), code /= 37;
    freq[idxf + 0] = ((code) + 'J');
    idxf += 3;
  }
  freq[idxf] = comp[idxc];
}
#else
void decompress(unsigned char *freq, const unsigned char *comp) {
  rint i = 0; // freq의 인덱스
  rint j = 0; // comp의 인덱스

  // compress와 역순으로 수행한다.
  for (; j < 666666; j += 2) {
    rint code = (comp[j] << 8) | (comp[j + 1]);
    freq[i + 2] = code % 37 + 74, code /= 37;
    freq[i + 1] = code % 37 + 74, code /= 37;
    freq[i] = code + 74;
    i += 3;
  }
  // 마지막 남은 1개는 그대로 담는다.
  freq[i] = comp[j];
}
#endif

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
 * */
