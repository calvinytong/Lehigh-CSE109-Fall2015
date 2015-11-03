#include "hash.h"

Hash::Hash(const char *str) {
  int tmp = 0;
  const char *p = str;
  while(*p) {
    tmp += *p++;
  }
  key = abs(tmp);
}

int Hash::hash() const{
  return key;
}
