/*
 * day07_is_there_user_1.cpp
 *
 *  Created on: 2022. 12. 13.
 *      Author: bw.jung
 */

const int LM = 100000;
int guess[LM + 5];
int used[LM + 1];

// ***** user.cpp *****
extern int countSameNumber(int guess[]);

void consistOf(int N, int K) {
    int bin = 0;
    while ((1 << (bin + 1)) <= K) {
        bin++;
    }

    for (int nn = 1; nn <= N; nn += bin) {
        int v = 0;
        int idx = 0;
        for (int bb = 0; bb < bin; bb++) {
            const int rep = 1 << bb;
            for (int ll = 0; ll < rep; ll++) {
                guess[idx++] = nn + bb;
            }
        }

        const int ret = countSameNumber(guess);

        for (int bb = 0; bb < bin; bb++) {
            used[nn + bb] = (ret >> bb) & 1;
        }
    }

}

int isEntryNumber(int num) {

    return used[num];
}
