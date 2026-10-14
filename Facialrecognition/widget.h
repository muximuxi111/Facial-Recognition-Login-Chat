#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include<opencv2/face.hpp>
#include <vector>
#include <map>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QTimerEvent>
#include<QtSerialPort/QtSerialPort>
#include<QtSerialPort/QSerialPortInfo>
#include<QLabel>
#include<QPushButton>
#include <QNetworkProxy>
#include <QTcpSocket>
#include "client.h"
#include "login.h"
#include "sign_up.h"
#include "database.h"
#include "password_login.h"
using namespace  cv;
using namespace cv::face;
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //初始化聊天室界面
    Client *cli;
    //初始化登录界面
    login *log;
    //初始化注册界面
    sign_up *sign;
    //初始化数据库
    database *data;
    //初始化账密登录界面
    Password_login *pass_log;


signals:
    void jump_signal();
private slots:
    void timerEvent(QTimerEvent *e);
    //点击打开摄像头按钮处理
    void on_openCameraBtn_clicked();
    //点击关闭摄像头按钮处理
    void on_closeCameraBtn_clicked();
    //点击录入人脸按钮处理
    void on_inputFaceBtn_clicked();
    //点击人脸识别按钮按钮处理
    void on_faceCheckBtn_clicked();
    //处理面部识别成功的信号
    void face_login_success_treat();
    //人脸登录信号处理
    void face_login_treat();
    //账密登录界面信号处理
    void password_login_treat();
    //注册界面信号处理
    void sign_up_treat();
    //客户端界面返回信号处理
    void client_back_treat();
    //注册界面返回信号处理
    void sign_back_treat();
    //账密登录界面返回信号处理
    void passwordlogin_back_treat();
    //注册界面发送的注册信号处理
    void sign_up_signal_treat();
    //账密登录界面的登录信号处理
    void password_login_signal_treat();
    //客户端接收消息信号处理
    void readyRead_treat();
    //客户端发送消息信号处理
    void send_message_treat();



private:
    Ui::Widget *ui;
    /********************摄像头有关变量**********************/
    Mat src;        //用于存储图像
    Mat rgb;        //存储rgb图像
    Mat gray;       //存储灰度图像
    Mat dest;       //存储均衡化图像
    VideoCapture video;//视频流对象，用于存储视频数据
    CascadeClassifier c;//定义级联分类对象(找到图像中人脸的矩形区域)
    vector<Rect>faces;//存储人脸矩形区域
    int cameraTiemrId;//展示摄像头的定时器

    /********************人脸录入有关变量**********************/
    Ptr<FaceRecognizer> recognizer;     //人脸识别器
    vector<Mat> input_faces;            //要进行人脸训练的脸的容器
    vector<int>input_labs;              //每张脸对应的编号
    int inputTimerId;                   //人脸录入定时器

    /********************人脸识别有关变量**********************/
    int faceLoginTimerid;       //人脸登录的定时器
};
#endif // WIDGET_H
