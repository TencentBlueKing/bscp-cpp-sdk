TARGET := libbscp_sdk.a

.PHONY: all pre clean

default: all

BSCP_CPP_SDK_PATH = $(CURDIR)
BUILD_DIR = $(BSCP_CPP_SDK_PATH)/build
INCLUDE_BUILD_DIR = $(BUILD_DIR)/include
LIB_BUILD_DIR = $(BUILD_DIR)/lib

# includes
INCLUDEF  = -I$(BSCP_CPP_SDK_PATH)/
INCLUDEF += -I$(BSCP_CPP_SDK_PATH)/internal
INCLUDEF += -I$(GRPC_PATH)/include

# compile
PROGRAMSET  = -g -O2 -Wno-deprecated-declarations
PROGRAMSET += -std=c++11

# command
CXX = g++
AR = ar
RM = rm
CP = cp
MV = mv
ECHO = echo
MKDIR = mkdir
FIND = find

all: pre $(TARGET)
	@$(FIND) . -type d -name "$(BSCP_CPP_SDK_PATH)/examples/*" -prune -o -type d -name "$(BSCP_CPP_SDK_PATH)/test/*" -prune -o -type f -name "*.h*" | xargs -I {} rsync -aR {} ${INCLUDE_BUILD_DIR}
	@$(MV) $(TARGET) $(LIB_BUILD_DIR)/
	@$(ECHO) -e "\033[32m\nBuilt $(TARGET) Successfully\n\033[0m"

pre:
	@$(ECHO) -e "\033[32m\nBuilding $(TARGET) ...\033[0m"
	@$(MKDIR) -p $(BUILD_DIR)
	@$(MKDIR) -p $(INCLUDE_BUILD_DIR)
	@$(MKDIR) -p $(LIB_BUILD_DIR)

clean:
	@$(RM) -rf $(BUILD_DIR) $(TARGET)

install:
	@$(MKDIR) -p /usr/local/include/bscp-cpp
	@$(CP) -rf $(INCLUDE_BUILD_DIR)/* /usr/local/include/bscp-cpp
	@$(CP) -rf $(LIB_BUILD_DIR)/* /usr/local/lib


SRCS = $(shell find $(BSCP_CPP_SDK_PATH) -maxdepth 1 -name "*.cpp")
SRCS += $(shell find $(BSCP_CPP_SDK_PATH)/internal -name "*.cpp")
SRCS += $(shell find $(BSCP_CPP_SDK_PATH)/third-party -name "*.cpp")
SRCS += $(shell find $(BSCP_CPP_SDK_PATH)/internal -name "*.cc")

# Combine all objects
OBJS := $(SRCS:$(BSCP_CPP_SDK_PATH)/%.cc=$(BUILD_DIR)/%.o)
OBJS := $(OBJS:$(BSCP_CPP_SDK_PATH)/%.cpp=$(BUILD_DIR)/%.o)

# Compile protobuf generated .cc to object files
$(BUILD_DIR)/%.o: $(BSCP_CPP_SDK_PATH)/%.cc
	@$(MKDIR) -p $(dir $@)
	$(CXX) $(INCLUDEF) $(PROGRAMSET) -MMD -c $< -o $@

# Compile C++ source files to object files
$(BUILD_DIR)/%.o: $(BSCP_CPP_SDK_PATH)/%.cpp
	@$(MKDIR) -p $(dir $@)
	$(CXX) $(INCLUDEF) $(PROGRAMSET) -MMD -c $< -o $@

# Generate target executable
$(TARGET): $(OBJS)
	@$(ECHO) -e "\033[32m\nLinking $(TARGET) ...\033[0m"
	$(AR) -r $@ $(OBJS)
