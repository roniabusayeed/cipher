#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// prototypes.
void print_usage_message(const char* program_name);
void transform(const char* input_filename, const char* output_filename, const char* key);
void print_file_not_found(const char* filename);

// Entry point.
int main(int argc, char** argv) {

    // Ensure proper usage.
    if (argc != 5) {
        print_usage_message(argv[0]);
        return EXIT_FAILURE;
    }

    // Remember input and output filenames.
    const char* input_filename = argv[2];
    const char* output_filename = argv[3];

    // Remember key.
    const char* key = argv[4];


    // Extract command options.
    if (argv[1][0] != '-' || strlen(argv[1]) != 2) {
        print_usage_message(argv[0]);
        return EXIT_FAILURE;
    }

    char option = argv[1][1];

    if (option == 'e') {
        // Encrypt.
        transform(input_filename, output_filename, key);
    } else if (option == 'd') {
        transform(input_filename, output_filename, key);
    }
}


void transform(const char* input_filename, const char* output_filename, const char* key) {
    
    // Open input file for reading.
    FILE* infile = fopen(input_filename, "r");
    if (! infile) {
        print_file_not_found(input_filename);
        exit(EXIT_FAILURE);
    }

    // Open output file for writing.
    FILE* outfile = fopen(output_filename, "w");
    
    // Transformation.
    char ch;
    int i = 0;
    size_t key_length = strlen(key);
    while (fread(&ch, 1, 1, infile)) {
        ch ^= key[i];
        i = (i + 1) % key_length;

        fwrite(&ch, 1, 1, outfile);
    }

    // Free resources.
    fclose(outfile);
    fclose(infile);
}


void print_usage_message(const char* program_name) {
    printf("To encrypt:\n");
    printf("%s -e <plaintext> <output filename> <key>\n", program_name);
    printf("To decrypt:\n");
    printf("%s -d <ciphertext> <output filename> <key>\n", program_name);
}

void print_file_not_found(const char* filename) {
    printf("%s doesn't exist or is busy.\n", filename);
}
