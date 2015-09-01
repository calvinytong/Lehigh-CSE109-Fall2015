/*
 * CSE 109
 * Calvin Tong
 * cyt219
 * Program Description:
 * Program #1
 * */

#include <stdio.h>
#include <string.h>

int write(int upper, int reverse)
{
 char c;
 char buf[256];
 int i = 0;

 while((c = getchar()) != EOF)
 {
  if(c == ' ' || c == '\n')
  {  
   buf[i] = '\0';
   int a;
   if(reverse)
   {
    for(a = i - 1; a >= 0; a--)
    {
     if(upper)
      putchar(toupper(buf[a]));
     else
      putchar(buf[a]);
    }
   }
   else
   {
    for(a = 0; a < i; a++)
    {
     if(upper)
      putchar(toupper(buf[a]));
     else
      putchar(buf[a]);
    }
   }
   
   putchar(' ');
   
   if(c == '\n')
    putchar('\n');  
 
   i = 0;
  }
  else
  {
   buf[i] = c;
   i++;
  }
 }
 return 0; 
}

int main(int argc, char *argv[])
{
 int upper = 0;
 int reverse = 0;
 int i;

 for(i = 1; i < argc; i++)
 { 
  if(strcmp(argv[i], "-u") == 0)
  {
   upper = 1;
   continue;
  }
  
  if(strcmp(argv[i], "-r") == 0)
  {
   reverse = 1;
   continue;
  }  
  //perror("Invalid command line option");
 }
 write(upper, reverse);

 return 0; 
}
