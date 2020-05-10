#include <stdio.h>
#include <cs50.h>
#include <string.h>

//calling the functions to avoid an error
bool IsUpper(char p);
bool IsLower(char l);
bool ValidKey(string j, int f);
bool treatment(int u, int s);
bool DuplicateChar(string reference);
char cipher(string i, string key);

//Main function used to call all other functions and execute the command line argument
int main(int argc, string argv[])
{
    //if used to check if the number of arguments is correct
    if (argc == 2)
    {
        int argument = strlen(argv[1]);
        //if used to call all the correctness check functions
        if ((treatment(argument, argc)) & ValidKey(argv[1], argument) & DuplicateChar(argv[1]))
        {
            string plaintext = get_string("plaintext: \n");
            cipher(plaintext, argv[1]);
            return 0;
        }
        //return error value and message for wrong key
        else
        {
            printf("Key must contain 26 different characters.\n");
            return 1;
        }
    }
    //return error value and message for wrong number of arguments
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

//function that replace the characters to the new ones
char cipher(string i, string key)
{
    int size = strlen(i);
    for (int x = 0 ; x < size ; x++)
    {
        //if used to check if the char is lower to avoid to convert it to a upper
        if (IsLower(i[x]))
        {
            if (IsLower((char)key[((int)i[x] - 65)]))
            {
                i[x] = (char)key[((int)i[x] - 65)];
            }
            //else used to convert a lower to a lower despite of the key char being an upper
            else
            {
                i[x] = (char)(key[((int)i[x] - 65)] - 32);
            }
        }
        //if used to check if the char is upper to avoid to convert it to a lower
        else if (IsUpper(i[x]))
        {
            if (IsUpper((char)key[((int)i[x] - 97)]))
            {
                i[x] = (char)key[((int)i[x] - 97)];
            }
            //else used to convert an upper to an upper despite of the key char being a lower
            else
            {
                i[x] = (char)(key[((int)i[x] - 97)] + 32);
            }
        }
    }
    printf("ciphertext: %s\n", i);
    return 0;
}

//Function to check if the char is upper
bool IsUpper(char p)
{
    if (((int)p > 96) & ((int)p < 123))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Function to check if the char is lower
bool IsLower(char l)
{
    if (((int)l > 64) & ((int)l < 91))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//function to check if all chars in the key are alphabetics
bool ValidKey(string j, int f)
{
    int u = 0;
    for (int k = 0 ; k < f ; k++)
    {
        if (!((IsUpper(j[k])) || (IsLower(j[k]))))
        {
            u += 1;
        }
    }
    if (u > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//function to check if the size of the key and the number of arguments is correct
bool treatment(int u, int s)
{
    if ((u == 26) & (s == 2))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//function to check if there are no duplicates chars in the key
bool DuplicateChar(string reference)
{
    int check = 0;
    int lenght = strlen(reference);
    for (int y = 0 ; y < lenght ; y++)
    {
        char element = reference[y];
        for (int b = 0 ; b < lenght ; b++)
        {
            if ((int)element == (int)reference[b])
            {
                check += 1;
            }
        }
    }
    if (check > 26)
    {
        return false;
    }
    else
    {
        return true;
    }
}
