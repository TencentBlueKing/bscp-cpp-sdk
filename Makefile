BUILD_DIR = ./build
INTERNAL_PATH = ./internal

BSCP_CPP_SDK_PATH = .

# includes
INCLUDEF  = -I./
INCLUDEF += -I${BUILD_DIR}/
INCLUDEF += -I${BSCP_CPP_SDK_PATH}/
INCLUDEF += -I${BSCP_CPP_SDK_PATH}/internal
INCLUDEF += -I${BSCP_CPP_SDK_PATH}/third-party
INCLUDEF += -I${GRPC_PATH}/include

# compile
PROGRAMSET  = -g -O2 -Wno-deprecated-declarations
PROGRAMSET += -std=c++11

# command
CXX = g++
AR = ar

TARGET := libbscp_sdk.a

SRCS := $(shell find ${BSCP_CPP_SDK_PATH} -name "client.cpp")
SRCS += $(shell find ${BSCP_CPP_SDK_PATH}/internal -name "*.cpp")
SRCS += $(shell find ${BSCP_CPP_SDK_PATH}/third-party -name "*.cpp")
SRCS += $(shell find ${BSCP_CPP_SDK_PATH}/internal -name "*.cc")

all: checkdirs $(TARGET)

checkdirs:
	@mkdir -p $(BUILD_DIR)

# Combine all objects
OBJS := $(SRCS:$(BSCP_CPP_SDK_PATH)/%.cc=$(BUILD_DIR)/%.o)
OBJS := $(OBJS:$(BSCP_CPP_SDK_PATH)/%.cpp=$(BUILD_DIR)/%.o)

# Compile protobuf generated .cc to object files
$(BUILD_DIR)/%.o: $(BSCP_CPP_SDK_PATH)/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(INCLUDEF) $(PROGRAMSET) -MMD -c $< -o $@

# Compile C++ source files to object files
$(BUILD_DIR)/%.o: $(BSCP_CPP_SDK_PATH)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(INCLUDEF) $(PROGRAMSET) -MMD -c $< -o $@

# Generate target executable
$(TARGET): $(OBJS)
	$(AR) -r $@ $(OBJS)

clean:
	@rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all checkdirs clean
default: all
