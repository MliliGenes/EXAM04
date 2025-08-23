#include <stdio.h>
#include <stdlib.h>

void print_subset(int *subset, int subset_size) {
    for (int i = 0; i < subset_size; i++) {
        printf("%d", subset[i]);
        if (i < subset_size - 1)
            printf(" ");
    }
    printf("\n");
}

void find_subsets(int *set, int set_size, int *subset, int subset_size, 
                  int index, int current_sum, int target_sum) {
    
    // If we found the target sum, print the subset
    if (current_sum == target_sum) {
        print_subset(subset, subset_size);
        return;
    }
    
    // If we've gone through all elements or sum is too big, stop
    if (index >= set_size || current_sum > target_sum) {
        return;
    }
    
    // Option 1: Include current element
    subset[subset_size] = set[index];
    find_subsets(set, set_size, subset, subset_size + 1, 
                 index + 1, current_sum + set[index], target_sum);
    
    // Option 2: Don't include current element
    find_subsets(set, set_size, subset, subset_size, 
                 index + 1, current_sum, target_sum);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <target_sum> <number1> <number2> ...\n", argv[0]);
        return 1;
    }

    int target_sum = atoi(argv[1]);
    int set_size = argc - 2;
    
    int *set = malloc(set_size * sizeof(int));
    if (!set) {
        return 1;
    }

    int *subset = malloc(set_size * sizeof(int));
    if (!subset) {
        free(set);
        return 1;
    }

    for (int i = 0; i < set_size; i++) {
        set[i] = atoi(argv[i + 2]);
    }

    find_subsets(set, set_size, subset, 0, 0, 0, target_sum);
    
    free(set);
    free(subset);
    return 0;
}
