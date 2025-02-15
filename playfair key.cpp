#include <stdio.h>

long long factorial(int n) {
    if (n == 0 || n == 1)
        return 1LL;
    else
        return n * factorial(n - 1);
}

int main() {
    // Calculate 25!
    long long factorial_25 = factorial(25);
    
    // Calculate 2!
    long long factorial_2 = factorial(2);
    
    // Calculate 25! / 2!
    long long possible_keys = factorial_25 / factorial_2;
    
    // Output the result
    printf("Number of possible keys for the Playfair cipher: %lld\n", possible_keys);
    
    return 0;
}
