class uberzahl {
  public:
    uberzahl ( void );
    ~uberzahl ( void );
    
    uberzahl ( const string& ); // string or char* ?
    const uberzahl& operator = ( const uberzahl& );
    const uberzahl& operator = ( const string& ); // string or char*? 
    
    unsigned int* value;
    friend ostream& operator << ( ostream&, uberzahl );

  private:
    unsigned int* workbench;
    unsigned int bitsize;

    // comparitors
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
