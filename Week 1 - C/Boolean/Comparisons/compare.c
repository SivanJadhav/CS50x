#include <cs50.h>
#include <stdio.h>

int main(void) {
  int x = get_int("Give me a number? ");
  int y = get_int("Give me one more number? ");

  if (x < y) {
    printf("The number %i is smaller than the number %i\n", x, y);
  } else if (x > y) {
    printf("The number %i is greater than the number %i\n", x, y);
  } else {
    printf("The number %i is equal to the number %i\n", x, y);
  }
}
