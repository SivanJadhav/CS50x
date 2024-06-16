#include <cs50.h>
#include <stdio.h>

int main(void) {
  char c = get_char("Do you agree? ");

  if (c == 'y' || 'Y') {
    printf("Agreed!\n");
  } else if (c == 'n' || 'N') {
    printf("Not Agreed!\n");
  }
}
