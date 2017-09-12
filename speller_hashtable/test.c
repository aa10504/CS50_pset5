#include <stdio.h>
#include <cs50.h>

int main()
{
    char *word = get_string();
    int temp = word[0] - 97;
    printf("%c\n", word[0]);
    printf("%i\n", temp);
    
    for(int i = 0; i < 10; i++)
    {
        if(i == 5)
        {
        
        }
        else
        {
            printf("%i\n", i);
        }
    }
}