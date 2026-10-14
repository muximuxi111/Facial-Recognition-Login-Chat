#ifndef PASSWORD_LOGIN_H
#define PASSWORD_LOGIN_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QDebug>

namespace Ui {
class Password_login;
}

class Password_login : public QWidget
{
    Q_OBJECT

signals:
    //账密登录界面返回信号
    void backsignal();
    //账密登录信号
    void password_login_signal();
public:
    explicit Password_login(QWidget *parent = nullptr);
    ~Password_login();
    QLabel      *background_label  = nullptr;
    QLabel      *username_label    = nullptr;
    QLabel      *password_label    = nullptr;
    QLineEdit   *username_lineEdit = nullptr;
    QLineEdit   *password_lineEdit = nullptr;
    QPushButton *login_pushBtn     = nullptr;
    QPushButton *back_pushBtn      = nullptr;

private slots:
    void on_back_pushBtn_clicked();

    void on_login_pushBtn_clicked();

private:
    Ui::Password_login *ui;


};

#endif // PASSWORD_LOGIN_H
