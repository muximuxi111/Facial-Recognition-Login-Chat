#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include "password_login.h"
#include "sign_up.h"
#include "client.h"
#include "database.h"

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
//    Password_login *passwprd_log;
//    sign_up *sign;
//    database *data;

signals:
    //发送申请人脸识别信号
    void face_login_signal();
    //发送申请账密登录信号
    void password_login_signal();
    //发送申请注册信号
    void sign_up_signal();

private slots:
    void on_password_pushBtn_clicked();

    void on_sign_pushBtn_clicked();

    void on_face_pushBtn_clicked();
//    //注册界面返回信号处理
//    void sign_back_treat();
//    //账密登录界面返回信号处理
//    void passwordlogin_back_treat();
//    //注册成功返回信号处理
//    void signup_success_treat();


private:
    Ui::login *ui;
};

#endif // LOGIN_H
