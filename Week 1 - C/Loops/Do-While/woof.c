#include "cs50.h"
#include <stdio.h>

int main(void)
{
   string rep = get_string("How many times should I Woof!: ")
   
   do
   {
      printf("Woof!\n");
   }
   while (rep > 10);
}
