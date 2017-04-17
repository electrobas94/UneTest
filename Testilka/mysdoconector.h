#ifndef MYSDOCONECTOR_H
#define MYSDOCONECTOR_H
#include <QtNetwork>
#include <QDebug>


class MySdoConector:public QObject// работа с sdo
{
    Q_OBJECT


    bool postsucess;
    bool getsucess;
    bool sucess;

    QString fnam;
    QString snam;
    int kurs;

    QNetworkAccessManager *manager;

    bool GetRequest()
    {
        QUrl urlUser("http://sdo.vsu.by/user/profile.php");

        QNetworkRequest request(urlUser);
        request.setRawHeader("Accept-Encoding","identity");

        QNetworkReply* reply= manager->get(request);

        connect( reply, SIGNAL(finished()),
                 this, SLOT(replyFinished())
                 );
    }

    bool PostRequest(QString login, QString pass)
    {
        QUrl urlDoLogin("http://sdo.vsu.by/login/index.php");

        QString userName=login;//=  ui->lineEdit->text();    //  e-mail
        QString password=pass;//=   ui->lineEdit_2->text();  //  пароль

        /* Формирование  запроса на основе пользовательских данных */
        QByteArray postData;
        postData+= "username=" +  QUrl::toPercentEncoding( userName.toUtf8() );
        //postData+= "&cookieuser=1";
        postData+= "&password="+  QUrl::toPercentEncoding( password.toUtf8() );

        QNetworkRequest request(urlDoLogin);
        request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
        request.setRawHeader("Accept-Encoding","identity"); // Отменяю сжатие что бы, можно было нормально просматривать контент снифером

        QNetworkReply* reply= manager->post(request,postData);

                connect( reply, SIGNAL(finished()),
                         this, SLOT(replyFinishedPost())
                         );

        //QTimer::singleShot(1000, this, SLOT(doAnother()));// а всякий случай
    }

public:
    MySdoConector()
    {
        manager=new QNetworkAccessManager();
    }

    bool SingIn(QString login, QString pass, QString &ffname, QString &ssname, int &kurss)
    {
        delete manager;
        manager=new QNetworkAccessManager();

            sucess=false;// пароль и логин верны
           postsucess=false;
           getsucess=false;

           PostRequest(login, pass);// вводим логин и пароль

           for(int i=0;i<500;i++)// таймаут 5 секунд
           {
               if(postsucess)
                   break;//
               ///QTimer::singleShot(100, this, SLOT(doAnother()));// а всякий случай
           }

           GetRequest();

           for(int i=0;i<500;i++)// таймаут 5 секунд
           {
               if(getsucess)
                   break;

              // QTimer::singleShot(100, this, SLOT(doAnother()));// а всякий случай
           }

           kurss=kurs;
           ffname=fnam;
           ssname=snam;

            return sucess;
    }

public slots:
    bool replyFinishedPost()
    {
        postsucess=true;
    }

    bool replyFinished()// ответ от  гет
    {
        QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray content= reply->readAll();
            QTextCodec *codec = QTextCodec::codecForName("utf-8");
            QString tmp=codec->toUnicode(content.data()) ;

            //ui->textBrowser->setHtml(tmp);

            QString vv ="class=\"userprofile\"><h2>";
            int beg=tmp.indexOf(vv);
            if(beg=-1)
                sucess =false;
            beg+=24;

            int endd=tmp.indexOf("</h2><div class=\"userprofilebox");
            if(endd=-1)
                sucess =false;

            vv=tmp.mid(beg, endd-beg);

            beg=vv.indexOf(' ');

            fnam=vv.left(beg);
            snam=vv.right(beg);

            // ui->lineEdit_3->setText(vv);// first-sur- name

            vv="&nbsp; (";
            beg=tmp.indexOf(vv);
            if(beg=-1)
                sucess =false;
            beg+=8;
            endd=tmp.indexOf(" дн.");
            if(endd=-1)
                sucess =false;
            vv=tmp.mid(beg, endd-beg);

            kurs= vv.toInt()/365+1 ;// курс

            sucess=true;
        }
        else
        {
            getsucess=true;
            qDebug()<<reply->errorString();
            return false;

        }

        reply->deleteLater();

        sucess=true;
        getsucess=true;
    }
};

#endif // MYSDOCONECTOR_H
