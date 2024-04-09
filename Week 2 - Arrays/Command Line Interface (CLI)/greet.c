#include <stdio.h>

int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Insufficient Arguments!\n");
        return 1;
    }
    
    for (int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }
}
