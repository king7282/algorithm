#include <stdio.h>

int main(void) {
    int test;
    scanf("%d", &test);
    
    for(int t = 1; t <= test; t++) {
        int a, b;
        scanf("%d %d", &a, &b);
        
        printf("Case %d: %d\n", t, a + b);
    }
}