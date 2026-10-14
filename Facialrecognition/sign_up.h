#ifndef SIGN_UP_H
#define SIGN_UP_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
class sign_up : public QWidget
{
    Q_OBJECT
public:
    explicit sign_up(QWidget *parent = nullptr);
     ~sign_up();
signals:
    //注册界面返回信号
    void backsignal();
    //发送注册信号
    void sign_up_signal();
public:
    QLabel *background_label;
    QLabel *title_label;

    QLabel *username_label;
    QLabel *password_label;
    QLabel *confirm_label;

    QLineEdit *username_edit;
    QLineEdit *password_edit;
    QLineEdit *confirm_edit;

    QPushButton *register_btn;
    QPushButton *back_btn;
private slots:
    //注册按钮处理
    void registerBtnSlot();
    //返回按钮处理
    void backBtnSlot();
};



#endif // SIGN_UP_H
