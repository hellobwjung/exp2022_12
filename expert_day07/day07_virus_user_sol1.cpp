/*
 * day07_where_are_you_user_sol2.cpp
 *
 *  Created on: 2022. 12. 13.
 *      Author: bw.jung
 */

/*
 29_바이러스제거_user_ver01
 binary search version
 SCORE: 1074335.001
 SCORE: 1074150.001
 SCORE: 1074348.001
 SCORE: 1074026.001
 SCORE: 1074298.001
 SCORE: 1073898.001
 SCORE: 1074247.001
 SCORE: 1074198.001
 SCORE: 1074171.001
 PASS
 */
#define rint register int

const int LM = 50'000'000;
const int SECT = 1024;

extern char virus_checkup(int n);
extern void culture(int n, int a, int b);
extern void clear(int n);

int bisearchLoop1(int low, int high) {
    while (low < high) {
        rint mid = (low + high) / 2;
        if (virus_checkup(LM + mid)) high = mid;
        else low = mid + 1;
    }
    return low;
}

int bisearchLoop2(int low, int high) {
    rint mid, ans = -1;
    while (low <= high) {
        if (low == high && ans < 0) return low;
        mid = (low + high) / 2;
        if (virus_checkup(LM + mid)) ans = mid, high = mid - 1;
        else low = mid + 1;
    }
    return ans;
}

int bisearchRecur(int low, int high) {
    if (low == high) return low;
    rint mid = (low + high) / 2;
    if (virus_checkup(LM + mid)) return bisearchRecur(low, mid);
    return bisearchRecur(mid + 1, high);
}

void test() {
    for (rint s = 0; s < LM;) {  // 구간 [s, e)
        rint e = s + SECT;
        if (e > LM) e = LM;

        // 1. culturing
        culture(LM + s, s, s);
        for (rint i = s + 1; i < e; ++i)
            culture(LM + i, LM + i - 1, i);

        // 2. find & erase
        if (virus_checkup(LM + e - 1)) {  // (s, e-1) 구간에서 찾은 경우
            //int tg = bisearchLoop1(s, e - 1);  // 찾기
            //int tg = bisearchLoop2(s, e - 1);  // 찾기
            int tg = bisearchRecur(s, e - 1);  // 찾기
            clear(tg);                         // 지우기
            s = tg + 1;
        }
        else s = e;                       // (s, e-1) 구간에서 못찾은 경우
    }
}
