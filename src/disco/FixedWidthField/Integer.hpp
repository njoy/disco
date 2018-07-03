template< uint16_t w, uint16_t m = std::numeric_limits<uint16_t>::max() >
struct Integer : public FixedWidthField< w >{

  using FixedWidthField_ = FixedWidthField< w >;

  struct Signed{};
  struct Unsigned{};

  struct WithPadding{};
  struct WithoutPadding{};

  using ZeroPaddingPolicy =
    std::conditional_t< m == std::numeric_limits<uint16_t>::max(),
                        WithoutPadding, WithPadding >;

  template<typename T>
  struct Type{};

  template<typename T>
  static constexpr Type<T> type_c{};

  /* helpers */
  #include "disco/FixedWidthField/Integer/src/parseInteger.hpp"

  /* methods */
  #include "disco/FixedWidthField/Integer/src/read.hpp"

  template< typename Iterator >
  static void write( Iterator& it ){
    ColumnPosition< w >::write( it );
  }

  template< typename Representation, typename Iterator >
  static void
  write( Representation integer, Iterator& it ){
    write( integer, it, ZeroPaddingPolicy() );
  }

  #include "disco/FixedWidthField/Integer/src/write.hpp"
  #include "disco/FixedWidthField/Integer/src/writeInvalid.hpp"
};

