/*
 * day10_EX_8퍼즐A_user_STL_ver1_1.cpp
 *
 *  Created on: 2022. 12. 16.
 *      Author: bw
 */

extern void move(int mode);

#include <cstdio>
#include <algorithm>
#include <unordered_map>
using namespace std;

#define rint register int

const int LM = 181440;
struct Data {
  int face, zeroPos, pathIdx, pathDir;
} que[LM + 5];
int fr, re;
unordered_map<int, int> hmap; // int:face, int: que's index
//////////////////////////////// hmap[face]= index
// 0이, 0~8위치에 있을, 상하좌우 인접한 위치, max4개까지 가

int adj[9][5] = { { 1, 3 }, { 0, 2, 4 }, { 1, 5 }, { 0, 4, 6 }, { 1, 3, 5, 7 },
    { 2, 4, 8 }, { 3, 7 }, { 4, 6, 8 }, { 5, 7 } };

// 0이 0~8위치에 있을 때, 상하좌우로 가는 방
int dir[9][5] = { { 3, 1 }, { 2, 3, 1 }, { 2, 1 }, { 0, 3, 1 }, { 0, 2, 3, 1 },
    { 0, 2, 1 }, { 0, 3 }, { 0, 2, 3 }, { 0, 2 } };

//             123,456,780  23,456,780  3,456,780
int dec[9] = { 100'000'000, 10'000'000, 1'000'000,
//  456,780  56,789  6,780
    100'000, 10'000, 1'000,
//  789  80  0
    100, 10, 1 };

void BFS() {
  que[re++] = { 123456780, 8 }; // face, zeroPos, pathIdx, pathDir
  const int key = 123456780, val = 0;
  hmap[key] = val;
  while (fr < re) {
    Data t = que[fr];
    int i = 0;
    do {
      const int newZeroPos = adj[t.zeroPos][i]; //0이 어디로 갈 수 있는가!!!!
      int val = t.face / dec[newZeroPos] % 10; //0이 이동할 위치에 있는 1~8의 숫자.
      // 0 을 이동시키
      int newFace = t.face - val * dec[newZeroPos] + val * dec[t.zeroPos];
      if (hmap.count(newFace) == 0) { // newFace가 이전에 만들어진 적이 없는지 확인,
        hmap[newFace] = re; // 새롭게 만들어진 수라면, 넣는데, 몇번째 인지를 넣어,
        que[re++] = { newFace, newZeroPos, fr, dir[t.zeroPos][i] ^ 1 }; // queue에다가 새로운 조합, 넣어
                                                                        // newFace, newZeroPos,
                                                                        // pathIdx(어디서 왔는지, 몇번째조합에서 왔는),
                                                                        // pathDir(되돌아 가려면 어느 방향으로 가야하는지)
      }

      i++;
    } while (adj[t.zeroPos][i]);

    ++fr;
  }

}

void test(const int puzzle[3][3]) {
  if (re == 0) {
    BFS();
  }

  int y, x, face = 0;
  for (y = 0; y < 3; y++) {
    for (x = 0; x < 3; x++) {
      face = face * 10 + puzzle[y][x];
    }
  }

  int idx = hmap[face];
  while (idx) {
    move(que[idx].pathDir);
    idx = que[idx].pathIdx;
  }

}
