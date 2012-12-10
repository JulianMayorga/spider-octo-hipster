/*
   The  program  below uses nested loops that employ strtok_r() to break a string into a two-level hierarchy of tokens.
   The first command-line argument specifies the string to be parsed.  The  second  argument  specifies  the  delimiter
   character(s)  to  be  used  to separate that string into "major" tokens.  The third argument specifies the delimiter
   character(s) to be used to separate the "major" tokens into subtokens.

   An example of the output produced by this program is the following:

     $ ./a.out 'a/bbb///cc;xxx:yyy:' ':;' '/'
      1: a/bbb///cc
      --> a
      --> bbb
      --> cc
      2: xxx
      --> xxx
      3: yyy
      --> yyy
      
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../file.h"
int main(int argc, char *argv[])
{
  char* url_buffer = NULL;
  char *str1, *str2, *token, *subtoken;
  char *saveptr1, *saveptr2;
  int j;

  url_buffer = file_to_buffer("../../url_frontier.csv");

  for (j = 1, str1 = url_buffer; ; j++, str1 = NULL) {
    token = strtok_r(str1, ";", &saveptr1);
    if (token == NULL)
      break;
    printf("%d: %s\n", j, token);

    for (str2 = token; ; str2 = NULL) {
      subtoken = strtok_r(str2, ",", &saveptr2);
      if (subtoken == NULL)
        break;
      printf(" --> %s\n", subtoken);
    }


  }
}
