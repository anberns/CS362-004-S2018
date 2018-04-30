/* Random Testing Quiz
 * Aaron Berns, bernsa
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // get random number between 32 and 125 inclusive for ascii character
    // rand () call help from stack overflow #1202687

    return (char)(rand() % (125 + 1 - 32) + 32);
}

char *inputString()
{
    // create 5 char string of random lowercase chars
    char *randomString;
    randomString = malloc(10 * sizeof(char));
    memset(randomString, '\0', 10);
    char *choices = "rest";
    for (int i = 0; i < 9; ++i) {

        // uncomment line below to test 'r', 'e', 's', 't' only
        randomString[i] = choices[((rand() % (4 + 1 - 0) + 0))];

        // uncomment line below to test chars from ' ' to '}'
        //randomString[i] = ((rand() % (125 + 1 - 32) + 32));
    }
    return randomString;
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
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

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
      free(s);
      exit(200);
    }
    free(s);
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
