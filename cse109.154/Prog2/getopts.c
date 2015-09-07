/*
 * CSE 109
 * Calvin Tong
 * cyt219
 * implements the getopts prototype defined in prog2.c, parses the args the user enters
 * Program #2
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * parses the users command line argument and returns them in a string array
 * @param command that the user types in stdin
 * @return char** the string array holding the tokenized cmdline args with a 0 as the last element
 */
char **getopts(char cmd[])
{
 //the string array that will hold the parsed command line args
 char **strarray;
 
 //copy the array into a new string array so we can use strtok to count the args without editing 
 //the original string
 int len = strlen(cmd);
 char copy[len + 1];
 strcpy(copy, cmd);
 
 //the number of tokens that have been read
 int tokcount = 0;

 //count the number of tokens in the inputed array
 //gets the first token in the string
 char *token = strtok(copy, " ");
 while(token != NULL)
 {
  //increment the token counter
  tokcount++;
  //grab the next token
  token = strtok(NULL, " ");
 }
 
 //use the number of tokens found to dynamically allocate the string array
 //adding 1 because we need to put a 0 onto the end of the array
 strarray = malloc((tokcount + 1) * sizeof(char*));
 
 //reset the tok count to 0 for the second iteration
 //on this iteration it is used as an index rather than just a count
 tokcount = 0;

 //since the copied array has been modified during the token count use the cmd array
 //for the second iteration
 
 //grab the first token
 token = strtok(cmd, " ");
 while(token != NULL)
 {
  //use the length of the token to dynamically allocate elements of strarray
  //adding one to acomidate the null termination
  strarray[tokcount] = malloc((strlen(token) + 1) * sizeof(char));

  //copy the token into the correct index of the string array
  strcpy(strarray[tokcount], token);

  //increment the token count
  tokcount++;

  //grab the next token
  token = strtok(NULL, " ");
 }
 
 //put a 0 onto the end of the array and then return the parsed opts
 strarray[tokcount] = 0;
 return strarray;
}
