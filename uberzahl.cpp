#include<iostream>
#include<string>
#include<vector>
#include<assert.h>

#include"uberzahl.h"
#define maxBits (8 * sizeof(int))

uberzahl::uberzahl ( void )
  : string_value("0")
{
  convert_to_numeric();
}

uberzahl::uberzahl ( const char* number ){
  string_value = number;
  convert_to_numeric();
}

uberzahl::~uberzahl ( void )
{ ;;; }

const uberzahl& uberzahl::operator = ( const char* number ){
  string_value = number;
  convert_to_numeric();
}

const uberzahl& uberzahl::operator = ( const uberzahl& number ){
  string_value = number.string_value;
  convert_to_numeric();
}

// take the string_value and convert it into a numeric_value
void uberzahl::convert_to_numeric ( void ){
  std::string workbench = string_value;
  value_vector.clear();
  unsigned int numeric_value = 0;
  size_t bits = 0;

  while ( workbench.length() ){
    ++bits;

    size_t len = workbench.length();
    numeric_value = numeric_value >> 1;
    if ( workbench[len-1] % 2 == 1 ){
      numeric_value = numeric_value | ( 1 << (maxBits-1) );
      workbench[len-1] = workbench[len-1] ^ 1;
    }
    
    for ( size_t i = workbench.length(); i > 0; --i ){
      // constant consistancy check! if this algorithm fails I want to know
      assert( workbench[i-1] >= '0' && workbench[i-1] <= '9' );

      if ( workbench[i-1] % 2 ){ // odd decimal digit
        workbench[i] += 0x05; // adjust the lower term up
      }
      workbench[i-1] -= '0'; // cut off 0x30 ascii
      workbench[i-1] = workbench[i-1] >> 1; // divide by 2
      workbench[i-1] += '0'; // add back the ascii
    }

    while ( workbench[0] == '0' )
      workbench = workbench.substr(1,len);

    // we have run out of room in numeric_value
    if ( bits % maxBits == 0 ){
      value_vector.push_back(numeric_value);
      numeric_value = 0;
    }
  }

  // take care of the remaining bits
  numeric_value = numeric_value >> (-bits % maxBits);
  value_vector.push_back(numeric_value);
}

// printing operator -- currently only for debug purposes
// prints the string and the associated vector
// [string]
// [low order] [higher order] [higher order] ... [highest order]
std::ostream& operator << ( std::ostream& ost, uberzahl& number ){
  ost << number.string_value << std::endl;
  for ( std::vector<unsigned int>::iterator it = number.value_vector.begin();
      it != number.value_vector.end(); ++it )
    ost << *it << ' ';
  ost << std::endl;

  return ost;
}
