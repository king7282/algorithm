#include <stdio.h>

int main(void) {
    int test;
    scanf("%d", &test);
    
    for(int t = 0; t < test; t++) {
        int a, b;
        scanf("%d %d", &a, &b);
        
        printf("You get %d piece(s) and your dad gets %d piece(s).\n", a / b, a % b);
    }
}