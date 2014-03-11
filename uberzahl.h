#ifndef UBERZAHL_H
#define UBERZAHL_H
#include<iostream>
#include<string>
#include<vector>

class uberzahl {
  public:
    uberzahl ( void );
    ~uberzahl ( void );
    uberzahl ( const char* );
    
    const uberzahl& operator = ( const char* ); 
    const uberzahl& operator = ( const uberzahl& );
    
    friend std::ostream& operator << ( std::ostream&, uberzahl& );

  private:
    std::string string_value;
    std::vector<unsigned int> value_vector;
    void convert_to_numeric ( void );

    // TO IMPLEMENT
    void convert_to_string ( void );
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
};

#endif
