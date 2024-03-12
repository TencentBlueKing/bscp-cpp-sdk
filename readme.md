## BSCP-CPP-SDK

[![license](https://img.shields.io/badge/license-MIT-brightgreen.svg?style=flat)]()

[EnglishDocs](./readme_en.md)

## Overview

bscp-cpp-sdk 是蓝鲸 BSCP 项目的 C++ SDK，它能帮助你轻松访问项目保存在 BSCP 上的配置内容。

## Feature

- kv 配置拉取
- kv 配置 watch

## 快速上手

### 部署编译

`bscp-cpp`基于`cpp11`版本实现，其以`gRPC`做为底层的通信协议，`gRPC`最新的支持`cpp11`的版本为`v1.46.x`,之后更新的版本需要`cpp17`以上的编译器。

#### 下载并安装`cpp11`版本`gRPC`

```shell
git clone --recurse-submodules -b v1.45.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc

cmake编译gRPC，进入到下载的grpc路径
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
将`home/path/to/grpc/`替换成你的安装路径，建议`/usr/local/grpc版本/`，如`/usr/local/grpc-1.45/`。

### 第三方依赖库安装

进入到`third-party`目录中，运行`sh ./install.sh`以安装相应的依赖库。

### `bscp-cpp`编译

#### examples的编译

* 进入到`internal`路径中，运行`make GRPC_PATH=/path/to/your/grpc`编译proto文件
* 进入到项目根目录中，运行`make GRPC_PATH=/path/to/your/grpc`编译`bscp-cpp-sdk`库文件libbscp_sdk.a
* 进入到具体的`examples`路径中，运行`make GRPC_PATH=/path/to/your/grpc`编译生成相应的二进制文件`utest`

#### 单元测试编译

* 进入到`internal`路径中，运行`make GRPC_PATH=/path/to/your/grpc`编译proto文件
* 进入到项目根目录中，运行`make GRPC_PATH=/path/to/your/grpc`编译`bscp-cpp-sdk`库文件libbscp_sdk.a
* 进入到具体的`test`路径中，运行`make GRPC_PATH=/path/to/your/grpc`编译生成相应的二进制文件`utest`

#### 编译产物清理

* 先进入到`internal`路径中，运行`make clean GRPC_PATH=/path/to/your/grpc`清理相应的文件
* 进入到项目根目录中，运行`make clean GRPC_PATH=/path/to/your/grpc`清理相应的文件
* 进入到具体的`examples`路径中，运行`make clean GRPC_PATH=/path/to/your/grpc`清理相应的文件
* 进入到具体的`test`路径中，运行`make clean GRPC_PATH=/path/to/your/grpc`清理相应的文件

## Support

- [蓝鲸论坛](https://bk.tencent.com/s-mart/community)
- [蓝鲸 DevOps 在线视频教程](https://bk.tencent.com/s-mart/video/)
- 联系我们，技术交流QQ群：

<img src="https://github.com/Tencent/bk-PaaS/raw/master/docs/resource/img/bk_qq_group.png" width="250" hegiht="250" align=center />

## BlueKing Community

- [BK-CI](https://github.com/Tencent/bk-ci)：蓝鲸持续集成平台是一个开源的持续集成和持续交付系统，可以轻松将你的研发流程呈现到你面前。
- [BK-BCS](https://github.com/Tencent/bk-bcs)：蓝鲸容器管理平台是以容器技术为基础，为微服务业务提供编排管理的基础服务平台。
- [BK-PaaS](https://github.com/Tencent/bk-PaaS)：蓝鲸PaaS平台是一个开放式的开发平台，让开发者可以方便快捷地创建、开发、部署和管理SaaS应用。
- [BK-SOPS](https://github.com/Tencent/bk-sops)：标准运维（SOPS）是通过可视化的图形界面进行任务流程编排和执行的系统，是蓝鲸体系中一款轻量级的调度编排类SaaS产品。
- [BK-CMDB](https://github.com/Tencent/bk-cmdb)：蓝鲸配置平台是一个面向资产及应用的企业级配置管理平台。

## Contributing

如果你有好的意见或建议，欢迎给我们提 Issues 或 Pull Requests，为蓝鲸开源社区贡献力量。

## License

`bscp-cpp-sdk`是基于MIT协议， 详细请参考[LICENSE](./LICENSE.txt)。
