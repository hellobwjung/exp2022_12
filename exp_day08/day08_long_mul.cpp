/*
 * day08_long_mul.cpp
 *
 *  Created on: 2022. 12. 14.
 *      Author: bw.jung
 */

#include <cstdio>
const int LM = 2005;
const int BASE = 10;
char as[LM], bs[LM];
int strlen(char *s) {
    int len = 0;
    while (*s++) {
        len++;
    }
    return len;
}

struct BigInt {
    int sign;
    int len;
    int num[LM];

    void init() {
        sign = 0;
        len = 1;
        for (int i = 0; i < LM; i++) {
            num[i] = 0;
        }
    }

    BigInt() {
        init();
    }
    BigInt(char *s) {
        init();
        if (s[0] == '-') ++s, sign = 1;
        len = strlen(s);
        for (int i = 0; i < len; i++) {
            num[len - 1 - i] = s[i] - '0';
        }
    }
    bool isZero() {
        return len == 1 && num[0] == 0;
    }

    inline int max(int a, int b) {
        return a > b ? a : b;
    }
    inline int min(int a, int b) {
        return a < b ? a : b;
    }

    int arrcmp(int *ap, int alen, int *bp, int blen) { // a>b이면 양수,a<b이면 음수
        if (alen != blen) return alen - blen;
        int i = alen - 1;
        for (; i > 0 && ap[i] == bp[i]; i--) {
            ;
        }
        return ap[i] - bp[i];
    }

    int plus(int *tg, int *ap, int *bp, int len) {
        for (int i = 0; i < len; i++) {
            tg[i] = ap[i] + bp[i];
            tg[i + 1] += tg[i] / BASE;
            tg[i] %= BASE;
        }
        return len + (tg[len] > 0);
    }

    int minus(int *tg, int *ap, int *bp, int len) {
        for (int i = 0; i < len; i++) {
            tg[i] = ap[i] - bp[i];
            if (tg[i] < 0) ap[i + 1]--, tg[i] += BASE;
        }
        int i = len - 1;
        for (; i > 0 && tg[i] == 0; i--)
            ;
        return i + 1;
    }

    void add(BigInt &b) {
        if (sign == b.sign) {
            plus(num, num, b.num, max(len, b.len));
        }
        else {
            int cmp = arrcmp(num, len, b.num, b.len);
            if (cmp < 0) {      // a < b
                len = minus(num, b.num, num, b.len);
            }
            else if (cmp > 0) { // a>b
                len = minus(num, num, b.num, len);
            }
            else {
                init(); // 같으면 zero
            }
        }
    }
    void subtract(BigInt b) {
        b.sign ^ 1;
        add(b);
    }

    void multi(BigInt &b) {
        if (isZero() || b.isZero()) { // 둘 중 하나라도 0이면 0
            init();
            return;
        }

        sign ^= b.sign;
        int ret[LM] =
            { 0 };
        int rlen = len + b.len - 1;
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < b.len; j++) {
                ret[i + j] = num[i] * num[j];
            }
        }

        for (int i = 0; i <= rlen; i++) { // rlen에 각이 채우질 수 있다.
            ret[i + 1] += ret[i] / BASE;
            num[i] = ret[i] % BASE;
        }

        len = rlen + (num[rlen] > 0);

    }

    void toString(char *ret) {
        int i = 0, j = 0;
        if (sign) ret[j++] = '-';
        for (int i = 0; i < len; ++i)
            ret[j++] = num[len - i - 1] + '0';
        ret[j] = 0;  // 문자열의 끝 : sentinel value
    }

} mul, diff, operand, sum;

int main() {

    puts("begin");
    while (scanf("%s %s", as, bs)) {
        puts(as);
        puts(bs);
        mul = BigInt(as);
        operand = BigInt(bs);
        if (mul.isZero() && operand.isZero()) break;
        mul.multi(operand);
        mul.toString(as);
        puts(as);

    }
    return 0;
}
