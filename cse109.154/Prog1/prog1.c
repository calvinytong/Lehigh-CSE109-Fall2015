/*
 * CSE 109
 * Calvin Tong
 * cyt219
 * Program Description: reads from standard input and writes back the read characters to standard output 
 * adding filters which are determined by the flags passed in the args
 * Program #1
 * */

#include <stdio.h>
#include <string.h>

//global character buffer for storing words
char buf[256];

/*
 * reverses a null terminated string
 * @param s the null terminated string to be flipped 
 * @param i the length of the string
 */
int reversestr(char *s, int i)
{
 //a is the index for the buffer while b is the index for the copy
 int a, b;
 char scopy[i];
 
 //copy the string so we have something that stays constant to read from as we edit the buffer
 strcpy(scopy, s);
 
 b = 0;

 //iterate through the buffer back to front and the copy front to back so the string reverses
 for(a = i - 1; a >= 0; a--)
 {
  s[a] = scopy[b];
  b++;
 }
 return 0;
}

/*
 * capitalizes a string
 * @param s the null terminated string to be capitalized
 * @param i the length of the string
 */
int capitalizestr(char *s, int i)
{
 int a;
 //iterate through the array changing all fo the characters to uppercase
 for(a = 0; a < i; a++)
 {
  s[a] = toupper(s[a]);
 }
}

/*
 * writes the string out to stdout
 * @param s the null terminated string
 * @param i the length of the string
 */
int write(char *s, int i)
{
 int a;
 //write the buffer to stdout
 for(a = 0; a < i; a++)
 {
  putchar(buf[a]);
 }
}

/*
 * reads from std output and writes to std input with appropriate filters
 * @param upper boolean value representing if the -u flag was passed in
 * @param reverse boolean value representing if the -r flag was passed in
 */
int filter(int upper, int reverse)
{
 char c;
 
 //counter for the while loop 
 int i = 0;

 while((c = getchar()) != EOF)
 {
  //if the character read in is a new line or a space then you have reached the end of a word 
  //so write it out with specified parameters
  if(c == ' ' || c == '\n')
  {
   //set the last character in the array to a null to indicate that the char array is a null terminated string
   buf[i] = '\0';
   
   //for loop counter
   int a;

   //if reverse is true then flip word in place
   if(reverse)
   {
    reversestr(buf, i);
   }
   
   //if upper is true capitilize the word 
   if(upper)
   {
    capitalizestr(buf, i);
   }
   
   //write the buffer to stdout
   write(buf,i);
   
   //reset and get ready to keep iterating
   
   //put a new line or space depending on c
   putchar(c);

   //set the counter to 0 so we can count the letters in the next word
   i = 0;
  }
  //if the character is not a space or a newline then we are still iterating through the array
  else
  {
   //set the char to the correct position in the array and increment the counter 
   buf[i] = c;
   i++;
  }
 }
 return 0; 
}

/* 
 * the main method, in this case it parses the command line args and then calls the write function
 * with the correct parameters
 * @param argc the number of commandline args
 * @param argv the array of strings containing the args
 */
int main(int argc, char *argv[])
{
 //boolean values 
 int upper = 0;
 int reverse = 0;
 
 int i;
 for(i = 1; i < argc; i++)
 { 
  //set the booleans to true if the arg is equal to -u or -r
  if(!strcmp(argv[i], "-u"))
  {
   upper = 1;
   continue;
  }
  
  if(!strcmp(argv[i], "-r"))
  {
   reverse = 1;
   continue;
  }
  
  //this will only run i0f the arg is not equal to -u or -r because of the continues
  //but if it is not a valid arg then write an error to stderr and return 1
  fprintf(stderr, "Invalid command line option: %s\n", argv[i]);
  return 1;
 }
 
 //run the filter function with the correct parameters
 filter(upper, reverse);

 return 0; 
}
