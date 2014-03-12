#include <iostream>
using namespace std;
#include "uberzahl.h"

int main( void ){
  unsigned int x = -2;
  uberzahl a = x;
  uberzahl b = "5";
  cout << (a + 1);
  cout << (a + 1) * 2;
}
