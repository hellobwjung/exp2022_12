/*
 * day01_minecraft2_1.cpp
 *
 *  Created on: 2022. 12. 5.
 *      Author: bw
 */

#include <cstdio>
#include <iostream>
using namespace std;

int N, M, NM, B;
const int LM = 505 * 505;
int arr[LM];
int height;
long long min_cost = 1 << 30;

void input1() {
  cin >> N >> M >> B;
  NM = N * M;
  for (int nn = 0; nn < NM; nn++) {
    cin >> arr[nn];
  }
}
int get_cost(int tgt) {
  long long cost = 0;
  int blocks = B;
  for (int nn = 0; nn < NM; nn++) {
    long long c = tgt - arr[nn];
    if (c > 0) { // tgt가 높을 때, 채워야해,
      cost += c;
      blocks -= c;
    } else { // tgt 가 낮을 때, 빼야
      cost += -(c * 2);
      blocks += -c;
    }

  }

  if (blocks < 0)
    return 1;

  if (min_cost >= cost) {
    min_cost = cost;
    height = tgt;

  }

  return 0;
}

void sol1() {
  for (int h = 0; h <= 256; h++) {
    if (get_cost(h)) {
      break;
    }
  }
}

int main() {
  input1();
  sol1();

  printf("%d %d\n", min_cost, height);

  return 0;
}
