## BSCP-CPP-SDK

[![license](https://img.shields.io/badge/license-MIT-brightgreen.svg?style=flat)](https://github.com/TencentBlueKing/bscp-cpp-sdk/blob/master/LICENSE.txt)

[EnglishDocs](./README_EN.md)

## Overview

bscp-cpp-sdk 是蓝鲸 BSCP 项目的 C++ SDK，它能帮助你轻松访问项目保存在 BSCP 上的配置内容。

## Features

- kv 配置拉取
- kv 配置 watch

## 快速上手

### 依赖安装

`bscp-cpp-sdk`基于`cpp11`版本实现，其以`gRPC`做为底层的通信协议，`gRPC`最新的支持`cpp11`的版本为`v1.46.x`,之后更新的版本需要`cpp17`以上的编译器。

```shell
sh third-party/install.sh
```

### 编译部署

- **make**: `bscp-cpp-sdk`编译
- **make install**: `bscp-cpp-sdk`安装
- **make examples**: examples编译
- **make utest**: 单元测试编译

## Roadmap

* [版本日志](CHANGELOG.md)

## Support

- [白皮书](https://bk.tencent.com/docs)
- [社区论坛](https://bk.tencent.com/s-mart/community)
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
[腾讯开源激励计划](https://opensource.tencent.com/contribution)鼓励开发者的参与和贡献，期待你的加入。

## License

项目基于 MIT 协议，详细请参考 [LICENSE](./LICENSE.txt)。

我们承诺未来不会更改适用于交付给任何人的当前项目版本的开源许可证（MIT 协议）。
