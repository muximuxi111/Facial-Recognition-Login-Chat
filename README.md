# 人脸识别登录 + TCP 多人聊天室

基于 **Qt 5** 的桌面应用，包含两大功能模块：

- **人脸识别登录** —— OpenCV 3.4 采集摄像头画面，Haar 级联检测人脸，LBPH 算法在线训练识别，识别通过后放行登录。
- **多人聊天室** —— 基于 QTcpSocket 的 TCP 通信客户端，支持多用户实时消息收发。

配套数据库采用 SQLite（`QSQLITE`），用于存储账号密码与人脸标签。

> 详细的设计思路、核心代码解析与接口说明见 [`docs/项目说明报告.docx`](docs/项目说明报告.docx)。

---

## 一、功能概览

| 模块 | 说明 |
| --- | --- |
| 注册 / 登录 | 账号密码注册与登录，数据落库 SQLite |
| 密码登录 | 传统账号密码校验方式 |
| 人脸识别登录 | 摄像头采集 → 人脸检测 → LBPH 识别 → 登录放行 |
| 人脸录入 | 采集 50 帧人脸样本训练生成识别模型 |
| 多人聊天室 | TCP 长连接，多客户端接入，实时收发消息 |

---

## 二、运行环境

| 项目 | 版本 / 说明 |
| --- | --- |
| 操作系统 | Windows 10 / 11 |
| Qt | 5.14.2（MinGW 32bit 套件） |
| 编译器 | MinGW 7.3.0 32-bit |
| OpenCV | 3.4（**必须为 MinGW 32bit 编译版本**） |
| 数据库 | SQLite（Qt 内置 `QSQLITE` 驱动） |

> ⚠️ 关键：OpenCV 必须与 Qt 的 MinGW 32bit 编译器 **ABI 一致**。直接用官方 MSVC 版 OpenCV 会在链接阶段报错。

---

## 三、依赖准备

### 1. 安装 Qt 5.14.2

通过 Qt 官方在线安装器勾选 **MinGW 7.3.0 32-bit** 组件。

### 2. 编译 OpenCV 3.4（MinGW 32bit）

```bash
# 在 OpenCV 源码目录下
mkdir build && cd build

cmake -G "MinGW Makefiles" ^
      -DCMAKE_BUILD_TYPE=Release ^
      -DCMAKE_INSTALL_PREFIX=D:/opencv/opencv3.4-qt-intall/install ^
      -DWITH_QT=ON ^
      -DBUILD_EXAMPLES=OFF ^
      -DBUILD_opencv_world=OFF ^
      ..

mingw32-make -j8
mingw32-make install
```

编译完成后，`install/` 目录下应有 `include/` 与 `x86/mingw/lib/` 两级结构。

### 3. 配置 OpenCV 路径

`Facialrecognition.pro` 默认按 `D:/opencv/opencv3.4-qt-intall/install` 查找 OpenCV。**如果你的路径不同，不需要修改 `.pro` 文件**，在构建时用变量覆盖即可：

```bash
qmake "OPENCV_ROOT=D:/opencv/你的安装路径/install"
```

或在 Qt Creator 中：`Projects → Build Steps → qmake → Additional arguments` 填入上面的参数。

---

## 四、构建与运行

### 方式一：Qt Creator

1. 用 Qt Creator 打开 `Facialrecognition/Facialrecognition.pro`
2. 选择 **Desktop Qt 5.14.2 MinGW 32-bit** 套件
3. 若 OpenCV 路径非默认，按上文配置 `OPENCV_ROOT`
4. 点击构建并运行

### 方式二：命令行

```bash
cd Facialrecognition
mkdir build && cd build
qmake "OPENCV_ROOT=D:/opencv/opencv3.4-qt-intall/install" ../Facialrecognition.pro
mingw32-make -j8
```

> ✅ 本仓库的 `.pro` 配置已在 **Qt 5.14.2 MinGW 7.3.0 32-bit + OpenCV 3.4** 环境下实测通过：
> qmake 与 mingw32-make 均退出码 0，成功链接生成 `Facialrecognition.exe`（约 2.9 MB）。
> 链接的 OpenCV 模块为 `core`、`imgproc`、`imgcodecs`、`videoio`、`objdetect`、`face` 共 6 个，
> 已在 `.pro` 中按实际使用精确声明，未使用通配符拉入无关库。

---

## 五、使用说明

### 人脸识别登录流程

1. **首次使用需先录入人脸**：进入注册 / 人脸录入界面，保持面部正对摄像头
2. 程序采集 **50 帧** 人脸图像，统一缩放至 **100×100** 灰度图，并做直方图均衡化
3. 训练生成识别模型 `myface.xml`
4. 登录时实时采集画面比对，**LBPH 距离阈值设为 80**，小于阈值判定为同一人

### 聊天室

程序内置 TCP 客户端，默认连接目标：

```
127.0.0.1:8888
```

> 📌 本工程仅包含**客户端**实现，聊天室服务端不在本仓库内。需要自行准备服务端监听 `8888` 端口，或修改 `client.cpp` 中的目标地址与端口。

---

## 六、目录结构

```
.
├── Facialrecognition/              # Qt 工程源码
│   ├── Facialrecognition.pro       # 工程文件（依赖声明）
│   ├── main.cpp                    # 程序入口
│   ├── login.h / .cpp / .ui        # 登录主界面
│   ├── password_login.h / .cpp / .ui   # 密码登录
│   ├── sign_up.h / .cpp            # 注册与人脸录入
│   ├── widget.h / .cpp / .ui       # 主功能界面
│   ├── client.h / .cpp / .ui       # TCP 聊天客户端
│   ├── database.h / .cpp           # SQLite 数据库操作
│   └── image/                      # 界面素材与图标
│       └── image.qrc               # Qt 资源文件
├── docs/
│   └── 项目说明报告.docx            # 项目说明文档
└── README.md
```

---

## 七、常见问题

**Q：编译报 `undefined reference to cv::xxx`？**

OpenCV 版本与编译器 ABI 不匹配。请确认使用的是 **MinGW 32bit 自编译版**，而非 MSVC 版。

**Q：链接报 `cannot find -lopencv_core345`？**

找不到库文件。确认 `OPENCV_ROOT/x86/mingw/lib/` 下存在 `libopencv_*.dll.a` 文件。
若你的 OpenCV 版本号不是 `345`（即 3.4.5），需修改 `.pro` 中 `OPENCV_MODULES` 循环里的版本后缀。

**Q：报「未找到 OpenCV 目录」？**

`.pro` 中已内置路径检查。用 `qmake "OPENCV_ROOT=你的路径/install"` 指定正确位置即可。

**Q：人脸识别一直识别失败？**

- 光照过暗或过曝会导致直方图均衡化效果变差
- 人脸未正对摄像头、遮挡过多会影响 Haar 检测
- 阈值为 80，若误识率高可适当调低 `setThreshold()` 的值

**Q：数据库文件在哪？**

首次运行后会在可执行文件同级目录生成 SQLite 数据库文件。该文件属于本地运行时数据，已被 `.gitignore` 排除，不会提交到仓库。

---

## 八、说明

- 仓库已排除构建产物（`build-*/`、`moc_*`、`ui_*` 等）、Qt Creator 用户配置（`*.pro.user`，内含本机绝对路径）以及运行时生成的数据库与模型文件。
- 人脸识别模型 `myface.xml` 由程序运行时生成，不随仓库分发；克隆后请先完成一次人脸录入。
