#! /bin/bash

#
# This script is used by Uintah's configure to build the PIDX thirdparty library
#
# $1 - location to build the 3P
# $2 - whether Uintah is being built in debug mode or not...
#

PIDX_TAG="tags/v0.9"

PIDX_DIR=$1

############################################################################

show_error()
{
    echo ""
    echo "An error occurred in the buid_pidx.sh script:"
    echo ""
    echo "  The error was from this line: $@"
    echo ""
    exit 1
}

############################################################################
# Run() runs the command sent in, and tests to make sure it succeeded.

run()
{
    echo "$@"
    eval $@
    if test $? != 0; then
        show_error "$@"
    fi
}

############################################################################

echo   ""
echo   "------------------------------------------------------------------"
echo   "Building PIDX Library..."
echo   ""
echo   ""
echo   "    Using Cmake: "`which cmake`
echo   ""
echo   "------------------------------------------------------------------"

run "cd $PIDX_DIR"

if  [ ! -d "./build" ]; then
  run "git init"
  run "git remote add -t master origin https://github.com/sci-visus/PIDX.git"
  run "mkdir build"
fi

run "git fetch --depth=1 --prune origin \"$PIDX_TAG\""
run "git checkout FETCH_HEAD"

run "cd build"

if test $2 != "no"; then
  DEBUG="-DCMAKE_BUILD_TYPE=Debug"
fi

run \
  "cmake \
    $DEBUG \
    -DCMAKE_INSTALL_PREFIX=\"$PIDX_DIR/install\" \
    -DPIDX_BUILD_PROFILE=FALSE \
    -DPIDX_BUILD_PROCESSING=FALSE \
    -DPIDX_BUILD_TUTORIAL=FALSE \
  .."

run "make install"

echo ""
echo "Done Building PIDX Library."
echo "------------------------------------------------------------------"
echo ""

# Return 0 == success
exit 0
