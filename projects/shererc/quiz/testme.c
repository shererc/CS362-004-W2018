#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
  // Get a random ASCII character between 40 and 125
  return rand() % 95 + 32;
}

char *inputString(int tcCount)
{
  static char stringString[6];
    int i;
      for(i = 0; i < 5; i++){
        //for the first 5 million test, run with all characters
        if(tcCount < 5000000){
          stringString[i] = rand() % 26 + 97;
        } else {
          // After the first 5 million, only run on ASCII characters e-t to get all of the characters we are testing for
          stringString[i] = rand() % 16 + 101;
        }
      }
    
    stringString[6] = '\0';
    return stringString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    char goodString[5] = "reset";
    c = inputChar();
    s = inputString(tcCount);
    if((tcCount % 10 == 0 || (strcmp(goodString, s) == 0))){
      printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);
    }

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
