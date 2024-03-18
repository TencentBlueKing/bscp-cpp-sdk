#!/usr/bin/env bash
set -eo pipefail

SCRIPTS_HOME="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)/scripts"
WORKSPACE="/tmp/bscp-cpp-sdk-thirdparty"

source $SCRIPTS_HOME/base.sh

# initialize sub installer workspace and the output file
cd $SCRIPTS_HOME
mkdir -p $WORKSPACE
if [[ -f "$WORKSPACE/message.out" ]]; then
    echo "" >$WORKSPACE/message.out
fi

# initialize the fd for printing progress
exec 3<&1
fd="3"

header_width=20

# intialize the main printer
progress() {
    echo -e "$COLOR_SUCC $@$COLOR_OFF"
}
fail() {
    echo -e "$COLOR_FAIL $@$COLOR_OFF, please check $WORKSPACE/message.out for detail logs"
    return 1
}

# handle some tricky actions for compating with old version
# creat an empty header for gse-proc so it can be compiled on x84-linux
touch /usr/local/include/stropts.h

# install the third-party dependences
progress "start to install bscp-cpp-sdk thirdparty dependences"
sh install_rapidjson.sh $WORKSPACE/rapidjson $fd $header_width &>>$WORKSPACE/message.out || fail "install rapidjson failed"
sh install_grpc.sh $WORKSPACE/grpc $fd $header_width &>>$WORKSPACE/message.out || fail "install rapidjson failed"
progress "success to install all bscp-cpp-sdk thirdparty dependences"

exec 3>&- # close fd.
