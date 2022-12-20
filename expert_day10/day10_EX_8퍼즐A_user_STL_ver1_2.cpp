/*
 * day10_EX_8퍼즐A_user_STL_ver1_2.cpp
 *
 *  Created on: 2022. 12. 20.
 *      Author: bw
 */

#include <unordered_map>
using namespace std;
extern void move(int mode);

struct Data {
  int face, zeroPos, prevHmapIdx, dir;
} queue[9 * 8 * 7 * 6 * 5 * 4 * 3];
int fr, re;

//  FACE         idx
// 1 2 3        0 1 2
// 4 5 6        3 4 5
// 7 8 0        6 7 8
//
// DIR
//             up  0(00)
// left 2(10)              right3 (11)
//            down 1(01)

const int adjIdx[9][5] = { { 1, 3 }, { 0, 2, 4 }, { 1, 5 }, //
    { 0, 4, 6 }, { 1, 3, 5, 7 }, { 2, 4, 8 }, //
    { 3, 7 }, { 4, 6, 8 }, { 5, 7 } };

const int U = 0, D = 1, L = 2, R = 3;
const int dir[9][5] = { { R, D }, { L, R, D }, { L, D }, //
    { U, R, D }, { U, L, R, D }, { U, L, D }, //
    { U, R }, { U, L, R }, { U, L } };
//int dir[9][5] = { { L, U }, { R, L, U }, { L, D }, //
//    { U, R, D }, { U, L, R, D }, { U, L, D }, //
//    { U, R }, { U, L, R }, { U, L } };
//              123,456,780, 23,456,780  3,456,780
int dec[10] = { 100'000'000, 10'000'000, 1'000'000, //
//  456,780  56,780  6,780
    100'000, 10'000, 1'000,
//  780  80  0
    100, 10, 1 };

unordered_map<int, int> hmap;
int face;

//void BFS() {
//
//  // enqueue
//  queue[re++] = { 123456780, 8 };
//
//  hmap[123456780] = 0; // 0번째, 즉, 제일 처음에, 넣는다, 여기까지 오면 길 찾는거임.
//
//  while (fr < re) {
//    // dequeue
//    Data d = queue[fr];
//    int zeroPos = d.zeroPos;
//    int i = 0;
//    do { // 한번 움직여 보자.
//      // 123456780  ->  123450786
//      //    123           123       012
//      //    456           450       345
//      //    780           786       678
//      const int newVal = (d.face / dec[adjIdx[zeroPos][i]]) % 10;
//      int newFace = d.face + newVal * dec[zeroPos] // 0 자리에 다가 바 녀석을 넣고
//      - newVal * dec[adjIdx[zeroPos][i]]; // 바꿀 자리에다가는 같은 수를 빼서 0으로 만든다.
////      if (re < 10)
////        printf("[%d]newFace: %d\n", re, newFace);
//
//      // enqueue next combination
//      if (hmap.count(newFace) == 0) { // 중복이 없으면,
//        hmap[newFace] = re;
//        queue[re++] = { newFace, adjIdx[zeroPos][i], fr, dir[zeroPos][i] ^ 1 };
//      }
//      i++;
//    } while (adjIdx[zeroPos][i]);
//    fr++;
//  }
//}
#define rint register int
void BFS() {
  queue[re++] = { 123456780, 8 };  // {123456780, 8, 0, 0}
  hmap[123456780] = 0;           // face가 123456780인 데이터는 que[0]에 있다.
  while (fr < re) {
    Data t = queue[fr];
    rint i = 0;
    do {
      rint newZeroPos = adjIdx[t.zeroPos][i];
      rint val = t.face / dec[newZeroPos] % 10;  // 0이 이동할 위치에 있는 1~8의 숫자 추출하기
      rint newFace = t.face - val * dec[newZeroPos] + val * dec[t.zeroPos]; // 0을 이동시키기
      if (hmap.count(newFace) == 0) {             // newFace가 이전에 만들어진적이 있는지 확인
        hmap[newFace] = re;                     // 새롭게 만들어진 수라면
        queue[re++] = { newFace, newZeroPos, fr, dir[t.zeroPos][i] ^ 1 };
      }
      i++;
    } while (adjIdx[t.zeroPos][i]);

    ++fr;
  }
}

int myface(const int p[3][3]) {
  // get face;
  int mface = 0;
  for (int y = 0; y < 3; y++) {
    for (int x = 0; x < 3; x++) {
      mface = mface * 10 + p[y][x];
    }
  }
  return mface;
}

void test(const int puzzle[3][3]) {

  if (re == 0) {
    BFS();
//    printf("once!!\n\n");
  }

  // get face;
  face = 0;
  for (int y = 0; y < 3; y++) {
    for (int x = 0; x < 3; x++) {
      face = face * 10 + puzzle[y][x];
    }
  }

  int cnt = 0;
  while (hmap[face]) {

    int order = hmap[face];

    const Data d = queue[order];
    move(d.dir);
    face = queue[d.prevHmapIdx].face; // update
    cnt++;
  }

//  printf("face=%d, mface=%d, cnt=%d \n", face, myface(puzzle), cnt);

//  printf("done done, hmap.size() = %d\n", hmap.size());
}
// 420
// 713
// 856

// 402  420
// 713  713
// 856  856
