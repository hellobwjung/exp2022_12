#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
 01_마인크래프트_ver02
 O(257*257)
 */
#include <cstdio>

const int LM = 257;  // LIMIT
int N, M, NM; // N(세로), M(가로), NM = N * M
int B;        // 인벤 정보
int cnt[LM];  // cnt[i] : 높이 i인 셀의 개수
int ansTime = 1 << 30, ansHeight;

int check(int tgH) {
  int timeCost = 0, inven = B;
  // tgH보다 낮은 자료에 대한 처리
  for (int i = 0; i < tgH; ++i) {
    int diff = tgH - i;
    inven -= diff * cnt[i];
    timeCost += diff * cnt[i];
  }

  // tgH보다 높은 자료에 대한 처리
  for (int i = tgH + 1; i < LM; ++i) {
    int diff = i - tgH;
    inven += diff * cnt[i];
    timeCost += diff * cnt[i] * 2;
  }

  if (inven < 0)  // 최종 결과가 음수라면
    return 1;

  if (timeCost <= ansTime) {
    ansTime = timeCost;
    ansHeight = tgH;
  }
  return 0;
}

int main() {
#ifdef _WIN32
    freopen("01.txt", "r", stdin);
#endif // _WIN32
  scanf("%d %d %d", &N, &M, &B);
  NM = N * M;
  int i, h;
  for (int i = 0; i < NM; ++i) {
    scanf("%d", &h);
    cnt[h]++;
  }

  for (int h = 0; h < 257; ++h) {
    if (check(h))
      break;
  }

  printf("%d %d\n", ansTime, ansHeight);
  return 0;
}
