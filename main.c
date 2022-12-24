
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "util.h"

enum TokenType {
COMBINATOR,
IDENTIFIER,
LEFT_PAREN,
RIGHT_PAREN
};

typedef struct {
    enum TokenType type;
    char  value;
} Token;

typedef struct{
    Token * tokens;
    size_t tokens_len;
    size_t curr_index;
} Lexer;

Lexer lex(char *input) {
    Token * tokens = malloc(sizeof(Token) * strlen(input));
    int token_index = 0;
    int char_index = 0;
    char current_char = input[char_index];

    while (current_char != '\0') {
        if (current_char == 'S' || current_char == 'K' || current_char == 'I'){
           tokens[token_index].type = COMBINATOR;
           tokens[token_index].value = current_char;
           token_index++;
        }
        if (current_char == '('){
            tokens[token_index].type = LEFT_PAREN;
            tokens[token_index].value = current_char;
            token_index++;
        }
        if (current_char == ')'){
            tokens[token_index].type = RIGHT_PAREN;
            tokens[token_index].value = current_char;
            token_index++;
        } else if (isalpha(current_char) && current_char != 'S' && current_char != 'K' && current_char != 'I'){
            tokens[token_index].type = IDENTIFIER;
            tokens[token_index].value = current_char;
            token_index++;
        }
    char_index++;
    current_char = input[char_index];
    }
    Lexer ret_lexer;
    ret_lexer.tokens = tokens;
    ret_lexer.tokens_len = token_index;
    ret_lexer.curr_index = 0;
    return ret_lexer;
}

////////////////////////////////////////////////////
///                   Parse                   /////
////////////////////////////////////////////////////
typedef struct ASTnode {
    char type;
    struct ASTnode *left;
    struct ASTnode *right;
} ASTnode;

struct S {
    char type;
    char first;
    char second;
    char third;
};

struct K {
    char type;
    char first;
    char second;
};

struct I {
    char type;

};

ASTnode* new_ASTnode(char type, ASTnode* left, ASTnode* right){
    ASTnode * node = malloc(sizeof(ASTnode));
    node->type = type;
    node->left = left;
    node->right = right;
    return node;
}






int main(int argc, char *argv[]){
    FILE *file;
    if (argc == 1){
        printf("Input a file\n");
    } else if (argc == 2){
        file = fopen(argv[1], "r");
        if (file == NULL){
            fprintf(stderr, "ERROR: NULL when opening file\n");
            exit(1);
        }
    } else {
        printf("ERROR: Too many arguments\n");
    }

    char * file_contents = read_file(file);
    Lexer toks = lex(file_contents);
    for (size_t i = 0; i < toks.tokens_len; i++){
        printf("%c\n", toks.tokens[i].value);
    }

    return 0;
}
