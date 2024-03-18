#!/usr/bin/env bash
set -eo pipefail
source $(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)/base.sh

# install grpc
# version 1.45.0
# source https://github.com/grpc/grpc/archive/refs/tags/v1.45.0.tar.gz
name="grpc"
version="1.45.0"

# handle the args from caller
dir="$1"
if [[ -z "$dir" ]]; then
    dir="/tmp/bscp-cpp-sdk-thirdparty/$name"
fi
fd="$2"
if [[ -z "$fd" ]]; then
    fd="1"
fi
head_width="$3"
if [[ -z "$head_width" ]]; then
    head_width=1
fi
progress() {
    printf "$COLOR_SUCC %-${head_width}s $COLOR_OFF$@\n" "[$name]" >&$fd
}
fail() {
    printf "$COLOR_FAIL %-${head_width}s $COLOR_OFF$@\n" "[$name]" >&$fd
}

# ensure dir
mkdir -p $dir
cd $dir

# get version
progress "checking $name"
need_install=1
if [[ -d "/usr/local/grpc-1.45.0" ]]; then
    need_install=0
fi

if [[ "$need_install" == "1" ]]; then
    progress "installing $name"

    # download source
    progress "downloading"
    git clone --recurse-submodules -b v1.45.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc

    # compile & install
    progress "compiling & installing"

    cd grpc
    mkdir -p cmake/build

    pushd cmake/build

    cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=/usr/local/grpc-1.45.0 ../..

    make -j 4
    mkdir -p /usr/local/grpc-1.45.0
    mkdir -p /usr/local/grpc-1.45.0/lib
    mkdir -p /usr/local/grpc-1.45.0/lib64
    make install

    popd

    progress "install $name $version successfully"
    exit 0
fi

if [[ "$need_install" == "0" ]]; then
    progress "$name $current_version found, skip installing"
    exit 0
fi

fail "$name $current_version is not equal to dependent $version, please remove the old one and reinstall"
exit 1
