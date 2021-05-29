#include <stdio.h>
#include <algorithm>

int input[4];

int main(void) {
    for(int i = 0; i < 4; i++)
        scanf("%d", input + i);
    
    std::sort(input, input + 4);
    printf("%d\n", input[0] * input[2]);
}