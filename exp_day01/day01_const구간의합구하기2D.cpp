/*
 * day02_const구간의합구하기2D.cpp
 *
 *  Created on: 2022. 12. 5.
 *      Author: bw
 */

#include <cstdio>
const int LM = 1000 + 10;
int arr[LM][LM];
long long sum[LM][LM];
int N, M;
int sr, sc, er, ec;
int input() {
  scanf("%d", &N);
  for (int yy = 1; yy <= N; yy++) {
    for (int xx = 1; xx <= N; xx++) {
      scanf("%d", &arr[yy][xx]);
      sum[yy][xx] = arr[yy][xx] + sum[yy - 1][xx] + sum[yy][xx - 1]
          - sum[yy - 1][xx - 1];
    }
  }

  scanf("%d", &M);
  return 0;
}

int main() {

  input();
//  printf("%d, %d: ", N, M);
  for (int i = 0; i < M; i++) {
//    printf("%d: ", i);
    scanf("%d %d %d %d", &sr, &sc, &er, &ec);

    const long long ans = sum[er][ec] - sum[sr - 1][ec] - sum[er][sc - 1]
        + sum[sr - 1][sc - 1];
    printf("%lld\n", ans);
  }
//  printf("done done\n");
  return 0;
}
