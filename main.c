
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

enum TokenType {
COMBINATOR,
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
        }
    char_index++;
    current_char = input[char_index];
    }
    Lexer ret_lexer;
    ret_lexer.tokens = tokens;
    ret_lexer.tokens_len = token_index;
    return ret_lexer;
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
    for (int i = 0; i < toks.tokens_len; i++){
        printf("%c\n", toks.tokens[i].value);
    }

    return 0;
}
