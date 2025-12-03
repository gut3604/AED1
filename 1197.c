#include <stdio.h>

int main() {
    long long v, t;
    while (scanf("%lld %lld", &v, &t) != EOF) {
        printf("%lld\n", v * (2 * t));
    }
    return 0;
}
