#ifndef UBERZAHL_H
#define UBERZAHL_H
#include<iostream>

class uberzahl {
  public:
    uberzahl ( void );
    ~uberzahl ( void );
    
    uberzahl ( const char* number ); // string or char* ?
    const uberzahl& operator = ( const uberzahl& );
    const uberzahl& operator = ( const char* number ); // string or char*? 
    
    unsigned int* value;
    friend ostream& operator << ( ostream&, uberzahl );

  private:
    unsigned int* workbench;
    unsigned int bitsize;

    // comparators
    bool operator > ( const uberzahl& );
    bool operator < ( const uberzahl& );
    bool operator >= ( const uberzahl& );
    bool operator <= ( const uberzahl& );
    bool operator == ( const uberzahl& );

    // arithmetic
    const uberzahl& operator + ( const uberzahl& );
    const uberzahl& operator - ( const uberzahl& );
    const uberzahl& operator * ( const uberzahl& );
    const uberzahl& operator / ( const uberzahl& );
    const uberzahl& operator % ( const uberzahl& );

    // bitwize operators
    const uberzahl& operator | ( const uberzahl& );
    const uberzahl& operator & ( const uberzahl& );
    const uberzahl& operator ^ ( const uberzahl& );
}

#endif
