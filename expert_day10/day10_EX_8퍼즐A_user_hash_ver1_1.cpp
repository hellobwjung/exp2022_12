/*
 * day10_EX_8퍼즐A_user_hash_ver1_1.cpp
 *
 *  Created on: 2022. 12. 20.
 *      Author: bw
 */
#include <cstdio>
#include <unordered_map>
using namespace std;
/// ***** user.cpp *****
extern void move(int mode);

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

const int qlen = 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 + 10;
struct Data {
  int face, zeroPos, prevIdx, dir;
} que[qlen];
unordered_map<int, int> hmap;

inline int getFace(int p[3][3]) {
  int face = 0;
  for (register int yy = 0; yy < 3; yy++) {
    for (register int xx = 0; xx < 3; xx++) {
      face = face * 10 + p[yy][xx];
    }
  }
  return face;
}
void test(const int puzzle[3][3]) {
// If you modify the puzzle const data by bypassing it, you will be disqualified.

//  int face = getFace(puzzle);

}
