inline void write_int(int x) {
#ifdef USE_SIGN
    if (x < 0) { putchar('-'); x = -x; }
#endif
    char buf[10], *p = buf;
    do { *p++ = '0' + x % 10; x /= 10; } while (x);
    do { putchar(*--p); } while (p > buf);
}

inline void read(int &res) {
    char c;
    while (c = getchar(), c <= ' ');
#ifdef USE_SIGN
    bool sign = c == '-';
    if (sign) { c = getchar(); }
#endif
    res = c - '0';
    while (c = getchar(), c >= '0' && c <= '9')
        res = res * 10 + (c - '0');a
#ifdef USE_SIGN
    if(sign) res = -res;
#endif
}