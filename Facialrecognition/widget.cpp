#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("人脸识别界面");
    this->setWindowIcon(QIcon(":/new/prefix1/image/face_login.png"));
    //隐藏当前界面
    this->hide();
    //显示登录界面
    log=new login;
    log->show();

    //初始化注册界面
    sign=new sign_up;
    //初始化数据库
    data=new database;
    qDebug()<<"Widget里面sign地址:"<<sign;
    //初始化账密登录界面
    pass_log=new Password_login;
    qDebug()<<"Widget里面pass_log地址:"<<pass_log;



    // ==============================
    // 初始化按钮状态：只启用"打开摄像头"
    // ==============================
    ui->openCameraBtn ->setEnabled(true);
    ui->closeCameraBtn->setEnabled(false);
    ui->inputFaceBtn  ->setEnabled(false);
    ui->faceCheckBtn  ->setEnabled(false);

    //级联分类器装载模型
    if(!c.load("D:/opencv/resources/haarcascade_frontalface_alt2.xml")){
         QMessageBox::information(this,"提示","人脸分类模型下载失败");

         return;
     }

    cli=new Client;
    cli->hide();
    // ==============================
        // 窗口设置
        // ==============================
        this->setFixedSize(800, 700);
        this->setWindowTitle("人脸识别界面");

        // ==============================
        // 背景图 + 暗色遮罩（和登录界面一致）
        // ==============================
        QLabel *background = new QLabel(this);
        background->setGeometry(0, 0, 800, 700);
        background->setStyleSheet(
            "border-image:url(:/new/prefix1/image/background3.jpg);"
        );
        background->lower();

        QLabel *overlay = new QLabel(this);
        overlay->setGeometry(0, 0, 800, 700);
        overlay->setStyleSheet("background-color:rgba(0,10,20,110);");
        overlay->lower();

        // ==============================
        // 标题
        // ==============================
        QLabel *title = new QLabel("人 脸 识 别", this);
        title->setGeometry(150, 25, 500, 55);
        title->setAlignment(Qt::AlignCenter);
        title->setStyleSheet(
            "QLabel{"
            "   color:#00ffff;"
            "   font-family:'Microsoft YaHei';"
            "   font-size:34px;"
            "   font-weight:bold;"
            "   background:transparent;"
            "}"
        );

        // 副标题
        QLabel *subtitle = new QLabel("FACE  RECOGNITION", this);
        subtitle->setGeometry(150, 82, 500, 22);
        subtitle->setAlignment(Qt::AlignCenter);
        subtitle->setStyleSheet(
            "QLabel{"
            "   color:rgba(0,255,255,160);"
            "   font-family:'Microsoft YaHei';"
            "   font-size:13px;"
            "   background:transparent;"
            "}"
        );

        // ==============================
        // 摄像头画面区（固定 400×400，居中）
        // ==============================
        // 800 宽窗口，居中：x = (800-400)/2 = 200
        ui->cameraLab->setGeometry(200, 120, 400, 400);
        ui->cameraLab->setAlignment(Qt::AlignCenter);
        ui->cameraLab->setText("人脸图像");
        ui->cameraLab->setStyleSheet(
            "QLabel{"
            "   background-color:rgba(0,0,0,180);"
            "   border:2px solid #00ffff;"
            "   border-radius:14px;"
            "   color:#7fdfff;"
            "   font-family:'Microsoft YaHei';"
            "   font-size:22px;"
            "}"
        );

        // ==============================
        // 四个按钮：一行四个，居中
        // ==============================
        // 800 宽，4 个按钮各 175 宽，间距 12
        // 总宽 = 175*4 + 12*3 = 736，起始 x = (800-736)/2 = 32
        const int btnW   = 175;
        const int btnH   = 66;
        const int gap    = 12;
        const int btnY   = 560;              // 摄像头框下方 40px
        const int startX = (800 - (btnW * 4 + gap * 3)) / 2;

        ui->openCameraBtn ->setGeometry(startX,                    btnY, btnW, btnH);
        ui->closeCameraBtn->setGeometry(startX + btnW + gap,       btnY, btnW, btnH);
        ui->inputFaceBtn  ->setGeometry(startX + (btnW + gap) * 2, btnY, btnW, btnH);
        ui->faceCheckBtn  ->setGeometry(startX + (btnW + gap) * 3, btnY, btnW, btnH);

        ui->openCameraBtn ->setCursor(Qt::PointingHandCursor);
        ui->closeCameraBtn->setCursor(Qt::PointingHandCursor);
        ui->inputFaceBtn  ->setCursor(Qt::PointingHandCursor);
        ui->faceCheckBtn  ->setCursor(Qt::PointingHandCursor);

        // ==============================
        // 按钮样式（统一蓝色，禁用变灰）
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
            "   border-radius:14px;"
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
            "}"
            "QPushButton:disabled{"
            "   background:qlineargradient(x1:0,y1:0,x2:0,y2:1,"
            "       stop:0 #555555, stop:1 #333333);"
            "   color:rgba(255,255,255,120);"
            "   border:2px solid #666666;"
            "}";

        ui->openCameraBtn ->setStyleSheet(btnStyle);
        ui->closeCameraBtn->setStyleSheet(btnStyle);
        ui->inputFaceBtn  ->setStyleSheet(btnStyle);
        ui->faceCheckBtn  ->setStyleSheet(btnStyle);



    //人脸识别成功，发送信号给其他界面展示
    connect(this,&Widget::jump_signal,this,&Widget::face_login_success_treat);

    //账密登录信号处理
    connect(log,&login::password_login_signal,this,&Widget::password_login_treat);

    //注册界面信号处理
    connect(log,&login::sign_up_signal,this,&Widget::sign_up_treat);

    //当登录界面发出请求人脸识别登录信号
    connect(log,&login::face_login_signal,this,&Widget::face_login_treat);

    //处理客户端界面返回信号
    connect(cli,&Client::back_signal,this,&Widget::client_back_treat);

    //处理注册界面返回信号
    connect(sign,&sign_up::backsignal,this,&Widget::sign_back_treat);

    //处理账密登录界面返回信号
    connect(pass_log,&Password_login::backsignal,this,&Widget::passwordlogin_back_treat);

    //处理注册界面发来的注册信号
    connect(sign,&sign_up::sign_up_signal,this,&Widget::sign_up_signal_treat);

    //处理登录界面发来的登录信号
    connect(pass_log,&Password_login::password_login_signal,this,&Widget::password_login_signal_treat);

    //处理TCP读取信号
    connect(cli->tcpSocket,&QTcpSocket::readyRead,this,&Widget::readyRead_treat);
    //处理发送信息按钮点击信号
    connect(cli,&Client::send_message_signal,this,&Widget::send_message_treat);
    //TCP连接错误信息处理
    connect(cli->tcpSocket,QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error),this,[=](QAbstractSocket::SocketError)
    {
        qDebug() << cli->tcpSocket->errorString();
    });

}

Widget::~Widget()
{
    delete ui;
    delete cli;
    delete log;
    delete sign;
    delete data;
    delete pass_log;
}

void Widget::timerEvent(QTimerEvent *e)
{
    //开启摄像头后的运行逻辑
    if(e->timerId()==cameraTiemrId){
        video.read(src);
        flip(src,src,1);
        cvtColor(src,rgb,CV_BGR2RGB);
        cv::resize(rgb,rgb,Size(400,400));
        cvtColor(rgb,gray,CV_BGR2GRAY);
        cv::equalizeHist(gray,dest);
        c.detectMultiScale(dest,faces);
        for (unsigned int i=0;i<faces.size();i++) {
            cv::rectangle(rgb,faces[i],Scalar(0,0,255),2);
        }
        QImage image = QImage(rgb.data
                              ,rgb.cols
                              ,rgb.rows
                              ,rgb.cols*rgb.channels()
                              ,QImage::Format_RGB888
                              );
        QPixmap pix=QPixmap::fromImage(image);
        ui->cameraLab->setPixmap(pix);
        ui->openCameraBtn->setEnabled(false);
        ui->closeCameraBtn->setEnabled(true);
    }

    //启动人脸录入后的运行逻辑
    if(e->timerId()==inputTimerId){
        qDebug()<<"正在人脸录入请稍后";

        if(faces.empty()){
            return;
        }

        Mat face=src(faces[0]);
        cv::resize(face,face,Size(100,100));
        cvtColor(face,face,CV_BGR2GRAY);
        equalizeHist(face,face);

        input_faces.push_back(face);
        input_labs.push_back(1);

        if(input_faces.size()==50){
            recognizer->update(input_faces,input_labs);
            recognizer->save("D:/opencv/resources/myface.xml");
            input_labs.clear();
            input_faces.clear();
            this->killTimer(inputTimerId);

            // 录入完成后恢复其他按钮
            ui->closeCameraBtn->setEnabled(true);
            ui->inputFaceBtn  ->setEnabled(true);
            ui->faceCheckBtn  ->setEnabled(true);

            QMessageBox::information(this,"提示","录入成功");
        }
    }

    //启动人脸识别后的运行逻辑
    if(e->timerId()==faceLoginTimerid){
        qDebug()<<"正在登录请稍后";

        if(faces.empty()||recognizer.empty()){
            return;
        }

        Mat face=src(faces[0]);
        cv::resize(face,face,Size(100,100));
        cvtColor(face,face,CV_BGR2GRAY);
        equalizeHist(face,face);

        int out_lab=-1;
        double out_conf=0.0;

        recognizer->predict(face,out_lab,out_conf);
         qDebug()<<"out_lab = "<<out_lab<<"     out_conf = "<<out_conf;

         if(out_lab!=-1){
             QMessageBox::information(this, "提示", "欢迎回来");
             killTimer(faceLoginTimerid);
             this->killTimer(cameraTiemrId);
             video.release();

             // 恢复所有按钮
//             ui->closeCameraBtn->setEnabled(true);
//             ui->faceCheckBtn->setEnabled(true);
//             ui->inputFaceBtn->setEnabled(true);

             emit jump_signal();
         }

    }
}

//打开摄像头按钮
void Widget::on_openCameraBtn_clicked()
{
    //打开摄像头
    if(!video.open(0)){
        QMessageBox::information(this,"提示","摄像头打开失败");
        qDebug()<<"摄像头打开失败"<<endl;
        return ;
    }

    // 打开摄像头成功后，启用其他三个按钮
    ui->closeCameraBtn->setEnabled(true);
    ui->inputFaceBtn  ->setEnabled(true);
    ui->faceCheckBtn  ->setEnabled(true);

    cameraTiemrId=this->startTimer(30);
}

//关闭摄像头按钮
void Widget::on_closeCameraBtn_clicked()
{
    //关闭定时器
    this->killTimer(cameraTiemrId);

    //关闭摄像头
    video.release();

    //清空容器内容
    ui->cameraLab->clear();
    ui->cameraLab->setText("人脸图像");     // 恢复占位文字

    // 关闭摄像头后：只保留"打开摄像头"可用，其余全部禁用
    ui->openCameraBtn ->setEnabled(true);
    ui->closeCameraBtn->setEnabled(false);
    ui->inputFaceBtn  ->setEnabled(false);
    ui->faceCheckBtn  ->setEnabled(false);
}

//人脸录入按钮
void Widget::on_inputFaceBtn_clicked()
{
    ui->closeCameraBtn->setEnabled(false);

    //给人脸识别器实例化一个空对象
    recognizer = LBPHFaceRecognizer::create();

    qDebug()<<"开始录入人脸"<<endl;

    //人脸录入的定时器
    inputTimerId = this->startTimer(50);
}

//人脸识别按钮
void Widget::on_faceCheckBtn_clicked()
{
    //找到人脸模型
      QFile file("D:/opencv/resources/myface.xml");
      //装载人脸识别器对象
      if(!file.exists())
      {
          QMessageBox::information(this,"提示", "无数据可用");
          return;
      }
      recognizer = FaceRecognizer::load<LBPHFaceRecognizer>("D:/opencv/resources/myface.xml");

      //启动一个定时器
      faceLoginTimerid = startTimer(50);

      //将相关组件禁用
      ui->closeCameraBtn->setEnabled(false);
      ui->faceCheckBtn->setEnabled(false);
      ui->inputFaceBtn->setEnabled(false);

      //设置可信度
      recognizer->setThreshold(80);
}

//人脸识别成功信号处理
void Widget::face_login_success_treat()
{
    this->hide();

    //清空容器内容
    ui->cameraLab->clear();
    ui->cameraLab->setText("人脸图像");     // 恢复占位文字

    // 关闭摄像头后：只保留"打开摄像头"可用，其余全部禁用
    ui->openCameraBtn ->setEnabled(true);
    ui->closeCameraBtn->setEnabled(false);
    ui->inputFaceBtn  ->setEnabled(false);
    ui->faceCheckBtn  ->setEnabled(false);
    //连接服务器
    QString ip=SERIP;
    QString port=SERPORT;
    //connectToHost连接服务器
    cli->tcpSocket->connectToHost(ip,port.toUShort());
    //waitForConnected判断是否连接成功，设置等待时间
    if(cli->tcpSocket->waitForConnected(3000)){
        cli->chatBrowser->setText(QString("%1加入聊天室......").arg(cli->username_label->text()));
        cli->tcpSocket->write(QString("%1加入聊天室......").arg(cli->username_label->text()).toLocal8Bit());
    }
    else{
        cli->chatBrowser->setText(QString("%1加入聊天室失败......").arg(cli->username_label->text()));
    }
    cli->show();
}
//进入人脸识别界面
void Widget::face_login_treat()
{
    this->show();
    log->hide();
}
//账密登录信号处理
void Widget::password_login_treat()
{
    log->hide();
    pass_log->show();
}
//进入注册界面信号处理
void Widget::sign_up_treat()
{
    log->hide();
    sign->show();
}
//客户端界面返回信号处理
void Widget::client_back_treat()
{
    cli->hide();
    log->show();
}

//注册界面返回信号处理
void Widget::sign_back_treat()
{
    sign->hide();
    log->show();
}

//账密登录界面返回信号处理
void Widget::passwordlogin_back_treat()
{
    pass_log->hide();
    log->show();
}

//注册界面发送的注册信号处理
void Widget::sign_up_signal_treat()
{
    qDebug()<<"进入注册信号处理函数"<<endl;
    QString username=sign->username_edit->text();
    QString password=sign->password_edit->text();

    QString sql = QString("insert into  user_info  values ('%1', '%2')").arg(username).arg(password);
    if(data->query->exec(sql))
    {
        qDebug() << "插入数据成功....." << endl;
        sign->hide();
        log->show();
        QMessageBox::information(this,"提示","注册成功！");
        //注册成功后清空行编辑器的账号密码
        sign->username_edit->clear();
        sign->password_edit->clear();
        sign->confirm_edit->clear();
    }
    else
    {
        qDebug() << "插入数据失败....." << endl;
    }
}

//账密登录界面的登录信号处理
void Widget::password_login_signal_treat()
{
    qDebug() << "进入账密登录信号处理函数";
    QString sql = "select * from user_info";

    if (data->query->exec(sql))
    {
        bool ok = false;
        while (data->query->next())
        {
            if (pass_log->username_lineEdit->text() == data->query->value(0).toString()
                && pass_log->password_lineEdit->text() == data->query->value(1).toString())
            {
                qDebug() << "查询成功.....";
                pass_log->hide();
                cli->show();
                /*********************设置客户端用户名*********************/
                cli->username_label->setText(data->query->value(0).toString());
                QPixmap pix(":/new/prefix1/image/head_image3.png");
                cli->avatar_label->setPixmap(pix);
                /*********************连接服务器*********************/
                QString ip=SERIP;
                QString port=SERPORT;
                //connectToHost连接服务器
                cli->tcpSocket->connectToHost(ip,port.toUShort());
                //waitForConnected判断是否连接成功，设置等待时间
                if(cli->tcpSocket->waitForConnected(3000)){
                    cli->chatBrowser->setText(QString("%1加入聊天室......").arg(cli->username_label->text()));
                    cli->tcpSocket->write(QString("%1加入聊天室......").arg(cli->username_label->text()).toLocal8Bit());
                }
                else{
                    cli->chatBrowser->setText(QString("%1加入聊天室失败......").arg(cli->username_label->text()));
                }
                //清空行编辑器的账号密码
                pass_log->username_lineEdit->clear();
                pass_log->password_lineEdit->clear();
                ok = true;
                break;
            }
        }
        if (!ok) {
            QMessageBox::warning(pass_log, "警告", "账号或密码错误");
            pass_log->password_lineEdit->clear();
            pass_log->password_lineEdit->setFocus();
        }
    }
    else
    {
        qDebug() << "查询失败.....";
        QMessageBox::warning(pass_log, "警告", "数据库查询失败");
    }
}

void Widget::readyRead_treat()
{
    QByteArray  buff;
    buff = cli->tcpSocket->readAll();
    cli->chatBrowser->append(QString("%1").arg( QString::fromLocal8Bit(buff)));
}

void Widget::send_message_treat()
{
    QString buff = cli->messageEdit->toPlainText();
    QString all_buff = QString("%1:%2").arg(cli->username_label->text()).arg(buff);
    cli->tcpSocket->write(all_buff.toLocal8Bit());
    cli->chatBrowser->append(QString("(我)%1:%2").arg(cli->username_label->text()).arg(buff));
    //发送消息后清空消息输入框
    cli->messageEdit->clear();
}
