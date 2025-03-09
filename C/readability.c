#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int countLetters(string text);
int countWords(string text);
int countSentences(string text);
int main(void){
    string text = get_string ("Text: ");
    int letters = countLetters(text);
    int words = countWords(text);
    int sentences = countSentences(text);
    float L = (letters *  100.0) / words;
    float S = (sentences * 100.0) / words;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    if (index < 1){
        printf("Before Grade 1\n");
    }
    else if (index >= 16){
        printf("Grade 16+\n");
    }
    else{
        printf("Grade %i\n", (int)round(index));
    }
}



//to count number of letters
int countLetters(string text){
    int letters = 0;
    for (int i = 0, n = strlen(text); i < n; i ++){
        if (isalpha(text[i])){
            letters += 1;
        }
    }
    return letters;
}


//to count number of words
int countWords(string text){
    int words = 0;
    for (int i = 0, n = strlen(text); i < n; i ++){
        if (isspace(text[i])){
            words += 1;
        }
    }
    return words + 1;
}


//to count number of sentences
int countSentences(string text){
    int sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i ++){
        if (text[i] == '.' || text[i] == '?' || text[i] == '!'){
            sentences += 1;
        }
    }
    return sentences;
}
