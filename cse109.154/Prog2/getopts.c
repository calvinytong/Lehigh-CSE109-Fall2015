#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char **strarray;

char **getopts(char cmd[])
{
 char *token;
 int tokcount;

 int len = strlen(cmd);
 char copy[len + 1];
 strcpy(cmd, copy);

 token = strtok(copy, " ");
 tokcount = 1;
 while(token != NULL)
 {
  token = strtok(NULL, cmd);
  tokcount++;
 }

 strarray = malloc((tokcount + 1) * sizeof(char*));
 
 printf("first malloc \n"); 
 
 int i = 0;

 token = strtok(cmd, " ");
 printf("token \n");
 strarray[i] = malloc((strlen(token) + 1) * sizeof(char));
 printf("second malloc\n");
 strcpy(strarray[i], token);
 printf("first token");
 while(token != NULL)
 {
  token = strtok(NULL, cmd);
  strarray[i] = malloc((strlen(token) + 1) * sizeof(char));
  strcpy(strarray[i], token);
  i++;
  printf("sup i'm a while loop \n");
 }

 strarray[i] = "0";
 return strarray;
}
