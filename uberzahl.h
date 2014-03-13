#ifndef UBERZAHL_H
#define UBERZAHL_H
#include<iostream>
#include<string>
#include<vector>

#define smallType unsigned short
#define mediumType unsigned int
#define largeType unsigned long long

class uberzahl {
  public:
    uberzahl ( void );
    ~uberzahl ( void );
    uberzahl ( const char* );
    uberzahl ( largeType );
    uberzahl ( const uberzahl& );
    const uberzahl& operator = ( const uberzahl& );
    
    friend std::ostream& operator << ( std::ostream&, const uberzahl& );
    
    // arithmetic - not true pass by references :(
    uberzahl operator + ( const uberzahl& ) const;
    uberzahl operator - ( const uberzahl& ) const;
    uberzahl operator * ( const uberzahl& ) const;
    uberzahl operator / ( const uberzahl& ) const; // Alex Check
    uberzahl operator / ( smallType ) const;
    uberzahl operator % ( const uberzahl& ) const;
    smallType operator % ( smallType ) const;
    
    // comparators
    bool operator > ( const uberzahl& ) const;
    bool operator < ( const uberzahl& ) const;
    bool operator >= ( const uberzahl& ) const;
    bool operator <= ( const uberzahl& ) const;
    bool operator == ( const uberzahl& ) const;
    bool operator != ( const uberzahl& ) const;
    
    // bitwize operators
    uberzahl operator | ( const uberzahl& ) const;
    uberzahl operator & ( const uberzahl& ) const;
    uberzahl operator ^ ( const uberzahl& ) const;
    uberzahl operator >> ( smallType ) const;
    uberzahl operator << ( smallType ) const;

    // Emily Update
    // inverses

    // uses the rand function - to seed use srand (unsigned int seed);
    uberzahl random ( largeType );

  private:
    std::string string_value;
    std::vector<smallType> value_vector;
    void convert_to_numeric ( void );
    std::string convert_to_string ( void ) const; // Emily do this too
    void clean_bits ( void );
};

#endif
