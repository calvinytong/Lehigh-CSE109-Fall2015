#ifndef Link_H
#define Link_H

using namespace std;

namespace prog8lib
{
  class TrieNode;
  class Link
  {
   //the assignment said to have all public members, note that this is not best practice
   public:
    //the letter held in the link
    char letter;
    
    //pointer to the next node
    TrieNode *next;
  
    //constructor
    Link(char l, TrieNode *n);
    
    //destructor
    ~Link();
  };
}
#endif
