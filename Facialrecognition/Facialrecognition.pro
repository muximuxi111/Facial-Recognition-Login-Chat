QT       += core gui
QT += network
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    database.cpp \
    login.cpp \
    main.cpp \
    password_login.cpp \
    sign_up.cpp \
    widget.cpp

HEADERS += \
    client.h \
    database.h \
    login.h \
    password_login.h \
    sign_up.h \
    widget.h

FORMS += \
    client.ui \
    login.ui \
    password_login.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# ============================================================
# OpenCV 3.4 配置（MinGW 32bit 编译）
# ------------------------------------------------------------
# 默认按本机安装位置查找；若你的安装路径不同，无需改本文件，
# 只需在 qmake 时通过变量覆盖，例如：
#   qmake "OPENCV_ROOT=D:/opencv/your-install-dir"
# ============================================================
isEmpty(OPENCV_ROOT) {
    OPENCV_ROOT = D:/opencv/opencv3.4-qt-intall/install
}

!exists($$OPENCV_ROOT) {
    error("未找到 OpenCV 目录：$$OPENCV_ROOT 。请用 qmake \"OPENCV_ROOT=你的路径\" 指定。")
}

INCLUDEPATH += $$OPENCV_ROOT/include \
               $$OPENCV_ROOT/include/opencv \
               $$OPENCV_ROOT/include/opencv2

# 链接目录（该发行版为 MinGW 32bit，库位于 x86/mingw/lib）
OPENCV_LIBDIR = $$OPENCV_ROOT/x86/mingw/lib

!exists($$OPENCV_LIBDIR) {
    error("未找到 OpenCV 库目录：$$OPENCV_LIBDIR")
}

# ------------------------------------------------------------
# 按实际使用到的模块精确链接，避免把 45 个库全部拖进来：
#   core        cv::Mat 等基础数据结构
#   imgproc     cvtColor / resize / equalizeHist
#   imgcodecs   imread / imwrite
#   videoio     VideoCapture 摄像头采集
#   objdetect   CascadeClassifier 人脸检测
#   face        LBPHFaceRecognizer 人脸识别
# ------------------------------------------------------------
OPENCV_MODULES = core imgproc imgcodecs videoio objdetect face

for(mod, OPENCV_MODULES) {
    LIBS += -L$$OPENCV_LIBDIR -lopencv_$${mod}345
}

RESOURCES += \
    image.qrc
