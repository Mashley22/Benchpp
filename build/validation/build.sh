EXTRA_ARGS="-DCMAKE_EXPORT_COMPILE_COMMANDS=y -DBENCHPP_TEST=y"


if command -v ninja &> /dev/null; then
    cmake ../.. -G Ninja "$EXTRA_ARGS"
else
    cmake ../.. "$EXTRA_ARGS"
fi
