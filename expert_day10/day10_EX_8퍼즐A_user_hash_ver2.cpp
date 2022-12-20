/*
 * day10_EX_8퍼즐A_user_hash_ver2.cpp
 *
 *  Created on: 2022. 12. 16.
 *      Author: bw
 */

/*
 38_EX_8퍼즐A_user_BFS_ver02
 nonSTL : custom queue + custom hash
 array chaining
 */
extern void move(int mode);

#define rint register int

const int LM = 181440 + 5;
const int MOD = 1 << 18;
struct Data {
  int face, zp, pathIdx, pathDir;
} que[LM], t;
int fr, re;

struct Hash {
  int st[MOD], link[LM];
  int probing(int face) {
    rint hidx = face % MOD, i = st[hidx];
    for (; i && que[i].face != face; i = link[i])
      ;
    return i;
  }
  void insert(int face, int np) {
    int hidx = face % MOD;
    link[np] = st[hidx], st[hidx] = np;
  }
} hmap;

int decimal[] = { 100'000'000, 10'000'000, 1'000'000, 100'000, 10'000, 1'000,
    100, 10, 1 };
int adj[][5] = { { 1, 3 }, { 0, 2, 4 }, { 1, 5 }, { 0, 4, 6 }, { 1, 3, 5, 7 }, {
    2, 4, 8 }, { 3, 7 }, { 4, 6, 8 }, { 5, 7 } };
int dir[][5] = { { 3, 1 }, { 2, 3, 1 }, { 2, 1 }, { 0, 3, 1 }, { 0, 2, 3, 1 }, {
    0, 2, 1 }, { 0, 3 }, { 0, 2, 3 }, { 0, 2 } };

void BFS() {
  fr = re = 1;
  que[re++] = { 123456780, 8, 0, 0 };
  hmap.insert(123456780, 1);
  while (fr < re) {
    t = que[fr];
    rint face = t.face;            // current face
    rint czp = t.zp;               // current zero pos
    rint i = 0;                    // adj index
    do {
      rint nzp = adj[czp][i];    // next zero pos
      rint val = face / decimal[nzp] % 10;  // target value
      rint newFace = face - val * decimal[nzp] + val * decimal[czp];
      if (hmap.probing(newFace) == 0) {
        hmap.insert(newFace, re);
        que[re++] = { newFace, nzp, fr, dir[czp][i] ^ 1 };
      }
      i++;
    } while (adj[czp][i]);
    ++fr;
  }
}

//#include <cstdio>
//struct Cheating {
//  Cheating() {
//      BFS();          //// may be considered cheating
//      puts("user Class : 내가 1빠");
//  }
//}object;

void test(const int puzzle[3][3]) {
  // If you modify the puzzle const data by bypassing it, you will be disqualified.

  if (re == 0)  // 10000개의 TC중에 처음 1번만 실행
    BFS();
  rint i, j, face = 0;
  //for (i = 0; i < 9; ++i)
  //  face = face * 10 + puzzle[i / 3][i % 3];  // 1차원 번호를 2차원으로 바꾸어 참조
  for (i = 0; i < 3; ++i)
    for (j = 0; j < 3; ++j)
      face = face * 10 + puzzle[i][j];

  i = hmap.probing(face);
  while (i > 1) {
    move(que[i].pathDir);
    i = que[i].pathIdx;
  }
  int debugBreakPoint = 1;
}
