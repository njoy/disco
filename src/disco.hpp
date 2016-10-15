#ifndef DISCO_HPP
#define DISCO_HPP

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <limits>
#include <type_traits>

namespace disco {

template< uint16_t w >
struct FixedWidthField;

template< uint16_t w = 1 >
struct ColumnPosition;

template< uint16_t w = 1 >
struct Character;

template< uint16_t w, uint16_t m = std::numeric_limits<uint16_t>::max() >
struct Integer;

template< uint16_t w >
struct Real;

template< uint16_t w, uint16_t d,
          uint16_t e = std::numeric_limits<uint16_t>::max() >
struct Scientific;

template< uint16_t w, uint16_t d >
struct FixedPoint;

struct ENDF;

template < typename... Components >
struct Record;

struct RetainCarriage{};

}

#include "disco/FixedWidthField.hpp"
#include "disco/FixedWidthField/noDigits.hpp"
#include "disco/FixedWidthField/ColumnPosition.hpp"
#include "disco/FixedWidthField/Real/Pow.hpp"
#include "disco/FixedWidthField/Real/Exponentiation.hpp"
#include "disco/FixedWidthField/Real.hpp"
#include "disco/FixedWidthField/Real/Scientific.hpp"
#include "disco/FixedWidthField/Real/FixedPoint.hpp"
#include "disco/FixedWidthField/Real/ENDF.hpp"
#include "disco/FixedWidthField/Integer.hpp"
#include "disco/FixedWidthField/Character.hpp"
#include "disco/Record.hpp"

namespace disco {

template< uint16_t w = 1 >
using X = ColumnPosition< w >;

template< uint16_t w = 1 >
using A = Character< w >;

template< uint16_t w, uint16_t m = std::numeric_limits<uint16_t>::max() >
using I = Integer< w, m >;

template< uint16_t w, uint16_t d,
          uint16_t e = std::numeric_limits<uint16_t>::max() >
using Es = Scientific< w, d, e >;

template< uint16_t w, uint16_t d >
using F = FixedPoint< w, d >;

}

#endif
