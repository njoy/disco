template< typename Representation, typename Iterator, bool trust = true >
static Representation
read( Iterator& it, const Iterator& end ){
  FixedWidthField_::verifyWidth_( it, end, TrustTag< trust >() );
  
  auto position = FixedWidthField_::skipPad( it );
  if ( position == w
       or FixedWidthField_::isNewline(*it)
       or FixedWidthField_::isEOF(*it) ){ return Representation(0.0); }
  
  const auto sign = Real::parseSign(it, position);

  bool baseSuccess = false;
  auto base = Real::parseBase(it, position, baseSuccess);
  //LOG(INFO) << "base: " << base;
  if ( position == Real::endPosition ){
    ++it;
    return Representation( sign * int64_t( base ) );
  }

  bool fractionSuccess = false;
  const auto decimalPosition = position;
  const auto fraction = Real::parseFraction( it, position, fractionSuccess );
  //LOG(INFO) << "fraction: " << fraction;
  if ( not baseSuccess && not fractionSuccess ){
    const bool succeeded = Real::parseInfinity( it, position );    
    if ( not succeeded || position != w  ){
      throw std::runtime_error("cannot parse invalid real number");
    }
    return sign * std::numeric_limits< Representation >::infinity();
  }

  const auto noFractionDigits =
    fractionSuccess * ( position - decimalPosition - (position != endPosition) );
  //LOG(INFO) << "noFractionDigits: " << noFractionDigits;
  const auto factor =
    integerExponentiation< uint64_t >::cache( noFractionDigits );
  //LOG(INFO) << "factor: " << factor;
  if ( position == Real::endPosition ){
    ++it;
    return sign * ( base + fraction / Representation(factor) );
  }

  const auto exponent = Real::parseExponent( it, position ) - noFractionDigits;
  //LOG(INFO) << "exponent: " << exponent;
  auto encounteredEOL =
    ( FixedWidthField_::isNewline(*it) or FixedWidthField_::isEOF(*it) );

  if ( position != Real::endPosition and not encounteredEOL ){
    throw std::runtime_error
      ("illegal character encountered while parsing real number");
  } else if ( exponent < std::numeric_limits< Representation >::min_exponent10 ){
    return 0.0;
  } else if ( exponent > std::numeric_limits< Representation >::max_exponent10 ){
    return sign * std::numeric_limits< Representation >::infinity();
  } 
  it += not encounteredEOL;
  
  return  sign * int64_t(base * factor + fraction )
    * realExponentiation< Representation >::cache( exponent );
}

template< typename Iterator, bool trust = true >
static double
read( Iterator& it, const Iterator& end ){
  return read<double>( it, end );
}