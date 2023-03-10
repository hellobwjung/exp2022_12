/*
 * test.cpp
 *
 *  Created on: 2022. 12. 19.
 *      Author: bw
 */

#include <cstdio>
#include <unordered_map>
#include <iostream>

using namespace std;

int main() {

  unordered_map<int, int> um;
  um.insert( { 1, 2 });
  um.insert( { 3, 4 });
  um.insert( { 5, 6 });
  um.insert( { 7, 8 });
  um.insert( { 7, 9 });
  um.insert( { 6, 6 });
  um[7] = 9;

  for (auto e : um) {
    cout << e.first << ", " << e.second << endl;

  }

  cout << "done done " << endl;
  return 0;
}
