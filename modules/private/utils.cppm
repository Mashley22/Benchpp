export module Benchpp:priv.utils;

namespace benchpp {

namespace priv {

void
terminate(void);

#ifdef BENCHPP_TEST
[[nodiscard]]
bool
has_terminated(void);

void
undo_terminate(void);
#endif

}

}
