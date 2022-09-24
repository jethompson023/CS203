#include <stdio.h>
#include <string.h>

/*
In this code we remove all occurrences of string length
and string concatenation functions.  We will pass a pointer
to the pointer which addresses which character of reversed
to access next.  This reversal is linear in the length of the
string to reverse.
*/

void makeNull(char * s, int n)
{
  for (int i = 0; i < n; i++)
    *(s + i) = '\0';
}
void reverseString(char *original, char **reversed)
{

  if (*original == '\0')
  {
    return;
  }
  reverseString(original + 1, reversed);
  **reversed = *original;
  *reversed += 1;
}

int main()
{
  char inLine[81];
  char reversedLine[81];
  makeNull(reversedLine, 81);
  char *revPtr;
  revPtr = reversedLine;
  char ** doubleRef;
  doubleRef = &revPtr;
  fgets(inLine, 81, stdin);
  
  while (strlen(inLine) > 1){
    reverseString(inLine, doubleRef);
    printf("%s", reversedLine);
    makeNull(reversedLine, 81);
    makeNull(inLine, 81);
    revPtr = reversedLine;
    doubleRef = &revPtr;
    fgets(inLine, 81, stdin);
  }
}