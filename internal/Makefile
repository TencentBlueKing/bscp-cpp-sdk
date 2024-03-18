.PHONY: all clean

default: all

ifndef GRPC_PATH
GRPC_PATH = /usr/local/grpc-1.45.0
endif

PROTOC = $(GRPC_PATH)/bin/protoc
GRPC_CPP_PLUGIN = $(GRPC_PATH)/bin/grpc_cpp_plugin

INTERNAL_PATH = $(CURDIR)

BUILD_DIR_PROTO_FILES += $(shell find $(INTERNAL_PATH) -name "*.proto")
PROTO_FILES := $(BUILD_DIR_PROTO_FILES:$(INTERNAL_PATH)/%.proto=%.proto)
GRPC_PROTO_FILES := pkg/protocol/feed-server/feed_server.proto
PB_PROTO_FILES := $(filter-out $(GRPC_PROTO_FILES), $(PROTO_FILES))

GRPC_GEN_FILES := \
    $(GRPC_PROTO_FILES:%.proto=%.grpc.pb.cc) \
    $(GRPC_PROTO_FILES:%.proto=%.grpc.pb.h)

PB_GEN_FILES := \
    $(PB_PROTO_FILES:%.proto=%.pb.cc) \
    $(PB_PROTO_FILES:%.proto=%.pb.h)

all: $(PB_GEN_FILES) $(GRPC_GEN_FILES)

clean: 
	@find . -name "*.pb.cc" -o -name "*.pb.h" | xargs rm -r

%.grpc.pb.cc %.grpc.pb.h: %.proto
	$(PROTOC) --proto_path=. --cpp_out=. --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN) $<

%.pb.cc %.pb.h: %.proto
	$(PROTOC) --proto_path=. --cpp_out=. $<


