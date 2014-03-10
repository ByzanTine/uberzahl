#include "uberzahl.h"

uberzahl::uberzahl ( void )
  :value(NULL), workbench(NULL), bitsize(0)
{ ;;; }

uberzahl::~uberzahl ( void )
{ ;;; }

uberzahl::uberzahl ( const char* number ); // string or char* ?
const uberzahl& uberzahl::operator = ( const uberzahl& integer ){
}

const uberzahl& uberzahl::operator = ( const char* number ); // string or char*? 
ostream& operator << ( ostream&, uberzahl );

bool uberzahl::operator > ( const uberzahl& );
bool uberzahl::operator < ( const uberzahl& );
bool uberzahl::operator >= ( const uberzahl& );
bool uberzahl::operator <= ( const uberzahl& );
bool uberzahl::operator == ( const uberzahl& );

// arithmetic
const uberzahl& uberzahl::operator + ( const uberzahl& );
const uberzahl& uberzahl::operator - ( const uberzahl& );
const uberzahl& uberzahl::operator * ( const uberzahl& );
const uberzahl& uberzahl::operator / ( const uberzahl& );
const uberzahl& uberzahl::operator % ( const uberzahl& );

// bitwize operators
const uberzahl& uberzahl::operator | ( const uberzahl& );
const uberzahl& uberzahl::operator & ( const uberzahl& );
const uberzahl& uberzahl::operator ^ ( const uberzahl& );
