#!/usr/bin/env bash
set -eo pipefail
source $(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)/base.sh

# install library_name
# version library_version
# source https://library_source_code_path
name="library_name"
version="library_version"

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
if [[ -f "/usr/local/include/library_name.h" ]]; then
    echo "
#include <iostream>
#include <library_name.h>
int main()
{
    std::cout << LIBRARY_VERSION;
}" >test_version.cpp
    g++ -I/usr/local/include test_version.cpp
    current_version=$(./a.out)
fi

if [[ -z "$current_version" ]]; then
    progress "installing $name"

    # download source
    progress "downloading"
    # wget -N library_download_path
    # tar zxvf package.tgz
    # cd package

    # compile & install
    progress "compiling & installing"
    # mkdir -p build
    # cd build
    # cmake ..
    # make -j4
    # make install

    progress "install $name $version successfully"
    exit 0
fi

if [[ "$current_version" == "$version" ]]; then
    progress "$name $current_version found, skip installing"
    exit 0
fi

fail "$name $current_version is not equal to dependent $version, please remove the old one and reinstall"
exit 1
