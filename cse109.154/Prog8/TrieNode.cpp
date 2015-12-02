#include <cstdlib>
#include "TrieNode.h"

namespace prog8lib
{
  //using a macro for array size to eliminate magic numbers
  #define ARRAY_SIZE 26
  
  /*
   * constructor that takes in an int value and sets it to value
   * @param v the value to be stored in the node
   */
  TrieNode::TrieNode(int v):value(v), numlinks(0)
  {
   links = new Link *[ARRAY_SIZE]; 
  }
  
  /*
   * default constructor sets the value of the node to '\0' by default
   */
  TrieNode::TrieNode():value('\0'), numlinks(0)
  {
   links = new Link *[ARRAY_SIZE]; 
  }
  
  /* 
   * destructor method deletes the dynamically allocated links array
   */
  TrieNode::~TrieNode()
  {
   delete []links;
  }
  
  /*
   * member function that finds if char c is already linked into the current node
   * @param c the character to find
   * @return NULL if the character is not found a pointer to the next node if it is found
   */
  TrieNode *TrieNode::findChar(char c)
  {
   //iterate through the array for number of links
   for(int i = 0; i < numlinks; i++)
   {
    //set the pointer to the current link
    Link *current = links[i];
  
    //if the link is equal to c then return the pointer to the node
    if(current->letter == c)
    {
     return current->next;
    }
   }
   //if the character is not found return NULL
   return NULL;
  }
}
