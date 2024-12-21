#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "password_spider.h"

char *program_name;  

int main(int argc, char *argv[]) {
    program_name = argv[0]; 
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        print_help(program_name);
        return 0;
    }
    if (argc < 3) {
        printf("Usage: %s <input_file> <output_file> [flags]\n", argv[0]);
        return 1;
    }
    const char *input_file = argv[1];
    const char *output_file = argv[2];
    int to_upper = 0, to_capitalize_flag = 0, add_nums = 0, add_special = 0, combine = 0;
    for (int i = 3; i < argc; i++) {
        if (strcmp(argv[i], "--upper") == 0) {
            to_upper = 1;
        } else if (strcmp(argv[i], "--capitalize") == 0) {
            to_capitalize_flag = 1;
        } else if (strcmp(argv[i], "--add_nums") == 0) {
            add_nums = 1;
        } else if (strcmp(argv[i], "--add_special") == 0) {
            add_special = 1;
        } else if (strcmp(argv[i], "--combine") == 0) {
            combine = 1;
        }
    }
    extract_top_passwords(input_file, output_file, to_upper, to_capitalize_flag, add_nums, add_special, combine);
    return 0;
}
