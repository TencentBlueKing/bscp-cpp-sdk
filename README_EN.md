## BSCP-CPP-SDK

[![license](https://img.shields.io/badge/license-MIT-brightgreen.svg?style=flat)](https://github.com/TencentBlueKing/bscp-cpp-sdk/blob/master/LICENSE.txt)

[中文文档](./README.md)

## Overview

bscp-cpp-sdk is the C++ SDK of the Blue Whale BSCP project. It can help you easily access the configuration content of the project saved on BSCP.

## Features

- kv configuration pull
- kv configuration watch

## Quick Start

### Dependency installation

`bscp-cpp` is implemented based on the `cpp11` version, which uses `gRPC` as the underlying communication protocol. The latest version of `gRPC` that supports `cpp11` is `v1.46.x`, and later updated versions require` Compilers above cpp17`.

```shell
sh third-party/install.sh
```

### Compilation and deployment

- **make**: `bscp-cpp-sdk` compilation
- **make install**: `bscp-cpp-sdk` installation
- **make examples**: examples compilation
- **make utest**: unit test compilation

## Roadmap

* [Changelog(In Chinese)](CHANGELOG.md)

## Support

- [White Paper(In Chinese)](https://bk.tencent.com/docs)
- [BlueKing Forum](https://bk.tencent.com/s-mart/community)
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
[Tencent OpenSource Plan](https://opensource.tencent.com/contribution) Developers are encouraged to participate and contribute, and we look forward to your participation.

## License

bscp-cpp-sdk is based on the MIT protocol. Please refer to [LICENSE](./LICENSE.txt) for details.