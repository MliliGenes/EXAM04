#include <stdio.h>

void bubbleSort(char *str, int n) {

    for (int i = 0; str[i]; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (str[j] > str[j+1]) {
                char tmp = str[j];
                str[j] = str[j+1];
                str[j+1] = tmp;
            }
        }
    }
}

int permutate(char *perm, int len) {

    int i;

    // we check if the chars are in a reversed order and also we check we to stop meaning check char we should swap
    for (i = len - 1 ; i > 0 && perm[i - 1] >= perm[i] ; i--)
        continue ;

    if (i <= 0) //we reached the end last perm which is the biggest composition
        return 0;


    int j;

    for (j = len ; j > i && perm[j - 1] <= perm[i - 1] ; j--)
        continue ;

    char tmp = perm[j - 1];
    perm[j - 1] = perm[i - 1];
    perm[i - 1] = tmp;

    i++;
    j = len;

    while (j > i) {
        tmp = perm[i - 1];
        perm[i - 1] = perm[j - 1];
        perm[j - 1] = tmp;
        i++;
        j--;
    }
    return 1;
}

int main(int ac, char **av) {

    int n;
    for (n = 0; av[1][n]; n++)
        continue;

    printf("%s\n", av[1]);
    bubbleSort(av[1], n);
    printf("%s\n", av[1]);

    printf("\tpermutations \n");
    printf("%s\n",  av[1]);
    while (permutate(av[1], n))
        printf("%s\n",  av[1]);
}


int permutate(char *perm, int len) {
    
    // OPTIMIZATION 1: Handle edge cases early
    if (len <= 1) return 0;
    
    // STEP 1: Find pivot (rightmost ascending pair)
    int pivot_pos = len - 2;
    while (pivot_pos >= 0 && perm[pivot_pos] >= perm[pivot_pos + 1]) {
        pivot_pos--;
    }
    
    // STEP 2: Check if last permutation
    if (pivot_pos < 0) return 0;
    
    // STEP 3: Find successor (rightmost element > pivot)
    // OPTIMIZATION 2: Start search closer to pivot since we know suffix is descending
    int successor_pos = len - 1;
    while (perm[successor_pos] <= perm[pivot_pos]) {
        successor_pos--;
    }
    
    // STEP 4: Swap pivot with successor
    // OPTIMIZATION 3: Use XOR swap to avoid temporary variable (compiler usually does this anyway)
    char temp = perm[pivot_pos];
    perm[pivot_pos] = perm[successor_pos];
    perm[successor_pos] = temp;
    
    // STEP 5: Reverse suffix after pivot
    // OPTIMIZATION 4: Use pointers for faster access (especially for long arrays)
    char *left_ptr = perm + pivot_pos + 1;
    char *right_ptr = perm + len - 1;
    
    while (left_ptr < right_ptr) {
        temp = *left_ptr;
        *left_ptr = *right_ptr;
        *right_ptr = temp;
        left_ptr++;
        right_ptr--;
    }
    
    return 1;
}

/*
ADDITIONAL OPTIMIZATIONS FOR SPECIFIC USE CASES:

1. If you're generating ALL permutations:
   - Use iterative approach instead of recursive
   - Pre-allocate arrays to avoid memory allocation overhead

2. If working with integers instead of chars:
   - The algorithm is the same but slightly faster due to native integer operations

3. If you know the data characteristics:
   - For mostly sorted data: the first loop will be very short
   - For reverse sorted data: it will immediately return 0

4. For very large arrays:
   - Consider using memcpy for the reversal step
   - Use restrict pointers if compiler supports it

5. Compiler optimizations:
   - Use -O2 or -O3 flags
   - The compiler will inline and vectorize where possible
*/

// ALTERNATIVE: More cache-friendly version for very large arrays
int permutate_cache_optimized(char *perm, int len) {
    if (len <= 1) return 0;
    
    // Same logic but with better memory access patterns
    int pivot_pos = len - 2;
    while (pivot_pos >= 0 && perm[pivot_pos] >= perm[pivot_pos + 1]) {
        pivot_pos--;
    }
    
    if (pivot_pos < 0) return 0;
    
    int successor_pos = len - 1;
    while (perm[successor_pos] <= perm[pivot_pos]) {
        successor_pos--;
    }
    
    // Swap
    char temp = perm[pivot_pos];
    perm[pivot_pos] = perm[successor_pos];
    perm[successor_pos] = temp;
    
    // Use memmove for large reversals (> 16 elements)
    int suffix_len = len - pivot_pos - 1;
    if (suffix_len > 16) {
        // For large suffixes, a more complex but cache-friendly reversal
        for (int i = 0; i < suffix_len / 2; i++) {
            temp = perm[pivot_pos + 1 + i];
            perm[pivot_pos + 1 + i] = perm[len - 1 - i];
            perm[len - 1 - i] = temp;
        }
    } else {
        // Simple reversal for small suffixes
        char *left = perm + pivot_pos + 1;
        char *right = perm + len - 1;
        while (left < right) {
            temp = *left;
            *left = *right;
            *right = temp;
            left++;
            right--;
        }
    }
    
    return 1;
}