
#include "util.h"

// input a file
char* read_file(FILE *file){
    if (file == NULL){
        fprintf(stderr, "ERROR: file open returned null\n");
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char * file_contents = malloc(file_size +1);

    fread(file_contents, 1, file_size, file);

    file_contents[file_size] = '\0';

    fclose(file);

    return file_contents;

}
