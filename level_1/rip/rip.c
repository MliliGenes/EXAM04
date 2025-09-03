#include <stdio.h>
#define MAX 256

int to_remove( char *str ) {
    int open = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(')
            open++;
        else
            open--;
    }
    return open;
}

int isValid(char s[]) {
    int bal = 0, i = 0;
    while (s[i] != '\0') {
        if (s[i] == '(')
            bal++;
        else if (s[i] == ')') {
            bal--;
            if (bal < 0)
                return 0;
        }
        i++;
    }
    return bal == 0;
}

// Generate combinations recursively
void generate(char s[], int pos, int imbalance) {
    if (s[pos] == '\0') {
        if (imbalance == 0 && isValid(s)) {
            printf("%s\n", s);
        }
        return;
    }
    
    if ((s[pos] == '(' || s[pos] == ')') && imbalance != 0) {
        char old = s[pos];
        s[pos] = ' ';
        generate(s, pos + 1, imbalance + (old == '(' ? -1 : 1));
        s[pos] = old;
    }
    
    generate(s, pos + 1, imbalance);
}

int main(int ac, char **av) {
    char *s = av[1];
    
    int imbalance = to_remove(s);
    
    if (isValid(s)) {
        printf("%s\n", s);
        return 0;
    }
    
    printf("Imbalance: %d\n", imbalance);
    generate(s, 0, imbalance);
    
    return 0;
}