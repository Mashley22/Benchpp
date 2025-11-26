EXTRA_ARGS="-DBENCHPP_BUILD_SAMPLES=ON"


if command -v ninja &> /dev/null; then
    cmake ../.. -G Ninja "$EXTRA_ARGS"
else
    cmake ../.. "$EXTRA_ARGS"
fi
