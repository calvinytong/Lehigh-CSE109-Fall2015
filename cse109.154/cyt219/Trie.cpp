#include <cstdlib>
#include <iostream>
#include "Trie.h"

namespace prog8lib
{
  /*
   * constructor method, create new trie by creating an empty node that acts as the startnode
   */
  Trie::Trie()
  {
   startnode = new TrieNode();
  }
  
  /*
   * destructor method, clean up the object here (not needed in this assignment)
   */
  Trie::~Trie()
  {
  
  }
  
  /*
   * puts a value into a tree for a given key
   * @param key the key with which the value will be retreived
   * @param value the int value to be stored in the trie 
   */
  void Trie::put(string key, int value)
  {
   //pointer holding the current node in the itereation
   TrieNode *current = startnode;
   
   //if the key is empty just return we cannot store those 
   if(key.length() == 0)
   {
    cout << "sorry you must enter a key" << endl;
    return;
   }
   
   //iterate through the key 
   for(uint i = 0; i < key.length(); i++)
   {
     //use the findChar member function to find out whether the char is already in the trie
     TrieNode *next = current->findChar(key[i]);
     
     //branch exists already
     if(next != NULL)
     {
      //keep following the branch
      current = next;
     }
     
     //branch does not exist, write out the rest of the word in a new branch
     else
     {
      current = makeLink(key[i], current);
     }
   }
   //after the key has been written out in the trie, store the value in the last node
   current->value = value;
  }
  
  /*
   * retreives a value from the tree with a given key, returns -1 if the value is not found
   * @param key the key to retreive
   * @return the value stored in the key -1 if the key is not keyed to a value
   */
  int Trie::get(string key)
  {
   //pointer holding the first node in the iteration
   TrieNode *current = startnode;
  
   //iterate through the key
   for(uint i = 0; i < key.length(); i++)
   {
    //use the findChar member function to get the pointer to the next node in the word
    TrieNode* next = current->findChar(key[i]);
    
    //if the node does not exist then the key does not have a value pair
    if(next == NULL)
    {
     return -1;
    }
    //set the current node to the next node and keep iterating
    current = next;
   }
   //return the value that is found
   return current->value;
  }
  
  /*
   * member function that creates a link between the current node and a new node
   * @param c the character to be stored in the link
   * @param current a pointer to the current node
   * @return toadd a pointer to the new node that the member function created
   */
  TrieNode *Trie::makeLink(char c, TrieNode *current)
  { 
   //create new node object
   TrieNode *toadd = new TrieNode();
  
   //create new link pointing to the new node and storing char c
   Link *link = new Link(c, toadd);
  
   //use the numlinks member function to figure out where to put the link
   current->links[current->numlinks] = link;
   
   //increment the number of links
   current->numlinks++;
  
   //return the new node
   return toadd;
  }
} 
  
  
  
