#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
 31_긴자리곱셈_ver01
 BigInt class : 1digit
 */
#include <cstdio>

const int LM = 2005;
const int BASE = 10;

char as[LM], bs[LM];
int strlen(const char *s, int len = 0) {
    for (; s[len]; ++len)
        ;
    return len;
}

struct BigInt {
    int num[LM];
    int len, sign;
    // default값 만들기 긴자리 0
    void init() {
        for (int i = 0; i < LM; ++i)
            num[i] = 0;
        len = 1;
        sign = 0;  // 0:양수 혹은 0, 1:음수
    }
    BigInt() {
        init();
    }
    BigInt(const char *s) {
        init();
        if (s[0] == '-') ++s, sign = 1;
        len = strlen(s);
        for (int i = 0; i < len; ++i)
            num[len - i - 1] = s[i] - '0';
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
    int arrcmp(int *ap, int alen, int *bp, int blen) {
        if (alen != blen) return alen - blen;  // 1순위: 길이가 긴것이 큰 수이다.
        int i = alen - 1;                      // 2순위: 길이가 같다면 높은 자리부터 비교한다.
        for (; i > 0 && ap[i] == bp[i]; --i)
            ;  //        같은 자리의 두수의 값이 다른 경우 또는 마지막 자리라면 종료
        return ap[i] - bp[i];                  // 음수(ap<bp), 0(ap==bp), 양수(ap>bp)
    }

    int plus(int *tg, int *ap, int *bp, int len) {
        for (int i = 0; i < len; ++i) {
            tg[i] = ap[i] + bp[i];
            tg[i + 1] += tg[i] / BASE;  // 자리올림 처리
            tg[i] %= BASE;
        }
        return len + (tg[len] > 0);
    }

    int minus(int *tg, int *ap, int *bp, int len) {
        for (int i = 0; i < len; ++i) {
            tg[i] = ap[i] - bp[i];
            if (tg[i] < 0) ap[i + 1]--, tg[i] += BASE;
        }
        int i = len - 1;
        for (; i > 0 && tg[i] == 0; --i)
            ;  // delete leading zero
        return i + 1;
    }

    void add(BigInt &b) {  // 계산 결과는 a에 저장된다.
        if (sign == b.sign) len = plus(num, num, b.num, max(len, b.len));
        else {
            int cmp = arrcmp(num, len, b.num, b.len);
            if (cmp < 0) len = minus(num, b.num, num, b.len);
            else if (cmp > 0) len = minus(num, num, b.num, len);
            else init();   // 두수가 같은 경우이므로 뺄셈의 결과는 0이다.
        }
    }

    void subtract(BigInt b) {
        b.sign ^= 1, add(b);
    }

    void multi(BigInt &b) {
        if (isZero() || b.isZero()) {
            init();
            return;
        }

        sign ^= b.sign;
        int ret[LM] =
            { 0 }, rlen = len + b.len - 1;
        for (int i = 0; i < len; ++i) {
            for (int j = 0; j < b.len; ++j) {
                ret[i + j] += num[i] * b.num[j];
            }
        }

        for (int i = 0; i <= rlen; ++i) {  // rlen에 값이 채워질수 있다.
            ret[i + 1] += ret[i] / BASE;
            num[i] = ret[i] % BASE;
        }
        len = rlen + (ret[rlen] > 0);
    }

    void toString(char *ret) {
        int i = 0, j = 0;
        if (sign) ret[j++] = '-';
        for (int i = 0; i < len; ++i)
            ret[j++] = num[len - i - 1] + '0';
        ret[j] = 0;  // 문자열의 끝 : sentinel value
    }
} sum, diff, operand, mul;
// 합: sum += operand
// 차: diff -= operand
// 곱: mul *= operand

int main() {
#ifdef _WIN32
    freopen("31.txt", "r", stdin);
#endif // _WIN32
    while (scanf("%s %s", as, bs)) {
        mul = BigInt(as);
        operand = BigInt(bs);
        if (mul.isZero() && operand.isZero()) break;
        mul.multi(operand);
        mul.toString(as);
        puts(as);
    }

    return 0;
}
