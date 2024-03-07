## BSCP-CPP-SDK

[![license](https://img.shields.io/badge/license-MIT-brightgreen.svg?style=flat)]()

[中文文档](./readme.md)

## Overview

bscp-cpp-sdk is the C++ SDK of the Blue Whale BSCP project. It can help you easily access the configuration content of the project saved on BSCP.

## Features

- kv configuration pull
- kv configuration watch

## Quick Start

### Deployment and compile

`bscp-cpp` is implemented based on the `cpp11` version, which uses `gRPC` as the underlying communication protocol. The latest version of `gRPC` that supports `cpp11` is `v1.46.x`, and later updated versions require` Compilers above cpp17`.

#### Download and install `cpp11` version `gRPC`

```shell
git clone --recurse-submodules -b v1.45.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc

cmake compiles gRPC and enters the downloaded grpc path
cd grpc
mkdir -p cmake/build

pushd cmake/build

cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=home/path/to/grpc/ ../..
make -j 4

mkdir -p home/path/to/grpc/
mkdir -p home/path/to/grpc/lib
mkdir -p home/path/to/grpc/lib64
make install

popd
```
Replace `home/path/to/grpc/` with your installation path, it is recommended `/usr/local/grpc version/`, such as `/usr/local/grpc-1.45/`.

### Third-party dependency library installation

Enter the `third-party/scripts` directory and run `sh ./install_rapidjson.sh` to install the corresponding dependent libraries.

### Compile with `bscp-cpp`

#### Compilation of examples

* Enter the `internal` path and run `make GRPC_PATH=/path/to/your/grpc` to compile the proto file
* Enter the project root directory and run `make GRPC_PATH=/path/to/your/grpc` to compile the `bscp-cpp-sdk` library file libbscp_sdk.a
* Enter the specific `examples` path and run `make GRPC_PATH=/path/to/your/grpc` to compile and generate the corresponding binary file `utest`

#### Unit test compilation

* Enter the `internal` path and run `make GRPC_PATH=/path/to/your/grpc` to compile the proto file
* Enter the project root directory and run `make GRPC_PATH=/path/to/your/grpc` to compile the `bscp-cpp-sdk` library file libbscp_sdk.a
* Enter the specific `test` path and run `make GRPC_PATH=/path/to/your/grpc` to compile and generate the corresponding binary file `utest`

#### Compile product cleanup

* First enter the `internal` path and run `make clean GRPC_PATH=/path/to/your/grpc` to clean up the corresponding files
* Enter the project root directory and run `make clean GRPC_PATH=/path/to/your/grpc` to clean up the corresponding files
* Enter the specific `examples` path and run `make clean GRPC_PATH=/path/to/your/grpc` to clean up the corresponding files
* Enter the specific `test` path and run `make clean GRPC_PATH=/path/to/your/grpc` to clean up the corresponding files

## Support

- [bk forum](https://bk.tencent.com/s-mart/community)
- [bk DevOps online video tutorial(In Chinese)](https://cloud.tencent.com/developer/edu/major-100008)
- Contact us, technical exchange QQ group:

<img src="https://github.com/Tencent/bk-PaaS/raw/master/docs/resource/img/bk_qq_group.png" width="250" hegiht="250" align=center />

## BlueKing Community

- [BK-CI](https://github.com/Tencent/bk-ci)：a continuous integration and continuous delivery system that can easily present your R & D process to you.
- [BK-BCS](https://github.com/Tencent/bk-bcs)：a basic container service platform which provides orchestration and management for micro-service business.
- [BK-BCS-SaaS](https://github.com/Tencent/bk-bcs-saas)：a SaaS provides users with highly scalable, flexible and easy-to-use container products and services.
- [BK-PaaS](https://github.com/Tencent/bk-PaaS)：an development platform that allows developers to create, develop, deploy and manage SaaS applications easily and quickly.
- [BK-SOPS](https://github.com/Tencent/bk-sops)：an lightweight scheduling SaaS  for task flow scheduling and execution through a visual graphical interface.
- [BK-CMDB](https://github.com/Tencent/bk-cmdb)：an enterprise-level configuration management platform for assets and applications.

## Contributing

If you have good ideas or suggestions, please let us know by Issues or Pull Requests and contribute to the Blue Whale Open Source Community.

## License

bscp-cpp-sdk is based on the MIT protocol. Please refer to [LICENSE](./LICENSE.txt) for details.