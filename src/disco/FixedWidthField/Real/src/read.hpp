template< typename Representation, typename Iterator, bool trust = true >
static Representation
read( Iterator& it, const Iterator& ){
  auto position = FixedWidthField_::whiteSpace( it );

  if( FixedWidthField_::isNewline(*it, it) or FixedWidthField_::isEOF(*it) ){
    return Representation(0.0);
  }

  if ( position == w ){
    ++it;
    return Representation(0.0);
  }

  const auto value = [&]{
    const auto sign = Real::parseSign(it, position);

    bool baseSuccess = false;
    auto base = Real::parseBase(it, position, baseSuccess);

    if ( position == Real::endPosition ){
      ++it;
      return Representation( sign * int64_t( base ) );
    }

    bool fractionSuccess = false;
    const auto decimalPosition = position;
    const auto fraction = Real::parseFraction( it, position, fractionSuccess );

    const auto noFractionDigits =
        fractionSuccess
        * ( position - decimalPosition - (position != endPosition) );

    if ( position == Real::endPosition ){
      const auto factor =
        realExponentiation< Representation >::cache( -noFractionDigits );

      ++it;
      return sign * ( base + fraction * Representation(factor) );
    }


    if ( unlikely( not baseSuccess && not fractionSuccess ) ){
      const bool succeeded = Real::parseInfinity( it, position );
      if ( unlikely( not succeeded ) ){
        throw std::runtime_error("cannot parse invalid real number");
      }

      std::advance( it, not ( ( position == ( Real::endPosition + 1 ) )
                              or FixedWidthField_::isNewline( *it, it )
                              or FixedWidthField_::isEOF( *it ) ) );

      return sign * std::numeric_limits< Representation >::infinity();
    }

    const auto exponent =
      Real::parseExponent( it, position ) - noFractionDigits;

    std::advance( it, not ( ( position == ( Real::endPosition + 1 ) )
                            or FixedWidthField_::isNewline( *it, it )
                            or FixedWidthField_::isEOF( *it ) ) );
    if ( unlikely( exponent
                   < std::numeric_limits< Representation >::min_exponent10 ) ){
      return sign * 0.0;
    }

    if ( unlikely( exponent
                   > std::numeric_limits< Representation >::max_exponent10 ) ){
      return sign * std::numeric_limits< Representation >::infinity();
    }

    const auto factor =
      integerExponentiation< int64_t >::cache( noFractionDigits );

    return sign * int64_t( base * factor + fraction )
     * realExponentiation< Representation >::cache( exponent );
  }();

  if ( unlikely( not FixedWidthField_::whiteSpace(it, position) ) ){
    throw std::runtime_error("cannot parse invalid real number");
  }

  return value;
}

template< typename Iterator, bool trust = true >
static double
read( Iterator& it, const Iterator& end ){
  return read<double>( it, end );
}
