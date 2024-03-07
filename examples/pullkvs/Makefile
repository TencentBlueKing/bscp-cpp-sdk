ifndef GRPC_PATH
$(error please define GRPC_PATH, eg: make GRPC_PATH=/path/to/your/grpc)
endif

BUILD_DIR = ./build
ABS_BUILD_DIR=$(abspath $(BUILD_DIR))
INTERNAL_PATH = ../../internal

BSCP_CPP_SDK_PATH = ../..

# includes
INCLUDEF  = -I./
INCLUDEF += -I${BUILD_DIR}/
INCLUDEF += -I${BSCP_CPP_SDK_PATH}/
INCLUDEF += -I${BSCP_CPP_SDK_PATH}/internal
INCLUDEF += -I${GRPC_PATH}/include

# compile
PROGRAMSET  = -g -O2 -Wno-deprecated-declarations
PROGRAMSET += -std=c++11

# library
# /usr/local/lib/libssl.a /usr/local/lib/libcrypto.a -lpthread -pthread
LIBRARYFILES := -L${BUILD_DIR}
LIBRARYFILES += -L/usr/local/lib -L/usr/lib64 -L/usr/local/lib64
LIBRARYFILES += -L${BSCP_CPP_SDK_PATH}
LIBRARYFILES += -L${GRPC_PATH}/lib -L${GRPC_PATH}/lib64
LIBRARYFILES +=  -lbscp_sdk
LIBRARYFILES += ${GRPC_PATH}/lib/libgrpc++_reflection.a ${GRPC_PATH}/lib/libgrpc++.a ${GRPC_PATH}/lib64/libprotobuf.a ${GRPC_PATH}/lib/libgrpc.a ${GRPC_PATH}/lib/libz.a ${GRPC_PATH}/lib/libcares.a ${GRPC_PATH}/lib/libaddress_sorting.a ${GRPC_PATH}/lib/libre2.a ${GRPC_PATH}/lib64/libabsl_raw_hash_set.a ${GRPC_PATH}/lib64/libabsl_hashtablez_sampler.a ${GRPC_PATH}/lib64/libabsl_hash.a ${GRPC_PATH}/lib64/libabsl_city.a ${GRPC_PATH}/lib64/libabsl_low_level_hash.a ${GRPC_PATH}/lib64/libabsl_statusor.a ${GRPC_PATH}/lib64/libabsl_bad_variant_access.a ${GRPC_PATH}/lib/libgpr.a ${GRPC_PATH}/lib/libupb.a -ldl -lm -lrt ${GRPC_PATH}/lib64/libabsl_status.a ${GRPC_PATH}/lib64/libabsl_random_distributions.a ${GRPC_PATH}/lib64/libabsl_random_seed_sequences.a ${GRPC_PATH}/lib64/libabsl_random_internal_pool_urbg.a ${GRPC_PATH}/lib64/libabsl_random_internal_randen.a ${GRPC_PATH}/lib64/libabsl_random_internal_randen_hwaes.a ${GRPC_PATH}/lib64/libabsl_random_internal_randen_hwaes_impl.a ${GRPC_PATH}/lib64/libabsl_random_internal_randen_slow.a ${GRPC_PATH}/lib64/libabsl_random_internal_platform.a ${GRPC_PATH}/lib64/libabsl_random_internal_seed_material.a ${GRPC_PATH}/lib64/libabsl_random_seed_gen_exception.a ${GRPC_PATH}/lib64/libabsl_cord.a ${GRPC_PATH}/lib64/libabsl_bad_optional_access.a ${GRPC_PATH}/lib64/libabsl_cordz_info.a ${GRPC_PATH}/lib64/libabsl_cord_internal.a ${GRPC_PATH}/lib64/libabsl_cordz_functions.a ${GRPC_PATH}/lib64/libabsl_exponential_biased.a ${GRPC_PATH}/lib64/libabsl_cordz_handle.a ${GRPC_PATH}/lib64/libabsl_str_format_internal.a ${GRPC_PATH}/lib64/libabsl_synchronization.a ${GRPC_PATH}/lib64/libabsl_stacktrace.a ${GRPC_PATH}/lib64/libabsl_symbolize.a ${GRPC_PATH}/lib64/libabsl_debugging_internal.a ${GRPC_PATH}/lib64/libabsl_demangle_internal.a ${GRPC_PATH}/lib64/libabsl_graphcycles_internal.a ${GRPC_PATH}/lib64/libabsl_malloc_internal.a ${GRPC_PATH}/lib64/libabsl_time.a ${GRPC_PATH}/lib64/libabsl_strings.a ${GRPC_PATH}/lib64/libabsl_throw_delegate.a ${GRPC_PATH}/lib64/libabsl_int128.a ${GRPC_PATH}/lib64/libabsl_strings_internal.a ${GRPC_PATH}/lib64/libabsl_base.a -lpthread ${GRPC_PATH}/lib64/libabsl_spinlock_wait.a -lrt ${GRPC_PATH}/lib64/libabsl_raw_logging_internal.a ${GRPC_PATH}/lib64/libabsl_log_severity.a ${GRPC_PATH}/lib64/libabsl_civil_time.a ${GRPC_PATH}/lib64/libabsl_time_zone.a ${GRPC_PATH}/lib/libssl.a ${GRPC_PATH}/lib/libcrypto.a -lpthread -pthread

# command
CXX = g++

TARGET := utest

SRCS := pullkvs.cpp

all: $(TARGET)

# Generate target executable
$(TARGET): $(OBJS)
	$(CXX) $(SRCS) $(INCLUDEF) $(PROGRAMSET) -o $@ $(OBJS) $(LIBRARYFILES)

clean:
	@rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all checkdirs clean
default: all
