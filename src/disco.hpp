#ifndef DISCO_HPP
#define DISCO_HPP

#include <algorithm>
#include <array>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <limits>
#include <string>
#include <type_traits>

namespace njoy {
namespace disco {

struct RetainCarriage{};

#include "disco/FixedWidthField.hpp"
#include "disco/FixedWidthField/noDigits.hpp"
#include "disco/FixedWidthField/ColumnPosition.hpp"
#include "disco/FixedWidthField/Real/Pow.hpp"
#include "disco/FixedWidthField/Real/Exponentiation.hpp"
#include "disco/FixedWidthField/Real.hpp"
#include "disco/FixedWidthField/Real/Scientific.hpp"
#include "disco/FixedWidthField/Real/FixedPoint.hpp"
#include "disco/FixedWidthField/Real/ENDF.hpp"
#include "disco/FixedWidthField/Character.hpp"
#include "disco/FixedWidthField/Integer.hpp"
#include "disco/Record.hpp"

}
}

#endif
