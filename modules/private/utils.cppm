export module Benchpp:priv.utils;

namespace benchpp {

namespace priv {

void
terminate(void);

#ifdef BENCHPP_TEST
export
[[nodiscard]]
bool
has_terminated(void);

export
void
undo_terminate(void);
#endif

}

}
