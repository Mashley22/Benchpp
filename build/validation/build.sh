EXTRA_ARGS="-DBENCHPP_TEST=ON"


if command -v ninja &> /dev/null; then
    cmake ../.. -G Ninja "$EXTRA_ARGS"
else
    cmake ../.. "$EXTRA_ARGS"
fi
