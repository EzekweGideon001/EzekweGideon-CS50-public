#include <stdio.h>
#include <cs50.h>

int main(void){
    int height;
    do{
        height = get_int("Choose a number between 1 and 8, inclusive: ");
    }
    while (height < 1 || height > 8);

    for(int i = 0; i < height; i++){
        //print right spaces
        for(int j = 0; j < height - 1 - i; j++){
            printf(" ");
        }

        //print left sides
        for(int k = 0; k <= i; k++){
            printf("#");
        }

        //print two spaces
        printf("  ");

        //print right side
        for(int l = 0; l <= i; l++){
            printf("#");
        }

        //go to new line
        printf("\n");
    }
}
