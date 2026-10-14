#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QLabel>
#include <QTextBrowser>
#include <QTextEdit>
#include <QPushButton>
#include <QTcpSocket>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QPainter>
#include <QResizeEvent>
#include <QPixmap>
#include <QNetworkProxy>
#include <QDebug>
#include <QPainter>
#include <QPainterPath>

#define SERIP "127.0.0.1"
#define SERPORT "8888"

namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();
    void setupUI();
    void applyStyle();
    //把任意 pixmap 剪成圆形
    void resizeEvent(QResizeEvent *event) override;

signals:
    void back_signal();
    void send_message_signal();
private slots:
//    //读取服务器端发来数据
//    void readyReadSlot();
    // 发送按钮点击
    void onSendClicked();
    //退出按钮点击
    void onCloseClicked();

public:

    Ui::Client *ui;

    //背景
    QLabel *background_label;
    //头像
    QLabel *avatar_label;
    //用户名显示
    QLabel *username_label;
    //聊天显示区域
    QTextBrowser *chatBrowser;
    //消息输入框
    QTextEdit *messageEdit;
    //按钮
    QPushButton *send_pushBtn;
    QPushButton *close_pushBtn;
    //TCP通信
    QTcpSocket *tcpSocket;

};

#endif // CLIENT_H
