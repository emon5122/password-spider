#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "password_spider.h" 

#define MAX_PASSWORD_LENGTH 100
#define MAX_LINE_LENGTH 256

void print_help(char *program_name) {
    printf("Usage: %s <input_file> <output_file> [flags]\n\n", program_name);
    printf("Arguments:\n");
    printf("  <input_file>          Path to the wordlist or password file to process\n");
    printf("  <output_file>         Path to the file where generated passwords will be saved\n");
    printf("\nFlags:\n");
    printf("  --upper               Convert all generated passwords to uppercase\n");
    printf("  --capitalize          Capitalize the first letter of the password\n");
    printf("  --add_nums            Append numbers (\"123\") to the generated password\n");
    printf("  --add_special         Append special characters (\"#$%%\") to the generated password\n");
    printf("  --combine             Combine each word from the input file with the top 10 passwords from the pipal output\n");
    printf("  --help                Display this help message\n");
    printf("\nExamples:\n");
    printf("  %s input.txt output.txt --upper --add_special\n", program_name);
    printf("  %s input.txt output.txt --combine\n", program_name);
}

void to_uppercase(char *str) {
    while (*str) {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

void to_capitalize(char *str) {
    if (str[0]) {
        str[0] = toupper((unsigned char)str[0]);
    }
}

void generate_variations(const char *password, FILE *output_file, int to_upper, int to_capitalize_flag, int add_nums, int add_special) {
    char modified_password[MAX_PASSWORD_LENGTH];
    strcpy(modified_password, password);  

    if (to_upper) {
        to_uppercase(modified_password);
    }

    if (to_capitalize_flag) {
        to_capitalize(modified_password);
    }

    fprintf(output_file, "%s\n", modified_password);
    printf("Generated: %s\n", modified_password); 

    if (add_nums) {
        strcat(modified_password, "123");
        fprintf(output_file, "%s\n", modified_password);
        printf("Generated with numbers: %s\n", modified_password); 
    }

    if (add_special) {
        strcat(modified_password, "#$%");
        fprintf(output_file, "%s\n", modified_password);
        printf("Generated with special characters: %s\n", modified_password); 
    }
}

void extract_top_passwords(const char *wordlist_location, const char *output_filename, int to_upper, int to_capitalize_flag, int add_nums, int add_special, int combine) {
    FILE *file = fopen(wordlist_location, "r");
    if (!file) {
        perror("Unable to open wordlist file");
        exit(1);
    }

    char line[MAX_PASSWORD_LENGTH];
    const int max_words = 1000;
    const char *words[max_words];
    int word_count = 0;

    while (fgets(line, sizeof(line), file) && word_count < max_words) {
        line[strcspn(line, "\n")] = 0;  
        words[word_count] = strdup(line);  
        word_count++;
    }

    fclose(file);

    FILE *out = fopen(output_filename, "w");
    if (!out) {
        perror("Unable to open output file");
        exit(1);
    }

    char command[MAX_LINE_LENGTH];
    snprintf(command, sizeof(command), "sudo pipal \"%s\" | grep -A 10 \"Top 10 passwords\" | tail -n +2 | awk -F '=' '{print $1}'", wordlist_location);

    FILE *piped_output = popen(command, "r");
    if (!piped_output) {
        perror("Error executing pipal command");
        exit(1);
    }

    char password[MAX_LINE_LENGTH];
    while (fgets(password, sizeof(password), piped_output)) {
        password[strcspn(password, "\n")] = 0;

        if (combine) {
            for (int i = 0; i < word_count; i++) {
                fprintf(out, "%s%s\n", words[i], password);  
            }
        } else {
            generate_variations(password, out, to_upper, to_capitalize_flag, add_nums, add_special);
        }
    }

    pclose(piped_output);  

    for (int i = 0; i < word_count; i++) {
        free((char *)words[i]);
    }

    fclose(out);
    printf("Passwords and variations saved to %s\n", output_filename);
}
