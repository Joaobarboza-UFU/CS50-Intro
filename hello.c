#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What's your Name?\n"); //Asking the name of the user
    int age = get_int("What's yout age?\n");
    printf("hello, %s!\n", name); //Printing Hello plus the name of the user
    printf("You are %i years old\n", age);

}
