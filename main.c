#include <stdio.h>
#include "str.h"
#include "scaner.h"

#define FILE_ERROR 5

string attr;

int main()
{

  printf("\nSTART SCANNER\n\n");

  strInit(&attr);
  int returnValue;
  while(1) {
    returnValue = getNextToken(&attr);
    printf("String: %20s \t\t Value: %20d\n", attr.str, returnValue);
    if(returnValue == END_OF_FILE) {
      break;
    }
  }
  strFree(&attr);

  printf("\nEND SCANNER\n");
  return 0;
}