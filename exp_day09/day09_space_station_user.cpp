/*
 * day09_space_station_user.cpp
 *
 *  Created on: 2022. 12. 15.
 *      Author: bw.jung
 */
#include <cstdio>
#include <algorithm>

using namespace std;
using LL = long long;

const int LM = 100'000;
const int SZ = LM + 100;
const int CMAX = 1 << 16; // 65536
const LL CMAX2 = (LL) 1 << 32; // 4294967296
struct Point {
    double x, y, z;
    int id;
    double dist;
} coord[SZ], tc[SZ];

double (*mcode)[3];

void msort(Point *arr, int s, int e) {
    if (s >= e) return;
    int left = 0, right = 0;

    // divide
    int m = (s + e) / 2;
    msort(arr, s, m);
    msort(arr, m + 1, e);

    // conquer
    int k = s;
    while (left <= m && right <= e) {
        if (arr[left].dist < arr[right].dist) tc[k++] = arr[left++];
        else tc[k++] = arr[right++];
    }
    while (left <= m)
        tc[k++] = arr[left++];
    while (right <= e)
        tc[k++] = arr[right++];

    // merge
    for (int nn = s; nn <= e; nn++) {
        arr[nn] = tc[nn];
    }
}

/// ***** user.cpp *****
extern double mysqrt(double);

void get_distances_from_zero() {
//    return;
    for (int nn = 0; nn < LM; nn++) {
        const double xx = mcode[nn][0];
        const double yy = mcode[nn][1];
        const double zz = mcode[nn][2];
        const double dist = mysqrt(xx * xx + yy * yy + zz * zz);
        coord[nn].x = xx;
        coord[nn].y = yy;
        coord[nn].z = zz;
        coord[nn].id = nn;
        coord[nn].dist = dist;
    }
}

void print(int s, int e) {
    for (int nn = s; nn <= e; nn++) {
        printf("id[%d], dist=%.3lf\n", coord[nn].id, coord[nn].dist);
    }

}

void getStation(double paraCoordi[100000][3], int result[3]) {
    mcode = paraCoordi;

    get_distances_from_zero();
    print(0, 10);
    msort(coord, 0, 100000 - 1);
//    print(0, 10);

    printf("%lld\n", CMAX2);

}

