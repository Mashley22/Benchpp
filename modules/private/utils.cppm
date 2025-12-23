export module Benchpp:priv.utils;

namespace benchpp {

namespace priv {

void
terminate(void);

#ifdef BENCHPP_TEST
export class TerminateCalled {};
#endif

}

}
