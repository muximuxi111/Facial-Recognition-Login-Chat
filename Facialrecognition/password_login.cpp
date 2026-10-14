#include "password_login.h"
#include "ui_password_login.h"

#include <QLabel>
#include <QFrame>

Password_login::Password_login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Password_login)
{
    // ★ 这里仍然调用 setupUi，让它建好 ui 里的控件对象
    //   下面我们把这些控件的指针复制到自己的公有成员上
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/new/prefix1/image/password_login.png"));

    // 把 ui 的成员"接"到公有成员
    background_label  = new QLabel(this);
    username_label    = new QLabel("账 户", this);
    password_label    = new QLabel("密 码", this);
    username_lineEdit = new QLineEdit(this);
    password_lineEdit = new QLineEdit(this);
    login_pushBtn     = new QPushButton("登录", this);
    back_pushBtn      = new QPushButton("返回", this);

    // ==================== 窗口设置 ====================
    this->setFixedSize(800, 700);
    this->setWindowTitle("账号密码登录");
    this->setObjectName("password_login");

    // ==================== 背景图片 ====================
    background_label->setGeometry(0, 0, 800, 700);
    background_label->setStyleSheet(
        "QLabel{"
        "   border-image:url(:/new/prefix1/image/background3.jpg);"
        "}"
    );
    background_label->lower();

    // 半透明遮罩
    QLabel *overlay = new QLabel(this);
    overlay->setGeometry(0, 0, 800, 700);
    overlay->setStyleSheet("background-color:rgba(0,10,20,110);");
    overlay->lower();

    // ==================== 主标题 ====================
    QLabel *title = new QLabel("账号密码登录", this);
    title->setGeometry(0, 70, 800, 80);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "QLabel{"
        "   color:#00ffff;"
        "   font-family:'Microsoft YaHei';"
        "   font-size:44px;"
        "   font-weight:bold;"
        "   background:transparent;"
        "}"
    );

    // ==================== 副标题 ====================
    QLabel *subtitle = new QLabel("WELCOME  BACK", this);
    subtitle->setGeometry(0, 155, 800, 30);
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setStyleSheet(
        "QLabel{"
        "   color:rgba(0,255,255,160);"
        "   font-family:'Microsoft YaHei';"
        "   font-size:16px;"
        "   background:transparent;"
        "}"
    );

    // ==================== 玻璃卡片 ====================
    QFrame *card = new QFrame(this);
    card->setGeometry(140, 210, 520, 420);
    card->setStyleSheet(
        "QFrame{"
        "   background-color:rgba(15,25,40,190);"
        "   border:1px solid rgba(0,255,255,70);"
        "   border-radius:22px;"
        "}"
    );

    // 卡片顶部渐变装饰线
    QFrame *topLine = new QFrame(card);
    topLine->setGeometry(60, 0, 400, 3);
    topLine->setStyleSheet(
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,"
        "stop:0 rgba(0,255,255,0),"
        "stop:0.5 rgba(0,255,255,255),"
        "stop:1 rgba(0,255,255,0));"
    );

    // ==================== 标签样式 ====================
    QString labelStyle =
        "QLabel{"
        "   color:#a0e8ff;"
        "   font-family:'Microsoft YaHei';"
        "   font-size:20px;"
        "   font-weight:bold;"
        "   background:transparent;"
        "}";

    username_label->setStyleSheet(labelStyle);
    password_label->setStyleSheet(labelStyle);
    username_label->setText("账 户");
    password_label->setText("密 码");

    // ==================== 输入框 ====================
    username_lineEdit->setPlaceholderText("请输入账号");
    password_lineEdit->setPlaceholderText("请输入密码");
    password_lineEdit->setEchoMode(QLineEdit::Password);

    QString lineEditStyle =
        "QLineEdit{"
        "   background-color:rgba(0,0,0,180);"
        "   border:2px solid rgba(0,180,200,120);"
        "   border-radius:12px;"
        "   color:white;"
        "   font-family:'Microsoft YaHei';"
        "   font-size:22px;"
        "   padding-left:18px;"
        "   selection-background-color:#00ffff;"
        "   selection-color:#002233;"
        "}"
        "QLineEdit:hover{"
        "   border:2px solid rgba(0,220,240,180);"
        "}"
        "QLineEdit:focus{"
        "   background-color:rgba(0,0,0,220);"
        "   border:2px solid #00ffff;"
        "}";

    username_lineEdit->setStyleSheet(lineEditStyle);
    password_lineEdit->setStyleSheet(lineEditStyle);

    // ==================== 登录按钮 ====================
    login_pushBtn->setStyleSheet(
        "QPushButton{"
        "   background:qlineargradient(x1:0,y1:0,x2:1,y2:1,"
        "       stop:0 #00c8ff, stop:1 #0088cc);"
        "   color:#ffffff;"
        "   font-family:'Microsoft YaHei';"
        "   font-size:22px;"
        "   font-weight:bold;"
        "   border:2px solid #00e0ff;"
        "   border-radius:14px;"
        "}"
        "QPushButton:hover{"
        "   background:qlineargradient(x1:0,y1:0,x2:1,y2:1,"
        "       stop:0 #00e0ff, stop:1 #00a0dd);"
        "   border:2px solid #00ffff;"
        "   color:#ffffff;"
        "}"
        "QPushButton:pressed{"
        "   background:qlineargradient(x1:0,y1:0,x2:1,y2:1,"
        "       stop:0 #007799, stop:1 #005f88);"
        "   border:2px solid #007799;"
        "   color:#ffffff;"
        "   padding-top:3px;"
        "}"
    );

    // ==================== 返回按钮 ====================
    back_pushBtn->setStyleSheet(
        "QPushButton{"
        "   background:qlineargradient(x1:0,y1:0,x2:1,y2:1,"
        "       stop:0 #1a3a55, stop:1 #0d2033);"
        "   color:#ffffff;"
        "   font-family:'Microsoft YaHei';"
        "   font-size:22px;"
        "   font-weight:bold;"
        "   border:2px solid #00a0c0;"
        "   border-radius:14px;"
        "}"
        "QPushButton:hover{"
        "   background:qlineargradient(x1:0,y1:0,x2:1,y2:1,"
        "       stop:0 #235070, stop:1 #103048);"
        "   border:2px solid #00ffff;"
        "   color:#ffffff;"
        "}"
        "QPushButton:pressed{"
        "   background:qlineargradient(x1:0,y1:0,x2:1,y2:1,"
        "       stop:0 #0a2030, stop:1 #061520);"
        "   border:2px solid #007799;"
        "   color:#ffffff;"
        "   padding-top:3px;"
        "}"
    );

    // ==================== 控件位置 ====================
    username_label->setGeometry(180, 260, 120, 30);
    username_lineEdit->setGeometry(180, 295, 440, 62);

    password_label->setGeometry(180, 385, 120, 30);
    password_lineEdit->setGeometry(180, 420, 440, 62);

    login_pushBtn->setGeometry(180, 520, 210, 66);
    back_pushBtn->setGeometry(410, 520, 210, 66);

    // 层级
    card->lower();
    title->raise();
    subtitle->raise();

    // ==================== 手动连接信号 ====================
    // ★ 原来依赖 ui->on_xxx_clicked 的自动连接；
    //   现在控件指针换了，需要用 Qt5 新语法手动连。
    connect(back_pushBtn, &QPushButton::clicked,
            this, &Password_login::on_back_pushBtn_clicked);

    connect(login_pushBtn, &QPushButton::clicked,
            this, &Password_login::on_login_pushBtn_clicked);

    qDebug()<<"password_login:"<<this;
}

Password_login::~Password_login()
{
    delete ui;
}

void Password_login::on_back_pushBtn_clicked()
{
    emit backsignal();
}

void Password_login::on_login_pushBtn_clicked()
{
    emit password_login_signal();
}
