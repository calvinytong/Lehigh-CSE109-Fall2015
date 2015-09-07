/*
 * CSE 109
 * Calvin Tong
 * cyt219
 * implements a simple cli into which the user types simple unix commands which are parsed and executed by the program
 * Program #2
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

//prototype for the getopts methods which is defined in getopts.c
char **getopts(char cmd[]);

/*
 * the main method
 * @param argc the number of command line args
 * @#param argv the array containg the cmdline args
 */
int main(int argc, char *argv[])
{
 //the string which holds the command read from stdin
 char buf[256];

 //the string that holds the name of the host computer 
 char hostname[100];
 
 //gets the host name of the computer. Only runs once 
 //because we are assmuing host machine will not change during runtime
 gethostname(hostname, 256);
 
 //infinite loop, breaks once the user types exit
 while(1)
 {
  //prompt the user with a string with format  hostname>
  printf("%s> ", hostname);
  
  //read in the command from stdin and store it in buf
  fgets(buf, 256, stdin);
  
  //chop off the \n character that is read in by fgets
  int len = strlen(buf);
  buf[len - 1] = '\0';
  
  //if the user typed in exit then break out of the loop
  if(strcmp(buf, "exit") == 0)
  {
   break;
  }
  
  //run the getopts method to parse command line args and assign
  //the parsed args to argv
  argv = getopts(buf);
  
  //not my code, taken from the assignment page
  //runs the parsed command line args
  if (fork() == 0)
  {
   execvp(argv[0], argv);
  } 
  else 
  {
   wait(NULL);
  }
 }
 return 0;
}
