template< uint16_t w >
struct FixedWidthField {
  /* convenience typedefs */
  template< typename T >
  using ArgumentType =
    std::conditional_t
    < std::is_trivially_copyable< T >::value,
      T, std::add_const_t < std::add_lvalue_reference_t< T > > >;

  constexpr static bool
  isSpace( const char c ){ return c == ' ' or c == '\t'; }

  template< typename Iterator >
  constexpr static bool
  isNewline( const char c, Iterator& it ){
    return
      c == '\n'
      or c == '\f'
      or ( c == '\r'
	   and ( *(++it) == '\n'
		 or []()-> bool {
		   throw std::runtime_error("carriage return unsupported");
		   return false;
		 }() ) );
  }

  constexpr static bool
  isEOF( const char c ){ return c == std::char_traits<char>::eof(); }

  #include "disco/FixedWidthField/src/whiteSpace.hpp"
  
};
