#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int score(string word);

int main(void) {
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    // Check scores and compare
    int score1 = score(player1);
    int score2 = score(player2);

    if (score1 > score2) {
        printf("Player 1 wins!\n");
    } else if (score2 > score1) {
        printf("Player 2 wins!\n");
    } else {
        printf("Tie!\n");
    }
}

int score(string word) {
    int sum = 0; // Initialize sum outside of the loop
    for (int i = 0, n = strlen(word); i < n; i++) {
        char lower_char = tolower(word[i]);
        // Go through chars to increase sum
        if (lower_char == 'a' || lower_char == 'e' || lower_char == 'i' ||
            lower_char == 'l' || lower_char == 'n' || lower_char == 'o' ||
            lower_char == 'r' || lower_char == 's' || lower_char == 't' || lower_char == 'u') {
            sum += 1;
        } else if (lower_char == 'd' || lower_char == 'g') {
            sum += 2;
        } else if (lower_char == 'b' || lower_char == 'c' || lower_char == 'm' || lower_char == 'p') {
            sum += 3;
        } else if (lower_char == 'f' || lower_char == 'h' || lower_char == 'v' ||
                   lower_char == 'w' || lower_char == 'y') {
            sum += 4;
        } else if (lower_char == 'k') {
            sum += 5;
        } else if (lower_char == 'j' || lower_char == 'x') {
            sum += 8;
        } else if (lower_char == 'q' || lower_char == 'z') {
            sum += 10;
        }
    }
    return sum;
}
