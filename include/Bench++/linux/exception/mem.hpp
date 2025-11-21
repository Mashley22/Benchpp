#ifndef BENCHPP_LINUX_EXCEPTION_MEM_HPP
#define BENCHPP_LINUX_EXCEPTION_MEM_HPP

#include <Bench++/mem.hpp>

namespace benchpp {

namespace mem {

namespace lnx {

class OpenStatusFileErr : Error {};

class KeyNotFoundErr : Error {};

class StrTo_ull_Err : Error {};

class LineParseErr: Error {};

}

}

}

#endif /* BENCHPP_LINUX_MEM_HPP */
