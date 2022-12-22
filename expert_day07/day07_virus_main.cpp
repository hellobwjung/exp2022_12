/*
 * day07_virus_main.cpp
 *
 *  Created on: 2022. 12. 13.
 *      Author: bw.jung
 */

/// *****  main.cpp *****
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include  <stdio.h >
#include  <time.h >

extern void test();

static const int MAIN_MAX = 50'000'000;
static double SCORE = 0.0;
static char tray[MAIN_MAX * 2];

char virus_checkup(int n)  // tray[n]값 알아보기: 비용 1발생
        {
    SCORE += 1.0;
    if (n < 0 || n >= MAIN_MAX * 2) return tray[0];
    return tray[n];
}

void culture(int n, int a, int b) // 비용 공짜
        {
    if (n < MAIN_MAX || n >= MAIN_MAX * 2) return;
    if (a < 0 || a >= MAIN_MAX * 2) return;
    if (b < 0 || b >= MAIN_MAX * 2) return;
    tray[n] = tray[a] | tray[b];
}

void clear(int n)  // tray[n]을 지우기 : 비용 10발생
        {
    if (n < 0 || n >= MAIN_MAX * 2) return;
    SCORE += 10.0;
    tray[n] = 0;
}

static unsigned long long seed = 5;

static unsigned int random(void) {
    seed = (seed = seed * 25214903917ULL + 11ULL);
    return ((unsigned int) (seed >> 16));
}

int main(void) {
    freopen("29.txt", "r", stdin);

    bool ok = true;

    for (int i = 0; i < 10; ++i) {

        int sd;
        scanf("%d", &sd);
        seed = sd;
        SCORE = 0;

        for (register int c = 0; c < MAIN_MAX * 2; c++)
            tray[c] = 0;  // 1억개의 공간 초기화

        // 0 ~ 49,999,999중 임의의 위치 50000개에 1을 넣기
        for (register int c = 0; c < MAIN_MAX / 1000; c++)
            tray[random() % MAIN_MAX] = 1;

        clock_t time = clock();
        test();                  // tray[]에서 1을 찾아 지워라.
        time = clock() - time;

        for (register int c = 0; c < MAIN_MAX; c++) {
            if (tray[c] != 0)   // 지우지 못한 1개당 1만점의 벌점 부과
            SCORE += 10000.0;
        }

        SCORE += ((double) (time) / CLOCKS_PER_SEC / 100);

        printf("SCORE: %.3f\n", SCORE);

        int cut;
        scanf("%d", &cut);
        if (SCORE > cut) ok = false;
    }

    if (ok) puts("PASS");
    else puts("FAIL");

    return 0;
}

