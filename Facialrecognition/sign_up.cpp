#include "sign_up.h"


sign_up::sign_up(QWidget *parent)
    : QWidget(parent)
{

    //窗口设置
    this->setFixedSize(800, 700);
    this->setWindowTitle("用户注册");
    this->setWindowIcon(QIcon(":/new/prefix1/image/register.png"));

    //背景图片
    background_label = new QLabel(this);
    background_label->setGeometry(0, 0, 800, 700);
    background_label->setPixmap(
        QPixmap(":/new/prefix1/image/background3.jpg")
    );
    background_label->setScaledContents(true);
    background_label->lower();

    // ============================================================
    // 标题（加大）
    // ============================================================
    title_label = new QLabel("用户注册", this);
    title_label->setGeometry(150, 45, 500, 90);
    title_label->setAlignment(Qt::AlignCenter);
    title_label->setStyleSheet(
        "QLabel{"
        "color:#00ffff;"
        "font-family:'Microsoft YaHei';"
        "font-size:44px;"                  // 38 → 44
        "font-weight:bold;"
        "background-color:rgba(0,0,0,120);"
        "border:2px solid #00ffff;"
        "border-radius:20px;"
        "}"
    );

    // ============================================================
    // 标签（加大 + 加宽 + 右对齐，贴紧输入框）
    // ============================================================
    username_label = new QLabel("用户名",   this);
    password_label = new QLabel("密  码",   this);
    confirm_label  = new QLabel("确认密码", this);

    // 上移一点、行距拉开到 95，标签宽度加大到 130
    username_label->setGeometry(120, 220, 140, 50);
    password_label->setGeometry(120, 315, 140, 50);
    confirm_label->setGeometry(120, 410, 140, 50);

    QString labelStyle =
        "QLabel{"
        "color:#00ffff;"
        "font-family:'Microsoft YaHei';"
        "font-size:26px;"                  // 22 → 26
        "font-weight:bold;"
        "}";

    username_label->setStyleSheet(labelStyle);
    password_label->setStyleSheet(labelStyle);
    confirm_label->setStyleSheet(labelStyle);

    // ============================================================
    // 输入框（加高 + 加宽 + 字体加大）
    // ============================================================
    username_edit = new QLineEdit(this);
    password_edit = new QLineEdit(this);
    confirm_edit  = new QLineEdit(this);

    // 与标签保持同一水平中线：标签 y=220 h=50 → 中线 245；输入框 y=215 h=62 → 中线 246 ✓
    username_edit->setGeometry(280, 214, 400, 62);
    password_edit->setGeometry(280, 309, 400, 62);
    confirm_edit ->setGeometry(280, 404, 400, 62);

    username_edit->setPlaceholderText("请输入用户名");
    password_edit->setPlaceholderText("请输入密码");
    confirm_edit ->setPlaceholderText("请再次输入密码");

    password_edit->setEchoMode(QLineEdit::Password);
    confirm_edit ->setEchoMode(QLineEdit::Password);

    QString editStyle =
        "QLineEdit{"
        "background-color:rgba(0,0,0,140);"
        "border:2px solid #00ffff;"
        "border-radius:14px;"
        "color:white;"
        "font-family:'Microsoft YaHei';"
        "font-size:24px;"                  // 22 → 24
        "padding-left:18px;"
        "selection-background-color:#00ffff;"
        "selection-color:#002233;"
        "}"
        "QLineEdit:focus{"
        "border:2px solid #ffffff;"
        "background-color:rgba(0,0,0,190);"
        "}";

    username_edit->setStyleSheet(editStyle);
    password_edit->setStyleSheet(editStyle);
    confirm_edit ->setStyleSheet(editStyle);

    // ============================================================
    // 按钮（加大 + 与登录页风格统一）
    // ============================================================
    register_btn = new QPushButton("注册", this);
    back_btn     = new QPushButton("返回", this);

    register_btn->setGeometry(200, 540, 180, 68);
    back_btn    ->setGeometry(420, 540, 180, 68);

    register_btn->setCursor(Qt::PointingHandCursor);
    back_btn    ->setCursor(Qt::PointingHandCursor);

    // 注册 = 主按钮（青色实心渐变）
    QString registerStyle =
        "QPushButton{"
        "   background:qlineargradient(x1:0,y1:0,x2:1,y2:1,"
        "       stop:0 #00d4ff, stop:1 #0099cc);"
        "   color:#ffffff;"
        "   font-family:'Microsoft YaHei';"
        "   font-size:24px;"
        "   font-weight:bold;"
        "   border:2px solid #00e0ff;"
        "   border-radius:14px;"
        "}"
        "QPushButton:hover{"
        "   background:qlineargradient(x1:0,y1:0,x2:1,y2:1,"
        "       stop:0 #00ffff, stop:1 #00b3dd);"
        "   border:2px solid #00ffff;"
        "}"
        "QPushButton:pressed{"
        "   background:qlineargradient(x1:0,y1:0,x2:1,y2:1,"
        "       stop:0 #007799, stop:1 #005f88);"
        "   border:2px solid #007799;"
        "   padding-top:3px;"
        "}";

    // 返回 = 次按钮（深蓝实心渐变，字体颜色 / 交互一致）
    QString backStyle =
        "QPushButton{"
        "   background:qlineargradient(x1:0,y1:0,x2:1,y2:1,"
        "       stop:0 #1a3a55, stop:1 #0d2033);"
        "   color:#ffffff;"
        "   font-family:'Microsoft YaHei';"
        "   font-size:24px;"
        "   font-weight:bold;"
        "   border:2px solid #00a0c0;"
        "   border-radius:14px;"
        "}"
        "QPushButton:hover{"
        "   background:qlineargradient(x1:0,y1:0,x2:1,y2:1,"
        "       stop:0 #235070, stop:1 #103048);"
        "   border:2px solid #00ffff;"
        "}"
        "QPushButton:pressed{"
        "   background:qlineargradient(x1:0,y1:0,x2:1,y2:1,"
        "       stop:0 #0a2030, stop:1 #061520);"
        "   border:2px solid #007799;"
        "   padding-top:3px;"
        "}";

    register_btn->setStyleSheet(registerStyle);
    back_btn    ->setStyleSheet(backStyle);

    // ============================================================
    // 信号槽（保持不变）
    // ============================================================
    connect(register_btn, &QPushButton::clicked,
            this, &sign_up::registerBtnSlot);
    connect(back_btn, &QPushButton::clicked,
            this, &sign_up::backBtnSlot);

    qDebug()<<"sign对象地址:"<<this;
}

sign_up::~sign_up()
{

}

void sign_up::registerBtnSlot()
{
    if(password_edit->text()==confirm_edit->text()){
        qDebug()<<"注册信号发送"<<endl;
        emit sign_up_signal();
    }
    else{
        QMessageBox::warning(this,"警告","两次密码输入不一致");
    }
}

void sign_up::backBtnSlot()
{
    emit backsignal();
}
