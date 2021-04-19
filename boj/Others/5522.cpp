#include <stdio.h>

int main(void) {
    int result = 0;
    for(int i = 0; i < 5; i++) {
        int a;
        scanf("%d", &a);
        
        result += a;
    }
    
    printf("%d\n", result);
}