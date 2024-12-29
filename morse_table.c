#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char morse_code_check(char* str) {
    //* Use the length of the string to determine the morse code
    // I use 'X' as the default return value if the input is not a valid morse code
    // Input: a character string of 0 and 1
    // Output: a character
    switch (strlen(str)) {
        case 1:
            if (strcmp(str, "0") == 0) return 'e';
            if (strcmp(str, "1") == 0) return 't';
            return 'X';
            break;
        case 2:
            if (strcmp(str, "01") == 0) return 'a';
            if (strcmp(str, "00") == 0) return 'i';
            if (strcmp(str, "11") == 0) return 'm';
            if (strcmp(str, "10") == 0) return 'n';
            return 'X';
            break;
        case 3:
            if (strcmp(str, "000") == 0) return 's';
            if (strcmp(str, "001") == 0) return 'u';
            if (strcmp(str, "010") == 0) return 'r';
            if (strcmp(str, "011") == 0) return 'w';
            if (strcmp(str, "100") == 0) return 'd';
            if (strcmp(str, "101") == 0) return 'k';
            if (strcmp(str, "110") == 0) return 'g';
            if (strcmp(str, "111") == 0) return 'o';
            return 'X';
            break;
        case 4:
            if (strcmp(str, "0000") == 0) return 'h';
            if (strcmp(str, "0001") == 0) return 'v';
            if (strcmp(str, "0010") == 0) return 'f';
            if (strcmp(str, "0100") == 0) return 'l';
            if (strcmp(str, "0110") == 0) return 'p';
            if (strcmp(str, "0111") == 0) return 'j';
            if (strcmp(str, "1000") == 0) return 'b';
            if (strcmp(str, "1001") == 0) return 'x';
            if (strcmp(str, "1010") == 0) return 'c';
            if (strcmp(str, "1011") == 0) return 'y';
            if (strcmp(str, "1100") == 0) return 'z';
            if (strcmp(str, "1101") == 0) return 'q';
            return 'X';
            break;
        case 5:
            if (strcmp(str, "11111") == 0) return '0';
            if (strcmp(str, "01111") == 0) return '1';
            if (strcmp(str, "00111") == 0) return '2';
            if (strcmp(str, "00011") == 0) return '3';
            if (strcmp(str, "00001") == 0) return '4';
            if (strcmp(str, "00000") == 0) return '5';
            if (strcmp(str, "10000") == 0) return '6';
            if (strcmp(str, "11000") == 0) return '7';
            if (strcmp(str, "11100") == 0) return '8';
            if (strcmp(str, "11110") == 0) return '9';
            if (strcmp(str, "10001") == 0) return '=';
            if (strcmp(str, "10010") == 0) return '/';
            if (strcmp(str, "10110") == 0) return '(';
            if (strcmp(str, "01000") == 0) return '&';
            if (strcmp(str, "01010") == 0) return '+';
            return 'X';
            break;
        case 6:
            if (strcmp(str, "010101") == 0) return '.';
            if (strcmp(str, "111000") == 0) return ':';
            if (strcmp(str, "110011") == 0) return ',';
            if (strcmp(str, "101010") == 0) return ';';
            if (strcmp(str, "001100") == 0) return '?';
            if (strcmp(str, "011110") == 0) return '\'';
            if (strcmp(str, "101011") == 0) return '!';
            if (strcmp(str, "100001") == 0) return '-';
            if (strcmp(str, "001101") == 0) return '_';
            if (strcmp(str, "010010") == 0) return '\"';
            if (strcmp(str, "101101") == 0) return ')';
            if (strcmp(str, "011010") == 0) return '@';
            return 'X';
            break;
        case 7:
            if (strcmp(str, "0001001") == 0) return '$';
            return 'X';
            break;
        default:
            return 'X';
            break;
    }
}

/**
 * @brief For self testing
 * if you want to test this function, please uncomment the main function below
 */

// char str[20];
// char c = 'X';

// int main() {
//     while (1) {
//         scanf("%s", str);
//         c = morse_code_check(str);
//         printf("%c\n", c);
//     }
//     return 0;
// }