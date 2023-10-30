#include <stdio.h>
int main()
{
    FILE *fP;
    unsigned int arr[60] = {0};
    fP = fopen("abc.txt", "r");
    char ch;
    char alpha[60]={'A','B','C','D','E','F' ,'G' ,'H' ,'I' ,'J' ,'K' ,'L' ,'M' ,'N' ,'O', 'P' ,'Q' ,'R' ,'S', 'T','U','V','W','X','Y','Z','.',' ',',','$','!','&','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    while (1)
    {

        ch = fgetc(fP);
        if (ch == EOF)
        {
            break;
        }
        else if (('A' <= ch <= 'Z') || ('a' <= ch <= 'z'))
        {
            // printf("%d",ch);
            arr[ch - 'A']++;
        }
        else
        {
            switch (ch)
            {
            case '.':
                arr[26]++;
                break;
            case ' ':
                arr[27]++;
                break;
            case ',':
                arr[28]++;
                break;
            case '$':
                arr[29]++;
                break;
            case '!':
                arr[30]++;
                break;
            case '&':
                arr[31]++;
                break;
            default:
                printf("\nNot valid character");
                break;
            }
        }
    }
    printf("Character  |  Frequency\n");
    printf("***************************\n");
    for (int i = 0; i <= 59; i++)
    {
        printf("%c   %14d\n",alpha[i],arr[i]);
    }
    printf("\n");
    fclose(fP);
    return 0;
}

