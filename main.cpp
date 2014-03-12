#include <iostream>
using namespace std;
#include "uberzahl.h"

int main( void ){
  uberzahl a = 9;
  uberzahl b = a << 63;
  uberzahl c = b >> 64;
  cout << a+"0";
  cout << b+"0";
  cout << c+"0";
}
