#include <stdio.h>

int main(void) {
    int test;
    scanf("%d", &test);
    
    for(int t = 0; t < test; t++) {
        int s;
        scanf("%d", &s);
        
        int n;
        scanf("%d", &n);
        
        for(int i = 1; i <= n; i++) {
            int q, p;
            scanf("%d %d", &q, &p);
            
            s += q * p;
        }
        
        printf("%d\n", s);
    }
}{\rtf1}