#include <type_traits>

#include "utility/TypeSwitch.hpp"

namespace disco{

template< uint16_t w >
struct FixedWidthField {

  /* tag structs */
  struct Trusted{};
  struct NotTrusted{};

  /* convenience typedefs */
  template< typename T >
  using ArgumentType =
    typename utility::TypeSwitch
             < T, typename std::add_const
                           < typename std::add_lvalue_reference
                                      < T >::type >::type,
               std::is_trivially_copyable< T >::value >::type;

  template< bool trust >
  using TrustTag = typename utility::TypeSwitch
                            < Trusted, NotTrusted, trust >::type;

  /* psuedo partial function specialization */
  template< typename Iterator >
  static void verifyWidth_( Iterator begin, Iterator end, Trusted ){} 

  template< typename Iterator >
  static void verifyWidth_( Iterator begin, Iterator end, NotTrusted ){
    if (  w > std::distance( begin, end ) ){ throw std::exception(); }
  }

  /* helper methods */
  template< bool trust, typename Iterator >
  static void verifyWidth( Iterator begin,Iterator end ){
    verifyWidth_( begin, end, TrustTag< trust >() );
  }
  
  constexpr static bool
  isSpace( const char c ){
    return c == ' ' || c == '\t' || c == '\n'
           || c == '\v' || c == '\f' || c == '\r';
  }

  template< typename Iterator >
  static uint16_t
  skipPad( Iterator& it ){
    constexpr uint16_t endPosition = w - 1;
    uint16_t position = 0;
    while( FixedWidthField::isSpace( *it ) ){
      ++it; ++position;
      if ( position == endPosition ){ break; } 
    }
    return position;
  }
    
};

}
