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

void process1(unsigned char *freq) { // 좌우 반전
  for (int y = 0; y < 1000; y++)
    for (int x = 0; x < 500; x++) {
      unsigned char tmp = freq[y * 1000 + x];
      freq[y * 1000 + x] = freq[y * 1000 + (999 - x)];
      freq[y * 1000 + (999 - x)] = tmp;
    }
}

void process2(unsigned char *freq) { // 상하 반전
  for (int y = 0; y < 500; y++)
    for (int x = 0; x < 1000; x++) {
      unsigned char tmp = freq[y * 1000 + x];
      freq[y * 1000 + x] = freq[(999 - y) * 1000 + x];
      freq[(999 - y) * 1000 + x] = tmp;
    }
}

void process3(unsigned char *freq) { // J더하기
  for (int y = 0; y < 1000; y++)
    for (int x = 0; x < 1000; x++)
      freq[y * 1000 + x] += 'J';
//freq[1'000'000] =;
}

/// ***** user.cpp *****
void test(unsigned char *freq, const unsigned char *bitMap) {
  clear(freq);
  count(freq, bitMap);
  process1(freq);
  process2(freq);
  process3(freq);
}

#define rint register int
void compress(unsigned char *comp, const unsigned char *freq) {
  const int wh = 1000;
  rint i = 0, j = 0, x = 0, y = 0;

  const unsigned long long mymax = (1 << 64) - 1;
  int exp = 0;
  unsigned long long base = 1;
  while (base < mymax) {
    base *= 36;
    exp++;
  }

  base /= 36;
  exp--;

// comp every 6 digits
  int k = 0;
  unsigned long long *mycomp6 = (unsigned long long*) comp;
  for (rint idx = 0; idx < 1'000'000; idx += 6) {
    unsigned long long comp6 = 0;
    for (rint d = idx; d < idx + 6 && d < 1'000'000; d++) {
      comp6 = comp6 * 36 + freq[d] - 'J';
    }
    mycomp6[k++] = comp6;
  }

  printf("digit %d, base %llu, mymax %llu, k8 %d\n", exp, base, mymax, k * 8);
}

void decompress(unsigned char *freq, const unsigned char *comp) {
  int k = 0;
  unsigned long long *mycomp6 = (unsigned long long*) comp;
  for (rint idx = 0; idx < 1'000'000; idx += 6) {
    unsigned long long comp6 = mycomp6[idx];
    for (rint d = idx; d < idx + 6 && d < 1'000'000; d++) {
      const unsigned char val = comp6 % 36;
      freq[d] = val + 'J';
      comp6 /= 36;
    }
  }
}
