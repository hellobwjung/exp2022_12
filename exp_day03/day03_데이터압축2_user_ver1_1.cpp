/*
 * day03_데이터압축2_user_ver1_1.cpp
 *
 *  Created on: 2023. 2. 15.
 *      Author: bw
 */

#define rint register int
const int LM = 10000;
const int TH = 30;
void comp(char map[10000][10000], char data[150000]) {

  rint dataIndex = 4; // data[]의 인덱스, data[0]: 가로의 선분 갯수, data[1]: 전체 선분의 갯수
  short *ap = (short*) data; //data 배열을 2바이트 단위로 사용하겠다는 의미
  int *bp = (int*) data; //

  // 가로로 세어 기록하기
  rint y, x, k;
  for (y = 0; y < LM; y++) {
    for (x = 0; x < LM; x++) {
      if (map[y][x] == 1) {
        for (k = x + 1; k < LM && map[y][k] == 1; k++) {
          ; // k:x축 길이
        }
        rint len = k - y + 1;
        if (len > TH) {
          ap[dataIndex++] = y; // 행번호
          ap[dataIndex++] = x; // 열시작
          ap[dataIndex++] = k; // 열끝
        }

        // 가로로 센 것을 표시 하기: 세로로 셀 때 제외하고 생각하기 위하여.
        for (; x < k; x++) {
          map[y][x] = 2;
        }
      }
      x = k;
    }
  }
  bp[0] = dataIndex;

  // 세로로 세어 기록하기

  for (x = 0; x < LM; x++) {
    for (y = 0; y < LM; y++) {
      if (map[y][x] == 1) { // 시작위치
        for (k = y + 1; k < LM && map[y][x] == 1; k++) {
          ; // k:y 축 길
        }
        ap[dataIndex++] = x; // 열번호
        ap[dataIndex++] = y; // 행시작
        ap[dataIndex++] = k; // 행끝
        y = k;
      }
    }
    bp[1] = dataIndex;
  }

}

}
void decomp(char map[10000][10000], char data[150000]) {

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
 *
 *
 *
 * */

