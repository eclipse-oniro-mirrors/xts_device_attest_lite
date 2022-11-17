# Device Attest Lite 轻量级设备证明

#### 介绍
Open Harmony设备证明开发分支
提供设备的合法性验证功能，通过端云结合的方式校验设备是否通过OpenHarmony兼容性认证（OHCA认证）

#### 软件架构
软件架构说明

代码目录结构：

    device_attest_lite
    |    build（编译配置）
    |    |   devattestconfig.gni（编译目录等公共配置）
    |    framework（SA启动框架）
    |    |    mini
    |    |    |    src
    |    |    small
    |    |    |    include
    |    |    |    src
    |    |    |    |    client
    |    |    |    |    service
    |    |    BUILD.gn
    |    interfaces（对外接口）
    |    |   include
    |    |   |   ***devattest_interface.h
    |    |   |   ***devattest_msg_def.h
    |    services（服务主体和业务逻辑代码）
    |    |   core（业务逻辑代码，暂时放在该目录）
    |    |   |   adapter
    |    |   |   attest
    |    |   |   dfx
    |    |   |   include
    |    |   |   network
    |    |   |   security
    |    |   |   utils
    |    |   |   BUILD.gn
    |    |   |   ***attest_entry.c
    |    |   |   ***attest_entry.h
    |    test（测试用例）
    |    |    data（测试用例数据）
    |    |    startup（L1测试启动模块）
    |    BUILD.gn（组件编译脚本）

#### 安装教程

1.  xxxx
2.  xxxx
3.  xxxx

#### L0使用说明
1. 拷贝项目代码
+  把device_attest_lite目录放到
```
//test/xts/
```
2.  添加组件到xts子系统
+ 修改//build/lite/components/xts.json
添加代码：
```
    {
      "component": "device_attest_lite",
      "description": "",
      "optional": "true",
      "dirs": [
        "test/xts/device_attest_lite"
      ],
      "targets": [
        "//test/xts/device_attest_lite:device_atTest_lite"
      ],
      "rom": "",
      "ram": "",
      "output": [],
      "adapted_kernel": [
        "liteos_m",
        "liteos_a",
        "linux"
      ],
      "features": [],
      "deps": {}
    }
```

3.  编译组件  
+ 修改//vendor/hisilicon/hispark_taurus/config.json
在"subsystem": "xts"下的"components"中添加
'''
{ "component": "device_attest_lite", "features":["build_xts = true"] }
'''
打开thirdparty_mbedtls
```c
"enable_ohos_startup_init_lite_use_thirdparty_mbedtls = true"
```

#### L1使用说明
1. 拷贝项目代码
+  把device_attest_lite目录放到
```
//test/xts/
```

2.  添加组件到xts子系统
+ 修改//build/lite/components/xts.json
添加代码：
```
    {
      "component": "device_attest_lite",
      "description": "",
      "optional": "true",
      "dirs": [
        "test/xts/device_attest_lite"
      ],
      "targets": [
        "//test/xts/device_attest_lite:device_atTest_lite"
      ],
      "rom": "",
      "ram": "",
      "output": [],
      "adapted_kernel": [
        "liteos_m",
        "liteos_a",
        "linux"
      ],
      "features": [],
      "deps": {}
    }
```


3.  编译组件  
+ 修改//vendor/hisilicon/hispark_taurus/config.json
+ 或者//vendor/hisilicon/hispark_taurus_linux/config.json  

在"subsystem": "xts"下的"components"中添加
```
{ "component": "device_attest_lite", "features":[ "build_xts = true" ] }
```


4.  启动SA服务  

* 4.1 liteos-a核  

修改vendor/hisilicon/hispark_taurus/init_configs目录下的  
init_liteos_a_3516dv300.cfg 和 init_liteos_a_3516dv300_mksh.cfg  
+ "jobs" -> "name" : "init" -> "cmds"下增加  
```
"start devattest_service"
```
+ "services"下增加
```
        {
            "name" : "devattest_service",
            "path" : ["/bin/devattest_service"],
            "uid" : 0,
            "gid" : 0,
            "once" : 1,
            "importance" : 0,
            "caps" : []
        }
```

+ "jobs" -> "name" : "pre-init" -> "cmds"下增加  
```
                "mkdir /storage/data/attest",
                "chmod 0755 /storage/data/attest",
```

* 4.2  linux核  
修改vendor/hisilicon/hispark_taurus_linux/init_configs目录下的  
init_linux_3516dv300_openharmony_debug.cfg 和 init_linux_3516dv300_openharmony_release.cfg  
+ 重复4.1的操作


5.  增加SA权限
修改base/security/permission_lite/services/ipc_auth/include/policy_preset.h
+  添加代码
```
FeaturePolicy devAttestFeature[] = {
    {
        "attest_feature",
        {
            {
                .type = RANGE,
                .uidMin = 0,
                .uidMax = __INT_MAX__,
            },
        },
    },
};
```
+  static PolicySetting g_presetPolicies[]下添加元素
```
    {"attest_service", devAttestFeature, 1}
```
PS:在添加元素后，记得在前面加逗号


6. 开启安全套件
* 6.1 liteos-a核
+ third_party/mbedtls/port/config/config_liteos_a.h 开启宏
```
#define MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED
```

* 6.2 linux核
+ //third_party/mbedtls/include/mbedtls/config.h 开启宏
```
#define MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED
```
+ 修改//device/soc/hisilicon/hi3516dv300/sdk_linux/drv/mpp/cfg.mak
```
export CONFIG_CIPHER=n
```

7. 预置token
+ 写入token

修改文件 test/xts/device_attest_lite/test/data/token

+ 开启token文件拷贝

修改文件 test/xts/device_attest_lite/services/core/BUILD.gn  
shared_library("devattest_core")里面添加
```
    deps += [
      ":token",
    ]
```

#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request


#### 特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
