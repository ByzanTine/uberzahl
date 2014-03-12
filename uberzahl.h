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
    uberzahl ( unsigned long long );
    uberzahl ( const uberzahl& );
    const uberzahl& operator = ( const uberzahl& );
    
    friend std::ostream& operator << ( std::ostream&, uberzahl );
    
    // arithmetic
    uberzahl operator + ( const uberzahl& ) const;
    uberzahl operator - ( const uberzahl& ) const;
    uberzahl operator * ( const uberzahl& ) const;
    uberzahl operator / ( const uberzahl& ) const;
    uberzahl operator % ( const uberzahl& ) const;
    
    // comparators
    bool operator > ( const uberzahl );
    bool operator < ( const uberzahl );
    bool operator >= ( const uberzahl );
    bool operator <= ( const uberzahl );
    bool operator == ( const uberzahl );
    bool operator != ( const uberzahl );
    
    // bitwize operators
    uberzahl operator | ( uberzahl );
    uberzahl operator & ( uberzahl );
    uberzahl operator ^ ( uberzahl );
    uberzahl operator >> ( unsigned int ) const;
    uberzahl operator << ( unsigned int ) const;

  private:
    std::string string_value;
    std::vector<unsigned int> value_vector;
    void convert_to_numeric ( void );
    void convert_to_string ( void );
    void clean_bits ( void );
};

#endif
