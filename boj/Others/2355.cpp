#include <stdio.h>
#include <algorithm>

int main(void) {
    long long a, b;
    scanf("%lld %lld", &a, &b);
    if(a > b)
        std::swap(a, b);
    
    printf("%lld\n", b * (b + 1) / 2 - a * (a - 1) / 2);
}