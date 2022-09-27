template< uint16_t w >
struct Real : public FixedWidthField< w >{

  /* tag structs */
  struct MayConsumeExponent{};
  struct MayNotConsumeExponent{};

  struct Full{};
  struct PartialNegative{};
  struct Partial{};

  /* constants */
  static constexpr uint16_t width = w;

  template< typename Iterator >
  static void write( Iterator& it ){ ColumnPosition< w >::write( it ); }

  /* helpers */
  #include "disco/FixedWidthField/Real/src/parseSign.hpp"
  #include "disco/FixedWidthField/Real/src/parseBase.hpp"
  #include "disco/FixedWidthField/Real/src/parseFraction.hpp"
  #include "disco/FixedWidthField/Real/src/parseExponent.hpp"
  #include "disco/FixedWidthField/Real/src/parseInfinity.hpp"

  /* methods */
  #include "disco/FixedWidthField/Real/src/read.hpp"

};
