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
    
    friend std::ostream& operator << ( std::ostream&, const uberzahl& );
    
    // arithmetic - not true pass by references :(
    uberzahl operator + ( const uberzahl& ) const;
    uberzahl operator - ( const uberzahl& ) const;
    uberzahl operator * ( const uberzahl& ) const;
    uberzahl operator / ( const uberzahl& ) const; // Alex Check
    uberzahl operator % ( const uberzahl& ) const;
    
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
    uberzahl operator >> ( unsigned int ) const;
    uberzahl operator << ( unsigned int ) const;

    // Emily Update
    // inverses

    // uses the rand function - to seed use srand (unsigned int seed);
    uberzahl random ( unsigned int );

  private:
    std::string string_value;
    std::vector<unsigned int> value_vector;
    void convert_to_numeric ( void );
    void convert_to_string ( void ); // Emily do this too
    void clean_bits ( void );
};

#endif
