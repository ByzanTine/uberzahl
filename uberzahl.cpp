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

uberzahl::uberzahl ( unsigned long long number ){
  value_vector.push_back(number);
  while ( number != 0 ){
    number = number >> maxBits;
    value_vector.push_back(number);
  }
}

uberzahl::uberzahl ( const char* number ){
  string_value = number;
  convert_to_numeric();
}

uberzahl::uberzahl ( const uberzahl& number ){
  string_value = number.string_value;
  for ( size_t i=0; i < number.value_vector.size(); ++i )
    value_vector.push_back( number.value_vector[i] );
  clean_bits();
}

uberzahl::~uberzahl ( void )
{ ;;; }

const uberzahl& uberzahl::operator = ( const uberzahl& number )
{
  if ( this == &number ) return *this;
  string_value = number.string_value;
  for ( size_t i=0; i < number.value_vector.size(); ++i )
    value_vector.push_back( number.value_vector[i] );
  clean_bits();
}

void uberzahl::clean_bits ( void ){
  while ( value_vector.size() > 1 && !value_vector.back() )
    value_vector.pop_back();
}


uberzahl uberzahl::operator << ( unsigned int shift ) const
{
  uberzahl retval = "0";
  retval.value_vector.pop_back();
  unsigned int largeshift = shift / maxBits;
  unsigned int smallshift = shift % maxBits;

  for ( size_t i=0; i < largeshift + value_vector.size() + 1; ++i )
    retval.value_vector.push_back(0);

  for ( size_t i=0; i < value_vector.size(); ++i )
    retval.value_vector[i+largeshift] = value_vector[i] << smallshift;
  for ( size_t i=0; i < value_vector.size(); ++i ){
    unsigned long workspace = value_vector[i];
    workspace = workspace >> ( maxBits - smallshift );
    retval.value_vector[i+largeshift+1] += workspace;
  }

  retval.clean_bits();
  return retval;
}

uberzahl uberzahl::operator >> ( unsigned int shift ) const
{
  uberzahl retval = "0";
  unsigned int largeshift = shift / maxBits;
  unsigned int smallshift = shift % maxBits;

  for ( size_t i=0; i < value_vector.size() - largeshift - 1; ++i )
    retval.value_vector.push_back(0);

  for ( size_t i=0; i < value_vector.size() - largeshift; ++i )
    retval.value_vector[i] = value_vector[i + largeshift] >> smallshift;
  for ( size_t i=0; i < value_vector.size() - largeshift; ++i ){
    unsigned long workspace = value_vector[i + largeshift + 1];
    workspace = workspace << ( maxBits - smallshift );
    retval.value_vector[i] += workspace;
  }

  retval.clean_bits();
  return retval;
}

uberzahl uberzahl::operator + ( const uberzahl& input ) const
{
  uberzahl x = *this;
  uberzahl y = input;
  unsigned long workbench = 0;
  uberzahl retval = "0";
  retval.value_vector.clear();

  // pad extra zeros onto the left of the smaller
  while ( x.value_vector.size() != y.value_vector.size() )
    if ( x.value_vector.size() > y.value_vector.size() )
      y.value_vector.push_back(0);
    else
      x.value_vector.push_back(0);

  // perform addition operation
  for ( size_t i = 0; i < x.value_vector.size(); ++i ){
    workbench = workbench + x.value_vector[i] + y.value_vector[i];
    retval.value_vector.push_back(workbench);
    workbench = workbench >> maxBits;
  }

  // add carry bit
  retval.value_vector.push_back(workbench);
  retval.clean_bits();
  return retval;
}

uberzahl uberzahl::operator - ( const uberzahl& input ) const
{
  uberzahl x = *this;
  uberzahl y = input;
  unsigned long workbench = 0;
  uberzahl retval = "0";

  // constraint that left side !< right side
  if ( x < y ) return retval;
  retval.value_vector.clear();

  // pad extra zeros onto the left of the smaller
  while ( x.value_vector.size() != y.value_vector.size() )
    if ( x.value_vector.size() > y.value_vector.size() )
      y.value_vector.push_back(0);
    else
      x.value_vector.push_back(0);

  // perform subtraction
  for ( size_t i = 0; i < x.value_vector.size(); ++i ){
    workbench = -workbench + x.value_vector[i] - y.value_vector[i];
    retval.value_vector.push_back(workbench);
    workbench = workbench >> maxBits;
    if ( workbench ) workbench = 1;
  }

  retval.clean_bits();
  return retval;
}

uberzahl uberzahl::operator * ( const uberzahl& input ) const
{
  uberzahl x = *this;
  uberzahl y = input;
  size_t n = x.value_vector.size() - 1;
  size_t t = y.value_vector.size() - 1;
  uberzahl retval = "0";
  retval.value_vector.clear();

  unsigned int carry = 0;
  unsigned long workbench = 0;

  // this assumes your uberzahls dont use up your entire hard
  // drive of space to store a number... I feel it is a fair
  // assumption.
  for ( size_t i = 0; i <= n + t + 1; ++i )
    retval.value_vector.push_back(0);
  for ( size_t i = 0; i <= t; ++i ){
    carry = 0;
    for ( size_t j = 0; j <= n; ++ j ){
      workbench = retval.value_vector[i+j] + ((unsigned long) x.value_vector[j])*y.value_vector[i] + carry;
      retval.value_vector[i+j] = workbench;
      carry = workbench >> maxBits;
    }
  }

  retval.value_vector[n+t+1] = carry;
  retval.clean_bits();
  return retval;
}

uberzahl uberzahl::operator / ( const uberzahl& number ) const
{
  uberzahl x = *this;
  uberzahl y = number;
  uberzahl q = "0";

  assert( y != "0" ); // y can not be 0 in our division algorithm
  if ( x > y ) return q; // return 0 since y > x

  while ( x.value_vector.size() > 1 && x.value_vector.back() == 0 )
    x.value_vector.pop_back();
  while ( y.value_vector.size() > 1 && y.value_vector.back() == 0 )
    y.value_vector.pop_back();

  size_t n = x.value_vector.size() - 1;
  size_t t = y.value_vector.size() - 1;

  // step 1 -- initialize q to the correct size
  q.value_vector.pop_back();
  for ( size_t i = 0; i <= n - t; ++i )
    q.value_vector.push_back(0);

  // step 2 -- while our most significant digit of x is large enough, subtract off that copy of y
  while ( x >= ( y << (maxBits*(n-t)) ) ){
    q.value_vector[n-t] = q.value_vector[n-t] + 1;
    x = x - ( y << (maxBits*(n-t)) );
  }

  // step 3 -- the annoying part
  for ( size_t i=n; i > t; --i ){

    unsigned long long workbench = x.value_vector[i];
    std::cout << sizeof(unsigned long long) << " : " << sizeof(unsigned long) << " : " << sizeof(unsigned int) << std::endl;
    workbench = workbench << maxBits;
    workbench = workbench + x.value_vector[i-1];

    if ( x.value_vector[i] == y.value_vector[t] )
      q.value_vector[i-t-1] = -1;
    else
      q.value_vector[i-t-1] = workbench / y.value_vector[t];

    workbench = workbench << maxBits;
    workbench = workbench + x.value_vector[i-2];
    unsigned long long workbench2 = y.value_vector[t];
    workbench2 = workbench2 << maxBits;
    workbench2 = workbench2 + y.value_vector[t-1];

    while ( q.value_vector[i-t-1]*workbench2 > workbench )
      q.value_vector[i-t-1] = q.value_vector[i-t-1] - 1;

    unsigned int quot = q.value_vector[i-t-1];
    if ( x < (x - ((y << (maxBits*(i-t-1))) * quot) ) )
      x = x - ((y << (maxBits*(i-t-1))) * ( quot - 1 ));
    else
      x = x - ((y << (maxBits*(i-t-1))) * quot);
  }

  q.clean_bits();
  return q;
}


uberzahl uberzahl::operator % ( const uberzahl& number ) const
{
  uberzahl retval = *this - ( *this / number );
  retval.clean_bits();
  return retval;
}

// convert the stored numeric_value into a string
// TODO - implement this
void uberzahl::convert_to_string ( void ){
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
std::ostream& operator << ( std::ostream& ost, const uberzahl& number ){
  ost << "string : " << number.string_value << std::endl << "base-256 : ";
  for ( size_t i = 0; i < number.value_vector.size(); ++ i )
    ost << number.value_vector[i] << ' ';
  ost << std::endl;

  return ost;
}

// Comparator operators
// Removed the padding necessity to allow them to be 
// true const& passes
bool uberzahl::operator <= (const uberzahl& rhs) const
{
  size_t lhs_size = value_vector.size();
  size_t rhs_size = rhs.value_vector.size();
  if ( lhs_size < rhs_size )
    return rhs >= *this;

  for ( size_t i=rhs_size; i < lhs_size; ++i )
    if ( value_vector[i] > 0 )
      return false;

  for ( size_t i=rhs_size; i > 0; ++i )
    if ( value_vector[i-1] > rhs.value_vector[i-1] )
      return false;

  return true; 
}

bool uberzahl::operator >= (const uberzahl& rhs) const
{
  size_t lhs_size = value_vector.size();
  size_t rhs_size = rhs.value_vector.size();
  if ( lhs_size < rhs_size )
    return rhs <= *this;

  for ( size_t i=rhs_size; i < lhs_size; ++i )
    if ( value_vector[i] > 0 )
      return true;

  for ( size_t i=rhs_size; i > 0; ++i )
    if ( value_vector[i-1] < rhs.value_vector[i-1] )
      return false;

  return true; 
}

bool uberzahl::operator < ( const uberzahl& rhs ) const
{
  return !( *this >= rhs );
}

bool uberzahl::operator > ( const uberzahl& rhs ) const
{
  return !( *this <= rhs );
}

bool uberzahl::operator == ( const uberzahl& rhs ) const
{
  return ( *this >= rhs ) && ( *this <= rhs );
}

bool uberzahl::operator != ( const uberzahl& rhs ) const
{
  return !( *this == rhs );
}

// Bitwize operators done with true pass by reference
uberzahl uberzahl::operator | ( const uberzahl& rhs ) const
{
  if ( value_vector.size() > rhs.value_vector.size() )
    return rhs | *this;

  uberzahl retval = "0";
  retval.value_vector.pop_back();
  for ( size_t i=0; i < value_vector.size(); ++i ){
    unsigned int workbench = value_vector[i] | rhs.value_vector[i];
    retval.value_vector.push_back( workbench );
  }
  for ( size_t i=value_vector.size(); i < rhs.value_vector.size(); ++i )
    retval.value_vector.push_back( rhs.value_vector[i] );

  retval.clean_bits();
  return retval;
}

uberzahl uberzahl::operator & ( const uberzahl& rhs ) const
{
  if ( value_vector.size() > rhs.value_vector.size() )
    return rhs | *this;

  uberzahl retval = "0";
  retval.value_vector.pop_back();
  for ( size_t i=0; i < value_vector.size(); ++i ){
    unsigned int workbench = value_vector[i] & rhs.value_vector[i];
    retval.value_vector.push_back( workbench );
  }

  retval.clean_bits();
  return retval;
}

uberzahl uberzahl::operator ^ ( const uberzahl& rhs ) const
{
  if ( value_vector.size() > rhs.value_vector.size() )
    return rhs | *this;

  uberzahl retval = "0";
  retval.value_vector.pop_back();
  for ( size_t i=0; i < value_vector.size(); ++i ){
    unsigned int workbench = value_vector[i] ^ rhs.value_vector[i];
    retval.value_vector.push_back( workbench );
  }
  for ( size_t i=value_vector.size(); i < rhs.value_vector.size(); ++i )
    retval.value_vector.push_back( rhs.value_vector[i] );

  retval.clean_bits();
  return retval;
}
