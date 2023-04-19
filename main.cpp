#include <iostream>
#include <cstring>
#include <fstream>

// prototypes.
void print_usage_message(char* program_name);
void transform(const std::string& input_filename, const std::string& output_filename, const std::string& key);
void print_file_not_found(const std::string& filename);

// Entry point.
int main(int argc, char** argv) {

    // Ensure proper usage.
    if (argc != 5) {
        print_usage_message(argv[0]);
        return EXIT_FAILURE;
    }

    // Remember input and output filenames.
    std::string input_filename = argv[2];
    std::string output_filename = argv[3];

    // Remember key.
    std::string key = argv[4];


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


void transform(const std::string& input_filename, const std::string& output_filename, const std::string& key) {
    
    // Open input file for reading.
    std::ifstream infile(input_filename);
    if (! infile.is_open()) {
        print_file_not_found(input_filename);
        exit(EXIT_FAILURE);
    }

    // Open output file for writing.
    std::ofstream outfile(output_filename);
    
    // Transformation.
    char ch;
    int i = 0;
    infile.read(&ch, 1);
    while (infile.gcount()) {
        ch ^= key[i];
        i = (i + 1) % key.length();

        outfile.write(&ch, 1);
        infile.read(&ch, 1);
    }

    // Free resources.
    outfile.close();
    infile.close();
}


void print_usage_message(char* program_name) {
    std::cout << "To encrypt:" << std::endl;
    std::cout << program_name << " -e <plaintext> <output filename> <key>" << std::endl;
    std::cout << "To decrypt:" << std::endl;
    std::cout << program_name << " -d <ciphertext> <output filename> <key>" << std::endl;
}

void print_file_not_found(const std::string& filename) {
    std::cout << filename << " doesn't exist or is busy." << std::endl;
}
