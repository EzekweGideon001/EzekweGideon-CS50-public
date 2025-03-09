#include <stdio.h>
#include <cs50.h>

int main(void){
    int change;
    do{
        change = get_int("Change owed: ");
    }
    while(change < 0);
    //initialize a counter
    int count = 0;

    //for quarters
    while(change >= 25){
        change -= 25;
        count += 1;
    }

    //for dimes
    while(change >= 10){
        change -= 10;
        count += 1;
    }

    //for nickels
    while(change >= 5){
        change -= 5;
        count += 1;
    }

    //for pennies
    while(change >= 1){
        change -= 1;
        count += 1;
    }

    //print result
    printf("%i\n", count);
}
