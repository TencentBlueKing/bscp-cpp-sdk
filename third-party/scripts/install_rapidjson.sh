#!/usr/bin/env bash
set -eo pipefail
source $(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)/base.sh

# install rapidjson
# version master
# source https://github.com/Tencent/rapidjson/archive/refs/heads/master.zip
name="rapidjson"
version="master"

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
# we use master branch of rapidjson, just install every time
progress "checking $name"
progress "installing $name"

# download source
progress "downloading"
wget -N https://github.com/Tencent/rapidjson/archive/refs/heads/master.zip
test -f rapidjson-master || rm -rf rapidjson-master
unzip master.zip
cd rapidjson-master

# compile & install
progress "compiling & installing"
mkdir -p build
cd build
cmake ..
make
make install

progress "install $name $version successfully"
exit 0
