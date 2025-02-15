#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Function to prepare the Playfair matrix
void preparePlayfairMatrix(char matrix[5][5], char key[]) {
    int keyLen = strlen(key);
    int index = 0;
    int i, j;
    char alphabet[26] = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // Note: I/J are treated as one in Playfair cipher

    // Initialize matrix with key
    for (i = 0; i < keyLen; ++i) {
        if (key[i] == 'J')
            key[i] = 'I'; // Replace J with I
        // Check if character already in matrix
        int found = 0;
        for (j = 0; j < index; ++j) {
            if (toupper(key[i]) == matrix[j/5][j%5]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            matrix[index/5][index%5] = toupper(key[i]);
            ++index;
        }
    }

    // Fill remaining matrix with remaining alphabet
    for (i = 0; i < 26; ++i) {
        if (alphabet[i] == 'J')
            alphabet[i] = 'I'; // Replace J with I
        // Check if character already in matrix
        int found = 0;
        for (j = 0; j < index; ++j) {
            if (alphabet[i] == matrix[j/5][j%5]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            matrix[index/5][index%5] = alphabet[i];
            ++index;
        }
        if (index == 25) break; // Matrix is filled
    }
}

// Function to find position of a character in the Playfair matrix
void findPosition(char matrix[5][5], char ch, int *row, int *col) {
    if (ch == 'J')
        ch = 'I'; // Replace J with I
    int i, j;
    for (i = 0; i < 5; ++i) {
        for (j = 0; j < 5; ++j) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt a message using Playfair cipher
void encryptMessage(char matrix[5][5], char *message, char *encryptedMessage) {
    int len = strlen(message);
    int i;
    char ch1, ch2;
    int row1, col1, row2, col2;

    // Adjust message for encryption (remove non-alpha characters and handle double letters)
    int j = 0;
    char adjustedMessage[len * 2];
    for (i = 0; i < len; ++i) {
        if (isalpha(message[i])) {
            adjustedMessage[j++] = toupper(message[i]);
            if (i+1 < len && message[i] == message[i+1]) {
                adjustedMessage[j++] = 'X'; // Insert 'X' between double letters
            }
        }
    }
    adjustedMessage[j] = '\0';

    // Encrypt the adjusted message
    len = strlen(adjustedMessage);
    j = 0;
    for (i = 0; i < len; i += 2) {
        ch1 = adjustedMessage[i];
        ch2 = (i+1 < len) ? adjustedMessage[i+1] : 'X'; // If odd number of characters, append 'X'

        findPosition(matrix, ch1, &row1, &col1);
        findPosition(matrix, ch2, &row2, &col2);

        if (row1 == row2) {
            encryptedMessage[j++] = matrix[row1][(col1+1)%5];
            encryptedMessage[j++] = matrix[row2][(col2+1)%5];
        } else if (col1 == col2) {
            encryptedMessage[j++] = matrix[(row1+1)%5][col1];
            encryptedMessage[j++] = matrix[(row2+1)%5][col2];
        } else {
            encryptedMessage[j++] = matrix[row1][col2];
            encryptedMessage[j++] = matrix[row2][col1];
        }
    }
    encryptedMessage[j] = '\0';
}

int main() {
    char key[] = "MFHIJKUNOPQZVWXYELARDSTBC"; // Playfair matrix key
    char matrix[5][5];
    char message[] = "Must see you over Cadogan West. Coming at once.";
    char encryptedMessage[1000];

    preparePlayfairMatrix(matrix, key);
    printf("Playfair Matrix:\n");
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    encryptMessage(matrix, message, encryptedMessage);
    printf("Original Message: %s\n", message);
    printf("Encrypted Message: %s\n", encryptedMessage);

    return 0;
}

