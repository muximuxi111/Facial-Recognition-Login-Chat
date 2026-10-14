#include "client.h"
#include "ui_client.h"


Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/new/prefix1/image/chat_room.png"));
    this->resize(1000, 700);
    this->setMinimumSize(720, 520);
    this->setWindowTitle("网络聊天室");

    // ============================================================
    // 在这里初始化所有控件对象
    // ============================================================

    // 背景
    background_label = new QLabel(this);
    background_label->setObjectName("background");
    background_label->setGeometry(0, 0, width(), height());
    background_label->lower();
    background_label->setScaledContents(true);

    // 左栏头像
    avatar_label = new QLabel(this);
    avatar_label->setObjectName("avatar");
    avatar_label->setFixedSize(120, 120);
    avatar_label->setAlignment(Qt::AlignCenter);

    // 方形头像
    QPixmap pix(":/new/prefix1/image/head_image.png");
    pix = pix.scaled(120, 120,
                     Qt::KeepAspectRatioByExpanding,
                     Qt::SmoothTransformation);
    avatar_label->setPixmap(pix);

    // 用户名
    username_label = new QLabel("muxi", this);
    username_label->setObjectName("username");
    username_label->setAlignment(Qt::AlignCenter);

    // 退出按钮
    close_pushBtn = new QPushButton("退出", this);
    close_pushBtn->setObjectName("closeBtn");
    close_pushBtn->setCursor(Qt::PointingHandCursor);
    close_pushBtn->setFixedHeight(44);

    // 聊天显示区
    chatBrowser = new QTextBrowser(this);
    chatBrowser->setObjectName("chatBrowser");
    chatBrowser->setPlaceholderText("暂无消息…");
    chatBrowser->document()->setDefaultStyleSheet("p{ line-height:150%; }");

    // ★ 输入框：不再固定高度，改成"最小 + 上限 + 可伸缩"
    messageEdit = new QTextEdit(this);
    messageEdit->setObjectName("messageEdit");
    messageEdit->setPlaceholderText("请输入消息…");
    messageEdit->setMinimumHeight(120);
    messageEdit->setMaximumHeight(240);
    messageEdit->setSizePolicy(QSizePolicy::Expanding,
                               QSizePolicy::Preferred);

    // ★ 发送按钮：宽度固定一点，高度跟着输入框伸缩
    send_pushBtn = new QPushButton("发送", this);
    send_pushBtn->setObjectName("sendBtn");
    send_pushBtn->setCursor(Qt::PointingHandCursor);
    send_pushBtn->setMinimumWidth(120);
    send_pushBtn->setMinimumHeight(60);
    send_pushBtn->setSizePolicy(QSizePolicy::Preferred,
                                QSizePolicy::Expanding);

    /**********************************TCP通信模块*****************************************/

    // TCP
    tcpSocket = new QTcpSocket(this);
//    //连接服务器
//    QString ip=SERIP;
//    QString port=SERPORT;
//    //connectToHost连接服务器
//    tcpSocket->connectToHost(ip,port.toUShort());
//    //waitForConnected判断是否连接成功，设置等待时间
//    if(tcpSocket->waitForConnected(3000)){
//        chatBrowser->setText(QString("%1加入聊天室......").arg(username_label->text()));
//    }
//    else{
//        chatBrowser->setText(QString("%1加入聊天室失败......").arg(username_label->text()));
//    }

    // 连接信号
    connect(send_pushBtn, &QPushButton::clicked,
            this, &Client::onSendClicked);
    connect(close_pushBtn, &QPushButton::clicked,
            this, &Client::onCloseClicked);

//    connect(tcpSocket,&QTcpSocket::readyRead,this,&Client::readyReadSlot);
//    connect(tcpSocket,QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error),this,[=](QAbstractSocket::SocketError)
//    {
//        qDebug() << tcpSocket->errorString();
//    });


    // ============================================================
    // 布局 + 样式
    // ============================================================
    setupUI();
    applyStyle();
}



Client::~Client()
{
    delete ui;
}

//void Client::readyReadSlot(){
//    QByteArray  buff;
//    buff = tcpSocket->readAll();
//    chatBrowser->append(QString("%1").arg( QString::fromLocal8Bit(buff)));

//}

void Client::onSendClicked()
{
    emit send_message_signal();
//    QString buff = messageEdit->toPlainText();
//    QString all_buff = QString("%1:%2").arg(username_label->text()).arg(buff);
//    tcpSocket->write(all_buff.toLocal8Bit());
//    chatBrowser->append(QString("(我)%1:%2").arg(username_label->text()).arg(buff));
//    //发送消息后清空消息输入框
//    messageEdit->clear();
}

void Client::onCloseClicked()
{
    qDebug()<<"clientback"<<endl;
    emit back_signal();
}

// ============================================================
// 背景图跟随窗口
// ============================================================
void Client::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    if (background_label) {
        background_label->setGeometry(0, 0, width(), height());
    }
}

// ============================================================
// 界面搭建
// ============================================================
void Client::setupUI()
{
    // ---------- 根布局 ----------
    QVBoxLayout *rootLayout = new QVBoxLayout(this);
    rootLayout->setContentsMargins(28, 24, 28, 24);
    rootLayout->setSpacing(14);

    // ============================================================
    // 顶部标题栏
    // ============================================================
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->setSpacing(8);

    QLabel *titleIcon = new QLabel("●", this);
    titleIcon->setObjectName("titleIcon");
    titleIcon->setFixedWidth(16);

    QLabel *titleLabel = new QLabel("网络聊天室", this);
    titleLabel->setObjectName("titleLabel");

    topLayout->addWidget(titleIcon);
    topLayout->addWidget(titleLabel);
    topLayout->addStretch();

    rootLayout->addLayout(topLayout);

    // ============================================================
    // 主体：左栏 | 右栏
    // ============================================================
    QHBoxLayout *bodyLayout = new QHBoxLayout();
    bodyLayout->setSpacing(18);

    // ---------- 左栏 ----------
    QFrame *leftPanel = new QFrame(this);
    leftPanel->setObjectName("leftPanel");
    leftPanel->setFixedWidth(200);

    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->setContentsMargins(16, 28, 16, 20);
    leftLayout->setSpacing(18);

    leftLayout->addWidget(avatar_label, 0, Qt::AlignHCenter);
    leftLayout->addWidget(username_label);
    leftLayout->addStretch();
    leftLayout->addWidget(close_pushBtn);

    // ---------- 右栏 ----------
    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->setSpacing(14);

    QHBoxLayout *inputRow = new QHBoxLayout();
    inputRow->setSpacing(12);

    inputRow->addWidget(messageEdit, 1);
    inputRow->addWidget(send_pushBtn);

    // ★ 聊天区 4 份，输入区 1 份，窗口拉大时按比例一起长
    rightLayout->addWidget(chatBrowser, 4);
    rightLayout->addLayout(inputRow, 1);

    // 组装
    bodyLayout->addWidget(leftPanel);
    bodyLayout->addLayout(rightLayout, 1);

    rootLayout->addLayout(bodyLayout, 1);

    // 背景保持在最底
    background_label->lower();
}

// ============================================================
// 样式
// ============================================================
void Client::applyStyle()
{
    QString qss = R"(
                  /* ===== 背景图 ===== */
                  #background{
                  border-image:url(:/new/prefix1/image/background1.jpg);
                  }

                  /* ===== 顶部标题 ===== */
                  #titleIcon{
                  color:#00ff9d;
                  font-size:18px;
                  background:transparent;
                  }

                  #titleLabel{
                  color:#00ffff;
                  font-family:'Microsoft YaHei';
                  font-size:22px;
                  font-weight:bold;
                  background:transparent;
                  }

                  /* ===== 左面板 ===== */
                  #leftPanel{
                  background-color:rgba(8,18,30,200);
                  border:1px solid rgba(0,255,255,90);
                  border-radius:16px;
                  }

                  /* ===== 方形头像 + 科技感边框 ===== */
                  #avatar{
                      background-color:#06121f;
                      border:2px solid #00ffff;
                      border-radius:10px;
                      padding:6px;
                      qproperty-alignment: AlignCenter;
                  }

                  #username{
                  color:#00ffff;
                  font-family:'Microsoft YaHei';
                  font-size:22px;
                  font-weight:bold;
                  background:transparent;
                  }

                  #closeBtn{
                  background-color:transparent;
                  color:#00ffff;
                  font-family:'Microsoft YaHei';
                  font-size:18px;
                  font-weight:bold;
                  border:2px solid #00ffff;
                  border-radius:10px;
                  }
                  #closeBtn:hover{
                  background-color:rgba(0,255,255,180);
                  color:#002233;
                  }
                  #closeBtn:pressed{
                  background-color:rgba(0,180,200,220);
                  }

                  /* ===== 聊天显示区（字体加大）===== */
                  #chatBrowser{
                  background-color:rgba(0,0,0,170);          /* 背景色 */
                  border:1px solid rgba(0,255,255,120);      /* 边框 */
                  border-radius:14px;                        /* 圆角 */
                  color:#e6faff;                             /* 文字颜色 */
                  font-family:'Microsoft YaHei';             /* 字体 */
                  font-size:30px;                            /* 字体大小 */
                  padding:16px 20px;                         /* 内边距 */
                  selection-background-color:#00ffff;        /* 选中时背景色 */
                  selection-color:#002233;                   /* 选中时文字色 */
                  }

                  /* ===== 滚动条 ===== */
                  QScrollBar:vertical{
                  background:transparent;
                  width:8px;
                  margin:4px;
                  }
                  QScrollBar::handle:vertical{
                  background:rgba(0,255,255,120);
                  border-radius:4px;
                  min-height:30px;
                  }
                  QScrollBar::handle:vertical:hover{
                  background:rgba(0,255,255,200);
                  }
                  QScrollBar::add-line:vertical,
                  QScrollBar::sub-line:vertical{ height:0; }
                  QScrollBar::add-page:vertical,
                  QScrollBar::sub-page:vertical{ background:transparent; }

                  /* ===== 输入框（字体加大）===== */
                  #messageEdit{
                  background-color:rgba(0,0,0,180);
                  border:1px solid rgba(0,255,255,120);
                  border-radius:12px;
                  color:white;
                  font-family:'Microsoft YaHei';
                  font-size:30px;
                  padding:12px 16px;
                  selection-background-color:#00ffff;
                  selection-color:#002233;
                  }
                  #messageEdit:focus{
                  border:2px solid #00ffff;
                  background-color:rgba(0,0,0,210);
                  }

                  /* ===== 发送按钮（QQ 风格）===== */
                  #sendBtn{
                  background:qlineargradient(x1:0,y1:0,x2:0,y2:1,
                  stop:0 #00d4ff, stop:1 #0088cc);
                  color:#ffffff;
                  font-family:'Microsoft YaHei';
                  font-size:22px;
                  font-weight:bold;
                  border:none;
                  border-radius:12px;
                  padding:0 24px;
                  }
                  #sendBtn:hover{
                  background:qlineargradient(x1:0,y1:0,x2:0,y2:1,
                  stop:0 #40e0ff, stop:1 #00a0dd);
                  }
                  #sendBtn:pressed{
                  background:qlineargradient(x1:0,y1:0,x2:0,y2:1,
                  stop:0 #006699, stop:1 #004f77);
                  padding-top:2px;
                  }
                  #sendBtn:disabled{
                  background:rgba(120,150,180,120);
                  color:rgba(255,255,255,180);
                  }
                  )";

    this->setStyleSheet(qss);
}
