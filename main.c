#include "number_converter.h"

int main() {
   int result = proccessNumber("XII");
   printf("%i", result);
   printf("\n");
   char * a = decimal_to_roman(13);
   printf("%s", a);
   return 0;
}
