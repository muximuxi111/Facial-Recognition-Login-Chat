#include "database.h"

database::database(QWidget *parent) : QWidget(parent)
{
    //1、加载数据库的驱动文件
    db = QSqlDatabase::addDatabase("QSQLITE");//我要使用sqlite数据库驱动

    //2、设置数据库的本地文件
   //db.setDatabaseName("user.db");//告诉qt数据库文件路径
    //使用绝对路径不然在build里运行文件找不到数据库
    db.setDatabaseName("D:\\C++\\QT\\day5\\build-Facialrecognition-Desktop_Qt_5_14_2_MinGW_32_bit-Debug\\user.db");

    //3、打开数据库
    if(db.open())//stu.db存在就打开，不存在就创建
    {
        qDebug() << "数据库打开成功......"  << endl;
    }
    else {
        qDebug() << "数据库打开失败....." << endl;
    }

    //4、创建发送SQL语句对象 发送SQL语句
    query = new QSqlQuery(db);
    QString sql =  "create  table   if  not  exists  user_info (username char(32), password char(32))";

    if(query->exec(sql))
    {
        qDebug() << "创建表格成功....." << endl;
    }
    else
    {
        qDebug() << "创建表格失败....." << endl;
    }

//    //数据库收到注册信号处理
//    connect(sign,&sign_up::sign_up_signal,this,&database::signup_signal_treat);
}

database::~database()
{
}

//void database::signup_signal_treat()
//{
//    QString username=sign->username_edit->text();
//    QString password=sign->password_edit->text();

//    QString sql = QString("insert into  user_info  values ('%1', '%2')").arg(username).arg(password);
//    if(query->exec(sql))
//    {
//        qDebug() << "插入数据成功....." << endl;
//    }
//    else
//    {
//        qDebug() << "插入数据失败....." << endl;
//    }
//}
