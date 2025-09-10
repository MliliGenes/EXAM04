#include <stdio.h>
// #include <malloc.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    ADD,
    MULTI,
    VAL
}   type_t;

typedef struct node {
    type_t type ;
    int val;
    struct node *l;
    struct node *r;
}   node;

typedef struct {
    char *str;
    int pos;
    char current;
    int len;
}lexer ;



#include <stdio.h>

// ANSI color codes
#define COLOR_RESET   "\033[0m"
#define COLOR_ADD     "\033[31m"  // Red
#define COLOR_MULTI   "\033[34m"  // Blue
#define COLOR_VAL     "\033[32m"  // Green

void print_tree(node *tree, int depth)
{
    if (!tree)
        return;

    // Indent based on depth
    for (int i = 0; i < depth; i++)
        printf("\t");  // 4 spaces per level

    // Print type and value with colors
    switch (tree->type) {
        case ADD:
            printf(COLOR_ADD "ADD\n" COLOR_RESET);
            break;
        case MULTI:
            printf(COLOR_MULTI "MULTI\n" COLOR_RESET);
            break;
        case VAL:
            printf(COLOR_VAL "VAL: %d\n" COLOR_RESET, tree->val);
            break;
    }

    // Recursively print children (left then right)
    if (tree->type != VAL) {
        print_tree(tree->l, depth + 1);
        print_tree(tree->r, depth + 1);
    }
}



void init_lexer(lexer *lex, char *str) {
    lex->str = strdup(str);
    if (!lex->str)
        return;
    lex->pos = 0;
    lex->current = lex->str[lex->pos];
    lex->len = strlen(lex->str);
}

void advance_lex(lexer* lex) {
    if (lex->pos < lex->len)
    {
        lex->pos++;
        lex->current = lex->str[lex->pos];
    }
}

node    *new_node(node n)
{
    node *ret = calloc(1, sizeof(n));
    if (!ret)
        return (NULL);
    *ret = n;
    return (ret);
}

void    destroy_tree(node *n)
{
    if (!n)
        return ;
    if (n->type != VAL)
    {
        destroy_tree(n->l);
        destroy_tree(n->r);
    }
    free(n);
}

void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of file\n");
}

int accept(lexer *lex, char c)
{
    advance_lex(lex);
    return (lex->current);
}

int expect(lexer* lex, char c)
{
    if (accept(lex, c))
        return (1);
    unexpected(lex->current);
    return (0);
}

node    *parse_expr(lexer * lex);

node *make_node(int type, int val, node *l, node *r) {
    node *n = malloc(sizeof(*n));
    if (!n) return NULL;
    n->type = type; n->val = val;
    n->l = l; n->r = r;
    return n;
}

node *parse_term(lexer *lex) {
    if (isdigit(lex->current)) {
        int val = lex->current - '0';
        advance_lex(lex);
        return make_node(VAL, val, NULL, NULL);
    }
    if (lex->current == '(') {
        advance_lex(lex);
        node *n = parse_expr(lex);
        if (!n) return NULL;
        if (lex->current != ')') return NULL;
        advance_lex(lex);
        return n;
    }
    return NULL;
}

node *parse_factor(lexer *lex) {
    node *left = parse_term(lex);
    if (!left) return NULL;
    while (lex->current == '*') {
        advance_lex(lex);
        node *right = parse_term(lex);
        left = make_node(MULTI, 0, left, right);
    }
    return left;
}

node *parse_expr(lexer *lex) {
    node *left = parse_factor(lex);
    if (!left) return NULL;
    while (lex->current == '+') {
        advance_lex(lex);
        node *right = parse_factor(lex);
        left = make_node(ADD, 0, left, right);
    }
    return left;
}


int eval_tree(node *tree)
{
    switch (tree->type)
    {
        case ADD:
            return (eval_tree(tree->l) + eval_tree(tree->r));
        case MULTI:
            return (eval_tree(tree->l) * eval_tree(tree->r));
        case VAL:
            return (tree->val);
    }
}

void ll()
{
    system("leaks a.out");
}

int main(int argc, char **argv)
{
    // atexit(ll);
    if (argc != 2)
        return (1);
    lexer lex;
    init_lexer(&lex, argv[1]);
    node *tree = parse_expr(&lex);
    print_tree(tree, 0);
    if (!tree || lex.current)
    {   
        unexpected(lex.current);
        destroy_tree(tree);
        free(lex.str);
        return (1);
    }
    printf("%d\n", eval_tree(tree));
    destroy_tree(tree);
    free(lex.str);
}