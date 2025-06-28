#include <stdio.h>
#include <string.h>

void compressRLE(FILE *inputFile, FILE *outputFile) {
    char currentChar;
    char nextChar;
    int count;

    if (fscanf(inputFile, "%c", &currentChar) == EOF) {
        return; // Empty file
    }

    while (1) {
        count = 1;
        // Read next character
        while (fscanf(inputFile, "%c", &nextChar) == 1 && nextChar == currentChar) {
            count++;
        }

        // Write count and character to output file
        fprintf(outputFile, "%d%c", count, currentChar);

        if (feof(inputFile)) { // Check if end of file was reached after the last character
            break;
        }
        currentChar = nextChar; // Move to the next character
    }
}

void decompressRLE(FILE *inputFile, FILE *outputFile) {
    int count;
    char charToPrint;

    while (fscanf(inputFile, "%d%c", &count, &charToPrint) == 2) {
        for (int i = 0; i < count; i++) {
            fprintf(outputFile, "%c", charToPrint);
        }
    }
}

int main() {
    FILE *inputFile, *compressedFile, *decompressedFile;

    // --- Compression ---
    inputFile = fopen("input.txt", "r");
    compressedFile = fopen("compressed.rle", "w");

    if (inputFile == NULL || compressedFile == NULL) {
        printf("Error opening files for compression.\n");
        return 1;
    }
    printf("Compressing...\n");
    compressRLE(inputFile, compressedFile);
    fclose(inputFile);
    fclose(compressedFile);
    printf("Compression complete. Check compressed.rle\n");

    // --- Decompression ---
    compressedFile = fopen("compressed.rle", "r");
    decompressedFile = fopen("decompressed.txt", "w");

    if (compressedFile == NULL || decompressedFile == NULL) {
        printf("Error opening files for decompression.\n");
        return 1;
    }
    printf("Decompressing...\n");
    decompressRLE(compressedFile, decompressedFile);
    fclose(compressedFile);
    fclose(decompressedFile);
    printf("Decompression complete. Check decompressed.txt\n");

    return 0;
}
