#include <stdio.h>
#include <cs50.h>
#include <string.h>

float index(float L, float S);

int main(void)
{
    //Askig the User the input Text.
    string text = get_string("Text: ");
    int string_size = strlen(text);
    //Creating a variable to store the number of words , sentences and letters
    float letters = 0;
    float words = 1;
    float sentences = 0;
    //Loop to calculate the number of letters, Words and sentences
    for (int i = 0 ; i < string_size ; i++)
    {
        //If used to check if the Char is a letter between a and z or A and Z
        if ((64 < text[i] & text[i] < 91) || (96 < text[i] & text[i] < 123))
        {
            letters += 1;
        }
        //Else if used to Check the number of words
        else if (text[i] == 32)
        {
            words += 1;
        }
        //Else if used to check the number of sentences
        else if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences += 1;
        }
    }
    //Variables used to store the avveras per 100 words
    float L1 = (letters * (100 / words));
    float S1 = (sentences * (100 / words));
    index(L1, S1);

}
//Function that calculates the index
float index(float L, float S)
{
    float ind = ((0.0588 * L) - (0.296 * S) - 15.8);
    if (ind > 16)
    {
        printf("Grade 16+\n");
    }
    else if (1 > ind)
    {
        printf("Before Grade 1\n");
    }
    //Else used to print the result if it's not bigger than 16 and not smaller than 1
    else
    {
        //if used to se the closest integer
        if ((ind - (int)ind) > 0.5)
        {
            printf("Grade %i\n", (int)ind + 1);
        }
        else
        {
            printf("Grade %i\n", (int)ind);
        }
    }
    return 0;
}
