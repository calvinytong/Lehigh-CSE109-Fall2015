#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char **getopts(char cmd[]);
char buf[256];
char hostname[256];

int main(int argc, char *argv[])
{
 gethostname(hostname, 256);
 
 while(1)
 {
  printf("%s> ", hostname);
  fgets(buf, 256, stdin);
  int len = strlen(buf);
  buf[len - 1] = '\0';
 
  printf("chopy chopy %s\n", buf);

  if(strcmp(buf, "exit") == 0)
  {
   return 0;
  }
  
  printf("cmp cmp\n");

  argv = getopts(buf);
  
  printf("got le opts\n");
  
  if(fork() == 0)
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
