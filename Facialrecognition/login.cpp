#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/new/prefix1/image/chat_room.png"));
    // ==============================
    // 固定窗口
    // ==============================
    this->setFixedSize(800, 700);
    this->setWindowTitle("网络聊天室");

    // ==============================
    // 背景图 + 暗色遮罩
    // ==============================
    ui->background_label->setGeometry(0, 0, 800, 700);
    ui->background_label->setStyleSheet(
        "border-image:url(:/new/prefix1/image/background3.jpg);"
    );
    ui->background_label->lower();

    QLabel *overlay = new QLabel(this);
    overlay->setGeometry(0, 0, 800, 700);
    overlay->setStyleSheet("background-color:rgba(0,10,20,110);");
    overlay->lower();
    ui->background_label->lower();

    // ==============================
    // 标题
    // ==============================
    ui->title_label->setGeometry(150, 60, 500, 80);
    ui->title_label->setAlignment(Qt::AlignCenter);
    ui->title_label->setText("网 络 聊 天 室");
    ui->title_label->setStyleSheet(
        "QLabel{"
        "   color:#00ffff;"
        "   font-family:'Microsoft YaHei';"
        "   font-size:40px;"
        "   font-weight:bold;"
        "   background:transparent;"      /* ★ 去掉黑底 */
        "}"
    );

    // 副标题
    QLabel *subtitle = new QLabel("CHAT  ROOM", this);
    subtitle->setGeometry(150, 140, 500, 30);
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setStyleSheet(
        "QLabel{"
        "   color:rgba(0,255,255,160);"
        "   font-family:'Microsoft YaHei';"
        "   font-size:14px;"
        "   background:transparent;"
        "}"
    );

    // ==============================
    // 头像（加圆形描边）
    // ==============================
    ui->image_label->setGeometry(300, 190, 200, 200);
    ui->image_label->setScaledContents(true);
    ui->image_label->setStyleSheet(
        "QLabel{"
        "   border:2px solid #00ffff;"
        "   background:transparent;"
        "}"
    );

    // ==============================
    // 三个按钮（等宽、等间距、居中）
    // ==============================
    // 800 宽，3 个按钮各 180 宽，间距 30
    // 总宽 = 180*3 + 30*2 = 600，起始 x = (800-600)/2 = 100
    const int btnW = 180;
    const int btnH = 60;
    const int btnY = 460;
    const int gap  = 30;
    const int startX = (800 - (btnW * 3 + gap * 2)) / 2;

    ui->password_pushBtn->setGeometry(startX,                         btnY, btnW, btnH);
    ui->sign_pushBtn    ->setGeometry(startX + btnW + gap,            btnY, btnW, btnH);
    ui->face_pushBtn    ->setGeometry(startX + (btnW + gap) * 2,      btnY, btnW, btnH);

    ui->password_pushBtn->setCursor(Qt::PointingHandCursor);
    ui->sign_pushBtn    ->setCursor(Qt::PointingHandCursor);
    ui->face_pushBtn    ->setCursor(Qt::PointingHandCursor);

    // ==============================
    // 按钮样式（青色科幻渐变）
    // ==============================
    QString btnStyle =
        "QPushButton{"
        "   background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "       stop:0 #00c8ff, stop:1 #0088cc);"
        "   color:#ffffff;"
        "   font-family:'Microsoft YaHei';"
        "   font-size:20px;"
        "   font-weight:bold;"
        "   border:2px solid #00e0ff;"
        "   border-radius:12px;"
        "}"
        "QPushButton:hover{"
        "   background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "       stop:0 #40e0ff, stop:1 #00a0dd);"
        "   border:2px solid #00ffff;"
        "}"
        "QPushButton:pressed{"
        "   background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "       stop:0 #006699, stop:1 #004f77);"
        "   border:2px solid #007799;"
        "   padding-top:3px;"
        "}";

    ui->password_pushBtn->setStyleSheet(btnStyle);
    ui->sign_pushBtn    ->setStyleSheet(btnStyle);
    ui->face_pushBtn    ->setStyleSheet(btnStyle);
}

login::~login()
{
    delete ui;
}

// 点击进入账密登录
void login::on_password_pushBtn_clicked()
{
    emit password_login_signal();
}

// 点击进入注册界面
void login::on_sign_pushBtn_clicked()
{
    emit sign_up_signal();
}

// 点击进入人脸识别
void login::on_face_pushBtn_clicked()
{
    emit face_login_signal();
}
