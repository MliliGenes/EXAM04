#include <stdio.h>

int check_balence(char *str)
{
    if (!str) {
        return 0;
    }
    int count = 0;
    for (int i = 0; str[i]; i++) {
        if(str[i] == '(')
            count++;
        else if (str[i] == ')') {
            count--;
            if (count < 0)
                return 0;
        }
    }
    if (count == 0)
        return  1;
    return 0;
}

int removals( char *str ) {
    int count = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] == '(')
            count++;
        else if (str[i] == ')'){
            count--;
        }
    }
    return  count;
}

void printf_balence(char *str, int balence, int pos, int len)
{
    int i = 0;
    char fake_str[len];
    while (str[i]) {
        fake_str[i] = str[i];
        i++;
    }
    fake_str[i] = '\0';

    if (balence < 0) {
        balence =  -balence;
        for (int j = 0; fake_str[j] && balence > 0; j++){
            if (fake_str[j] == ')' && j != pos)
            {    fake_str[j] = ' ';
                balence --;}
        }
        if (check_balence(fake_str))
            printf("%s\n",fake_str);
    }
    if (balence > 0) {
        for (int j = 0; fake_str[j]  && balence > 0; j++){
            if (fake_str[j] == '(' && j != pos)
            {fake_str[j] = ' ';
                balence --;}
        }
        if (check_balence(fake_str))
            printf("%s\n",fake_str);
    }
}

int main(int ac, char **av)
{
    if (ac != 2) {
        return 1;
    }
    char *str = av[1];
    int balence = removals(str);
    if (!balence) {
        puts(str);
        return 0;
    }
    printf("%d\n", balence);
    int len = 0;
    while (str[len]) {
        len++;
    }
    for (int i = 0; str[i]; i++) {
        printf_balence(str, balence, i, len);
    }
    
}