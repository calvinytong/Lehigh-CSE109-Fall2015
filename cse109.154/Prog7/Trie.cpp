#include <cstdlib>
#include <iostream>
#include "Trie.h"
#include <algorithm>
#include <sstream>
#include <iterator>
#include <iomanip>

/*
 * constructor method, create new trie by creating an empty node that acts as the startnode
 */
Trie::Trie():numkeys(0)
{
 startnode = new Node();
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
void Trie::put(string key, string value)
{
 //pointer holding the current node in the itereation
 Node *current = startnode;

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
   Node *next = current->findChar(key[i]);

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

 keys[numkeys] = key;
 numkeys++;
}

/*
 * retreives a value from the tree with a given key, returns -1 if the value is not found
 * @param key the key to retreive
 * @return the value stored in the key -1 if the key is not keyed to a value
 */
string Trie::get(string key)
{
 //pointer holding the first node in the iteration
 Node *current = startnode;

 //iterate through the key
 for(uint i = 0; i < key.length(); i++)
 {
  //use the findChar member function to get the pointer to the next node in the word
  Node* next = current->findChar(key[i]);

  //if the node does not exist then the key does not have a value pair
  if(next == NULL)
  {
   return "";
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
Node *Trie::makeLink(char c, Node *current)
{
 //create new node object
 Node *toadd = new Node();

 //create new link pointing to the new node and storing char c
 Link *link = new Link(c, toadd);

 //use the numlinks member function to figure out where to put the link
 current->links[current->numlinks] = link;

 //increment the number of links
 current->numlinks++;

 //return the new node
 return toadd;
}

//prints out the trie in plain text
void Trie::printPlainText()
{
 for(int a = 0; a < this->numkeys; a++)
 {
  unsigned int x;
  stringstream ss;
  ss << hex << this->get(this->keys[a]);
  ss >> x;
  cout << static_cast<int>(x) << " " << this->keys[a] << endl;
 }
 cout << endl;
}

//changes ascii to hex string
string asciiToHex(string s)
{
 ostringstream result;
 if(s[0] == '0' && s.length() == 2)
 {
  s = s.substr(1);
 }
 result << setw(2) << setfill('0') << hex << nouppercase;
 std::copy(s.begin(), s.end(), ostream_iterator<unsigned int>(result, ""));
 return result.str();
}

//overloaded << operator to print to file
ostream& operator<<(ostream& out, Trie& t)
{
 for(int i = 0; i < t.numkeys; i++)
 {
  out << t.get(t.keys[i]) << asciiToHex(t.keys[i]) << "ff";
 }
 out << "aa";
 return out;
}
