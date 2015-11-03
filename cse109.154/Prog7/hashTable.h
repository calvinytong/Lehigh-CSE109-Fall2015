#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "hash.h"
#include "link.h"
#include <iostream>
#include <cstring>

using namespace std;

class HashTable{
public:
  HashTable(int n=97);
  HashTable(const HashTable &t);
  ~HashTable();

  HashTable& add(const char *str, double d);

  bool inTable(const char *)const;

  double& operator [](const char *);

  const double operator [](const char *) const;

  HashTable& operator += (const char *);

  void remove(const char *);

  friend ostream& operator<<(ostream &out,const HashTable& h);
  
private:
  int size;   //the size of the array table
  Link **table;  //dynamically allocated array of pointers, each
		 //pointer pointing to a linked list of Links or NULL

  // return true if and only iff k is a positive prime
  bool prime(int k);

  // if b is true do nothing, else display on cerr the error message and exit
  static void check(bool b, const char *mess);
};

#endif
