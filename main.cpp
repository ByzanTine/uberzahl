#include <iostream>
using namespace std;
#include "uberzahl.h"

/*const string& string::operator - ( void ){
  size_t length = this->len();

  for ( size_t i=length; i>0; --i )
    if ( this[i] == '0' )
      this[i] = '9';
    else{
      this[i] = this[i]-1;
      break
    }

  // trim off the leading zeros
  while ( this[0] == '0' )
    this = this + 1;
  // allow one zero if we trimmed everything off
  if ( this == '\0' )
    this = '0'
  return this;
}*/

int main( void ){
  uberzahl a = "4294967296";
  cout << a << endl;
}
