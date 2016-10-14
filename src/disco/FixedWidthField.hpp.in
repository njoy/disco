#include <type_traits>

namespace disco{

template< uint16_t w >
struct FixedWidthField {

  /* tag structs */
  struct Trusted{};
  struct NotTrusted{};

  /* convenience typedefs */
  template< typename T >
  using ArgumentType =
    std::conditional_t
    < std::is_trivially_copyable< T >::value,
      T, std::add_const_t < std::add_lvalue_reference_t< T > > >;

  template< bool trust >
  using TrustTag = std::conditional_t< trust, Trusted, NotTrusted >;

  /* helper methods */
  template< typename Iterator >
  static void
  verifyWidth_( Iterator, Iterator, Trusted ){} 

  template< typename Iterator >
  static void
  verifyWidth_( Iterator begin, Iterator end, NotTrusted ){
    if (  w > std::distance( begin, end ) ){ throw std::exception(); }
  }
  
  constexpr static bool
  isSpace( const char c ){ return c == ' ' || c == '\t'; }

  constexpr static bool
  isNewline( const char c ){ return c == '\n' || c == '\f' || c == '\r'; }

  constexpr static bool
  isEOF( const char c ){ return c == std::char_traits<char>::eof(); }

#include "disco/FixedWidthField/src/skipPad.hpp"
  
};

}
