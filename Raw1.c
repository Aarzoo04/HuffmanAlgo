#include <stdio.h>
int main()
{
    FILE *fP;
    unsigned int arr[58] = {0};
    fP = fopen("abc.txt", "r");
    char ch;
    char alpha[58]={'A','B','C','D','E','F' ,'G' ,'H' ,'I' ,'J' ,'K' ,'L' ,'M' ,'N' ,'O', 'P' ,'Q' ,'R' ,'S', 'T','U','V','W','X','Y','Z','.',' ',',','$','!','&','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    while (1)
    {

        ch = fgetc(fP);
        if (ch == EOF)
        {
            break;
        }
        // Check if the character is in the 'alpha' array
        int index = -1;
        for (int i = 0; i < 58; i++) {
            if (alpha[i] == ch) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            arr[index]++;
        } else {
            printf("\nNot a valid character");
        }
        }
    
    printf("Character  |  Frequency\n");
    printf("***************************\n");
    for (int i = 0; i <= 57; i++)
    {
        printf("%c   %14d\n",alpha[i],arr[i]);
    }
    printf("\n");
    fclose(fP);
    return 0;
}

