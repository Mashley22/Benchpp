module;

#include <exception>

export module Benchpp:lnx.exception.mem;
import :mem;

export namespace benchpp {

namespace mem {

namespace lnx {

class OpenStatusFileErr : Error {};

class KeyNotFoundErr : Error {};

class StrTo_ull_Err : Error {};

class LineParseErr: Error {};

}

}

}
