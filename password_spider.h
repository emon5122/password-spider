#ifndef PASSWORD_SPIDER_H
#define PASSWORD_SPIDER_H

#include <stdio.h> 

void print_help(char *program_name);
void to_uppercase(char *str);
void to_capitalize(char *str);
void generate_variations(const char *password, FILE *output_file, int to_upper, int to_capitalize_flag, int add_nums, int add_special);
void extract_top_passwords(const char *wordlist_location, const char *output_filename, int to_upper, int to_capitalize_flag, int add_nums, int add_special, int combine);

#endif
