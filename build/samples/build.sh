SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
echo $SCRIPT_DIR
source $SCRIPT_DIR/../build_core.sh

EXTRA_ARGS="-DBENCHPP_BUILD_SAMPLES=ON"

eval $BASE_CMAKE_BUILD_COMMAND $EXTRA_ARGS $@
