#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myadmin.h"
#include "form.h"
#include <QTimer>
#include <QFrame>
#include <QDesktopWidget>
#include <QtNetwork>
#include <QMovie>

//#include <QStyle>
bool flagus=false;
bool posend=false;
bool getend=false;
bool pc_base=false; // online/ofline mode

quint64 tim=30;
QNetworkAccessManager *manager;
MainWindow * mw;
QTimer* timer ;
MyAdmin *Admin=new MyAdmin();//все через интерфейс данного класса
QFrame *frm;// фрейм настроек базы

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //show();

    showFullScreen();
    //ui->pushButton_12->hide();
    //ui->pushButton_13->hide();
    manager=new QNetworkAccessManager(this);

    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());

    // ициализация таймера
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()) );
    //timer ->start(1000);

    ui->frame_3->hide();
    ui->frame_2->hide();
    ui->frame_4->hide();
    //ui->tabWidget->removeTab(2);
    ui->frame_10->layout()->setMargin(0);
    //ui->frame_10->setStyleSheet("background-color: #f0f0f0;");
    //Admin->SetTabWidget(ui->tabWidget_2);//список тестов
    Admin->SetTabWidget(ui->listWidget);//список вопросов
    Admin->SetTextVopros(ui->textBrowser_2);//текст текущего вопроса
    Admin->SetImageLabel(ui->label_2);// для отображения картинки
    Admin->SetOtweti(ui->verticalLayout_4);

    Admin->SetSUBDSetting(ui->lineEdit_3->text(),//host
                          ui->lineEdit_4->text(),//username
                          ui->lineEdit_5->text(),//pass
                          ui->lineEdit_6->text(),//dbname
                          ui->spinBox->value());//port

    QVBoxLayout *laut=new QVBoxLayout();
    laut->addWidget(ui->frame_9);
    frm=new QFrame();
    frm->setLayout(laut);

    //Admin->CloseConect();
    Admin->ConectBase();
    ui->comboBox->setEnabled(true);
    ui->textBrowser->setEnabled(true);

    Admin->RetTestList(ui->comboBox);

    if(Admin->TestSavLod->SUBD->GetStatus())//онлайн режми
    {
        if(ui->comboBox->count()==0)
        {
            QMessageBox msgBox;
            msgBox.addButton(QMessageBox::Ok);
            msgBox.addButton(QMessageBox::Cancel);
            msgBox.setText("В текущей базе нет тестов для открытия");
            return;

        }

        //RetKommentTest

    }
    else
    {
        QMessageBox msgBox;
        msgBox.addButton(QMessageBox::Ok);
        msgBox.addButton(QMessageBox::Cancel);
        msgBox.setText("Нет соединения с базой данных.\nПроверьте настройки подключения или\nоткройте тест в в автономном режиме");
        return;
    }

    ui->comboBox->activated(0);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTimeout()
{
    if(tim==0)
    {
        timer->stop();
        ui->pushButton_3->click();
        return;
    }
    tim--;
    quint32 tmp=tim;
    ui->spinBox_3->setValue(tmp%60);// ставим секнды
    tmp/=60; //минуты
    ui->spinBox_2->setValue(tmp%60);// ставим секнды
    tmp/=60; //минуты
    ui->spinBox_4->setValue(tmp%60);// ставим секнды
}


void MainWindow::on_pushButton_clicked()// PREV
{
    if(ui->listWidget->currentRow()!=0)
    {
        int tmp=Admin->ChangeVopros(ui->listWidget->currentRow()-1);
        ui->frame_7->setMaximumWidth(tmp);
        ui->frame_7->setMinimumWidth(tmp);
    }

    ui->label_4->setText(QString::number(ui->listWidget->currentRow()+1));
}

void MainWindow::on_pushButton_3_clicked()// завершить тест
{
    Admin->SaveVopros();

    ui->label_20->setText("<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Имя теста"
                          "</span></p></body></html>");
    ui->textBrowser->clear();
    ui->lineEdit_7->setText("Фамилия");
    ui->lineEdit_8->setText("Имя");
    ui->lineEdit_9->setText("Отчество");
    ui->comboBox_2->setCurrentIndex(0);
    ui->spinBox_5->setValue(1);
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox->activated(0);
    // pc_base=false;

    Form *formre=new Form(Admin->TestList->Current(), Admin);
    formre->showFullScreen();
    //formre->show();

    Admin->SaveVopros();
    //удаляем текущую картинку
    Admin->TestList->Current()->VoprosList->Current()->ClearOtwetGraf();//удаляем ответы


    // Admin->DeleteTest(0);
    ui->frame->show();
    ui->frame_3->hide();


}

void MainWindow::on_pushButton_4_clicked()// Начать тест
{
    if(pc_base)
    {

    }
    else
    {
        if(ui->comboBox->count()==0)
        {
            return;
        }


        ui->frame_4->show();
        ui->frame->hide();//пож подожди
        qApp->processEvents();

        Admin->OpenTestBD(Admin->TestSavLod->SUBD->RetTableName(ui->comboBox->currentIndex()));

    }

    ui->label->setText("<html><head/><body><p align=\"center\"><br/><span style="
                       "font-size:18pt; font-weight:600; color:#47304f;\">Тест:"+
                       Admin->TestList->Current()->GetTestName()
                       +"</span></p></body></html>");

    ui->label_6->setText(QString::number(Admin->TestList->Current()->VoprosList->Count()));
    ui->frame->hide();
    ui->frame_3->show();
    ui->label_4->setText(QString::number(1));

    if(Admin->TestList->Current()->VoprosList->Count()!=0)
    {
        int tmp=Admin->ChangeVopros(0);
        ui->frame_7->setMaximumWidth(tmp);
        ui->frame_7->setMinimumWidth(tmp);
    }

    ui->frame_4->hide();//пож подожди


    quint16 tmp=Admin->TestList->Current()->atrib;
    if(tmp%10==0)
    {

        ui->frame_10->hide();
        ui->pushButton->hide();
    }
    else if(tmp%10==1)
    {
        ui->frame_10->hide();
        ui->pushButton->show();
    }
    else
    {
        ui->frame_10->show();
        ui->pushButton->show();
    }

    tmp/=10;

    //            if(tmp==1 || tmp==3)
    //            randvop->setChecked(true);
    //            if(tmp==2 || tmp==3)
    //            randotwet->setChecked(true);

    if(Admin->TestList->Current()->attrib2>=10)// граничение по времени
    {
        tim=Admin->TestList->Current()->timeTest.s+Admin->TestList->Current()->timeTest.m*60+Admin->TestList->Current()->timeTest.h*60*60;
        timer ->start(1000);
    }

    if(Admin->TestList->Current()->attrib2%10==1)//показывать изображение
        ui->frame_7->show();
    else
        ui->frame_7->hide();

    Admin->TestList->Current()->FIO[0]=ui->lineEdit_7->text();
    Admin->TestList->Current()->FIO[1]=ui->lineEdit_8->text();
    Admin->TestList->Current()->FIO[2]=ui->lineEdit_9->text();

    if(ui->comboBox_2->currentIndex()==0)
        Admin->TestList->Current()->kurs=ui->spinBox_5->value();
    else
        Admin->TestList->Current()->kurs=0;
}

void MainWindow::on_action_2_triggered()//автораскида элементов
{

}

void MainWindow::on_pushButton_5_clicked()// вход
{

    flagus=false;// got login
    posend=false;// post request finish
    getend=false;// get request finish


    delete manager;
    manager=new QNetworkAccessManager();


    //post start
    {
        QUrl urlDoLogin("http://sdo.vsu.by/login/index.php");

        QString userName=  ui->lineEdit->text();    //  e-mail
        QString password=   ui->lineEdit_2->text();  //  пароль

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
                 this, SLOT(replyFinishedForPost())
                 );
    }
    // post end

    QTime time;
    time.start();
    bool f=false;
    for(;time.elapsed() < 5000;)
    {
        //  ui->pushButton_14->click();
        //можно (
        qApp->processEvents();
        if(posend)
        {
            f=true;
            break;
        }
    }

    if(!f)
    {
        QMessageBox msgBox;
        msgBox.setText("Соединениe не установлено. Возможно нет доступа к сети");
        msgBox.exec();

        return;
    }
    //get start
    {
        QUrl urlUser("http://sdo.vsu.by/user/profile.php");

        QNetworkRequest request(urlUser);
        request.setRawHeader("Accept-Encoding","identity");

        QNetworkReply* reply= manager->get(request);

        connect( reply, SIGNAL(finished()),
                 this, SLOT(replyFinished())
                 );
    }

    QTime time2;
    time2.start();
    f=false;
    for(;time2.elapsed() < 5000;)
    {
        //  ui->pushButton_14->click();
        //можно (
        qApp->processEvents();
        if(getend)
        {
            f=true;
            break;
        }
    }

    if(!f)
    {
        QMessageBox msgBox;
        msgBox.setText("Соединениe не установлено. Возможно нет доступа к сети");
        msgBox.exec();

        return;
    }


    QTime time3;
    time3.start();
    f=false;
    for(;time3.elapsed() < 5000;)
    {
        //  ui->pushButton_14->click();
        //можно (
        qApp->processEvents();
        if(flagus)
        {
            f=true;
            break;
        }
    }

    if(!f)
    {
        QMessageBox msgBox;
        msgBox.setText("Неверный логин или пароль. ");
        msgBox.exec();

        return;
    }

    // ui->tab->show();
    ui->tabWidget->setCurrentIndex(0);

}

void MainWindow::on_pushButton_pressed()
{

    //ui->pushButton->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #f0eeaa, stop: 1 #eeaa88);");
}

void MainWindow::on_pushButtonNew_clicked()// new test
{
    Admin->AddTest();

}

void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{
    int tmp=Admin->ChangeVopros(ui->listWidget->currentRow());

    ui->label_4->setText(QString::number(ui->listWidget->currentRow()+1));

    ui->frame_7->setMaximumWidth(tmp);
    ui->frame_7->setMinimumWidth(tmp);
}

void MainWindow::on_pushButton_2_clicked()// next
{
    if(ui->listWidget->currentRow()!=ui->listWidget->count()-1)
    {
        int tmp=Admin->ChangeVopros(ui->listWidget->currentRow()+1);
        ui->frame_7->setMaximumWidth(tmp);
        ui->frame_7->setMinimumWidth(tmp);
    }

    ui->label_4->setText(QString::number(ui->listWidget->currentRow()+1));
}

void MainWindow::on_tabWidget_2_currentChanged(int index)// смена теста
{
    Admin->ChangeTest(index);
}

void MainWindow::on_pushButton_6_clicked()// выход
{
    frm->close();
    close();
}

void MainWindow::on_pushButton_7_clicked()//обновить список тестов
{
    Admin->CloseConect();
    Admin->ConectBase();
    ui->comboBox->setEnabled(true);
    ui->textBrowser->setEnabled(true);

    Admin->RetTestList(ui->comboBox);

    if(Admin->TestSavLod->SUBD->GetStatus())//онлайн режми
    {
        if(ui->comboBox->count()==0)
        {
            QMessageBox msgBox;
            msgBox.addButton(QMessageBox::Ok);
            msgBox.addButton(QMessageBox::Cancel);
            msgBox.setText("В текущей базе нет тестов для открытия");
            return;

        }

        //RetKommentTest

    }
    else
    {
        QMessageBox msgBox;
        msgBox.addButton(QMessageBox::Ok);
        msgBox.addButton(QMessageBox::Cancel);
        msgBox.setText("Нет соединения с базой данных.\nПроверьте настройки подключения или\nоткройте тест в в автономном режиме");
        return;
    }
}

void MainWindow::on_pushButton_8_clicked()//вызов настроек базы
{
    frm->close();
    frm->show();
}

void MainWindow::on_pushButton_9_clicked()
{
    Admin->PrevivImage();
}

void MainWindow::on_pushButton_10_clicked()//открыть файл из теста
{
    ui->frame_4->show();
    ui->frame->hide();//пож подожди



    if(Admin->OpenTest())
    {

        ui->label_20->setText("<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">"+Admin->TestList->Current()->GetTestName()+
                              "-ПК"
                              +"</span></p></body></html>");
        ui->textBrowser->setText(Admin->TestList->Current()->GetKomment());
        pc_base=true;

        if(Admin->TestList->Current()->VoprosList->Count()!=0)
            Admin->ChangeVopros(0);

        ui->frame_4->hide();//пож подожди
        ui->frame->show();

    }
    else
    {
        ui->frame_4->hide();//пож подожди
        ui->frame->show();
    }

    ui->frame_4->hide();

    ui->centralWidget->activateWindow();//выносит окно на передний план
}

void MainWindow::on_pushButton_11_clicked()// применить настройки для базы
{
    Admin->SetSUBDSetting(ui->lineEdit_3->text(),//host
                          ui->lineEdit_4->text(),//username
                          ui->lineEdit_5->text(),//pass
                          ui->lineEdit_6->text(),//dbname
                          ui->spinBox->value());//port

    frm->close();
}

void MainWindow::on_checkBox_clicked()
{

}

void MainWindow::on_checkBox_clicked(bool checked)
{
    //    if(!checked)
    //    {
    //        Admin->CloseConect();
    //        ui->checkBox->setStyleSheet("border-image: url(:/icons/C:/Users/electrobas94/Desktop/99_diagona/disconnect.png);");
    //        return;
    //    }
    //    if(!(Admin->ConectBase()))
    //    {
    //        ui->checkBox->setChecked(false);
    //        ui->checkBox->setStyleSheet("border-image: url(:/icons/C:/Users/electrobas94/Desktop/99_diagona/disconnect.png);");
    //    }
    //    else
    //        ui->checkBox->setStyleSheet("border-image: url(:/icons/C:/Users/electrobas94/Desktop/99_diagona/connect.png);");
}

void MainWindow::on_pushButton_12_clicked()
{


}

void MainWindow::on_pushAddVop_clicked()
{
    //Admin->AddVopros(ui->checkBox_copy->isChecked());
}

void MainWindow::on_pushAddOtw_clicked()
{
    Admin->AddOtwet();
}

void MainWindow::on_textBrowser_2_selectionChanged()
{


}

void MainWindow::on_pushButton_13_clicked()
{
    QUrl urlUser("http://sdo.vsu.by/user/profile.php");

    QNetworkRequest request(urlUser);
    request.setRawHeader("Accept-Encoding","identity");

    QNetworkReply* reply= manager->get(request);

    connect( reply, SIGNAL(finished()),
             this, SLOT(replyFinished())
             );
}

void MainWindow::on_pushButton_15_clicked()
{
    if(ui->textBrowser_2->fontUnderline())
        ui->textBrowser_2->setFontUnderline(false);
    else
        ui->textBrowser_2->setFontUnderline(true);
    ui->textBrowser_2->setFocus();
}

void MainWindow::on_pushButton_14_clicked()
{
    if(ui->textBrowser_2->fontItalic())
        ui->textBrowser_2->setFontItalic(false);
    else
        ui->textBrowser_2->setFontItalic(true);

    ui->textBrowser_2->setFocus();
}

void MainWindow::on_pushButton_16_clicked()
{
    if(ui->textBrowser_2->alignment()==Qt::AlignLeft)
        ui->textBrowser_2->setAlignment(Qt::AlignAbsolute);
    else
        ui->textBrowser_2->setAlignment(Qt::AlignLeft);

    ui->textBrowser_2->setFocus();
}

void MainWindow::on_pushButton_18_clicked()
{
    if(ui->textBrowser_2->alignment()==Qt::AlignRight)
        ui->textBrowser_2->setAlignment(Qt::AlignAbsolute);
    else
        ui->textBrowser_2->setAlignment(Qt::AlignRight);
    ui->textBrowser_2->setFocus();
}

void MainWindow::on_pushButton_17_clicked()
{
    if(ui->textBrowser_2->alignment()==Qt::AlignHCenter)
        ui->textBrowser_2->setAlignment(Qt::AlignAbsolute);
    else
        ui->textBrowser_2->setAlignment(Qt::AlignHCenter);

    ui->textBrowser_2->setFocus();
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    ui->textBrowser_2->setFontPointSize(arg1);
    ui->textBrowser_2->setFocus();
}

void MainWindow::on_pushButton_19_clicked()
{
    QColor col = QColorDialog::getColor(ui->textBrowser_2->textColor(), this);
    if (!col.isValid())
        return;
    QTextCharFormat fmt;
    fmt.setForeground(col);

    QTextCursor cursor = ui->textBrowser_2->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(fmt);
    ui->textBrowser_2->mergeCurrentCharFormat(fmt);
    //ui->pushButton_9->setStyleSheet();
    ui->textBrowser_2->setFocus();
}

void MainWindow::on_fontComboBox_currentFontChanged(const QFont &f)
{
    QTextCharFormat fmt;
    fmt.setFont(f);

    QTextCursor cursor = ui->textBrowser_2->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(fmt);
    ui->textBrowser_2->mergeCurrentCharFormat(fmt);

    ui->textBrowser_2->setFocus();
}

void MainWindow::on_pushButton_21_clicked()
{
    //    QMessageBox::StandardButton reply;
    //    reply = QMessageBox::question(this, "Test", "Quit?",
    //                                  QMessageBox::Yes|QMessageBox::No);
    //    if (reply == QMessageBox::Yes) {
    //        qDebug() << "Yes was clicked";
    //        QApplication::quit();
    //    } else {
    //        qDebug() << "Yes was *not* clicked";
    //    }

    QObject::connect(ui->textBrowser_2, SIGNAL(clicked()), this, SLOT(MyEventHandler()));
}

void MainWindow::on_buttonBox_accepted()
{

}

void MainWindow::on_pushButton_25_clicked()
{
    //    if(ui->tabWidget_2->count()==0)
    //        return;

    //    QVBoxLayout *laut=new QVBoxLayout();
    //    laut->addWidget(ui->frame_ts);
    //    QFrame *frm=new QFrame();
    //    frm->setLayout(laut);
    //    frm->show();
    //    ui->lineEdit_5->setText(Admin->TestList->Current()->GetTestName());
    //    ui->textEdit->setText(Admin->TestList->Current()->GetKomment());
    //    Admin->TestList->Current()->GetCalcAttribute(ui->checkBox_2,
    //                                                 ui->checkBox_3,
    //                                                 ui->radioButton,
    //                                                 ui->radioButton_2,
    //                                                 ui->radioButton_3);
}

void MainWindow::on_pushButton_23_clicked()
{
    //    if(ui->lineEdit_5->text()=="")
    //    {
    //        QMessageBox msgBox;
    //        msgBox.addButton(QMessageBox::Ok);
    //        msgBox.addButton(QMessageBox::Cancel);
    //        msgBox.setText("Имя не должно быть пустым");
    //        return;
    //    }

    //    Admin->TestList->Current()->SetKomment(ui->textEdit->toPlainText());
    //    Admin->TestList->Current()->SetTestName(ui->lineEdit_5->text());
    //    Admin->TestList->Current()->CalcAttribute(ui->checkBox_2->isChecked(),
    //                                              ui->checkBox_3->isChecked(),
    //                                              ui->radioButton_2->isChecked(),
    //                                              ui->radioButton_3->isChecked());

    //    ui->tabWidget_2->setTabText(ui->tabWidget_2->currentIndex(),
    //                                " "+ui->lineEdit_5->text());
}

void MainWindow::on_pushRemVop_clicked()
{
    Admin->DeleteVopros();
}

void MainWindow::on_listWidget_itemSelectionChanged()
{

}

void MainWindow::on_pushRemOtw_clicked()
{
    Admin->DeleteOtwet();
}

void MainWindow::on_tabWidget_2_tabCloseRequested(int index)
{
    Admin->DeleteTest(index);
}

void MainWindow::on_pushButton_26_clicked()
{
    //    if(!(Admin->TestSavLod->SUBD->GetStatus()))
    //        return;

    //    QVBoxLayout *laut=new QVBoxLayout();
    //    laut->addWidget(ui->frame_15);
    //    QFrame *frm=new QFrame();
    //    frm->setLayout(laut);

    //    Admin->RetTestList(ui->listWidget_2);
    //    frm->show();
}

void MainWindow::on_pushButton_27_clicked()// удалить тест из базы
{
    //    if(ui->listWidget_2->count()==0)
    //        return;

    //    Admin->DelTestTable(ui->listWidget_2->currentRow());// удаление теста из базы
    //    Admin->RetTestList(ui->listWidget_2);// обновление списка
}

void MainWindow::on_pushButton_28_clicked()// спин боксы целые
{
    Admin->SetTypeOtwet(2);
}

void MainWindow::on_pushButton_29_clicked()// спин боксы дробные
{
    Admin->SetTypeOtwet(3);
}

void MainWindow::on_pushButton_30_clicked()// однострочные лайны
{
    Admin->SetTypeOtwet(4);
}

void MainWindow::on_pushButton_31_clicked()// мноострочные лайны
{
    Admin->SetTypeOtwet(5);
}

void MainWindow::on_pushButton_32_clicked()
{
    QPixmap pixmap;
    QByteArray bArray;
    QBuffer buffer( &bArray );
    buffer.open( QIODevice::WriteOnly );
    pixmap.save( &buffer, "PNG" );

    QString b(bArray.data());
    //b= QString::append (  QByteArray & bArray );
}

void MainWindow::on_pushButton_34_clicked()//Down vopros
{
    Admin->ChangePosVopros(ui->listWidget->currentRow()+1);
}

void MainWindow::on_pushButton_33_clicked()
{
    Admin->ChangePosVopros(ui->listWidget->currentRow()-1);// up вопрос
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
//    if(ui->comboBox->count()==0)
//        return;

//    ui->textBrowser->setText(Admin->RetKommentTest(index));



}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{

}

void MainWindow::on_centralWidget_destroyed()
{
    frm->close();
}

void MainWindow::on_pushButton_35_clicked()
{
    frm->close();
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    if(index==0)
        ui->spinBox_5->setEnabled(true);
    else
        ui->spinBox_5->setEnabled(false);
}


void MainWindow::replyFinished()
{


    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (reply->error() == QNetworkReply::NoError)
    {
        getend=true;
        QByteArray content= reply->readAll();
        QTextCodec *codec = QTextCodec::codecForName("utf-8");
        QString tmp=codec->toUnicode(content.data()) ;

        //ui->textBrowser->setHtml(tmp);

        QString vv ="class=\"userprofile\"><h2>";
        int beg=tmp.indexOf(vv);
        beg+=24;
        int endd=tmp.indexOf("</h2><div class=\"userprofilebox");

        if(beg==-1 || endd==-1)
            return;
        vv=tmp.mid(beg, endd-beg);
        int tmo=vv.indexOf(' ');
        ui->lineEdit_7->setText(vv.left(tmo));
        ui->lineEdit_8->setText(vv.right(vv.count()-tmo-1));
        ui->lineEdit_9->setText(ui->lineEdit->text());


        //ui->lineEdit_3->setText(vv);

        vv="&nbsp; (";
        beg=tmp.indexOf(vv);
        beg+=8;
        endd=tmp.indexOf(" дн.");

        //        if(beg==-1 || endd==-1)
        //            return;

        vv=tmp.mid(beg, endd-beg);

        int sss=vv.toInt()/365+1;



        if(sss<6)
        {
            ui->spinBox_5->setValue( sss);// курс
            ui->comboBox_2->setCurrentIndex(0);
        }
        else
        {
            ui->spinBox_5->setValue( 1);// курс
            ui->comboBox_2->setCurrentIndex(1);
        }

        flagus=true;
    }
    else qDebug()<<reply->errorString();

    reply->deleteLater();
}

void MainWindow::replyFinishedForPost()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (reply->error() == QNetworkReply::NoError)
    {
        posend=true;
    }
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{

}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->label_20->setText("<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">"+arg1+"</span></p></body></html>");
}

void MainWindow::on_comboBox_activated(int index)
{
    pc_base=false;
    if(ui->comboBox->count()==0)
        return;

    ui->label_20->setText("<p><span style=\" font-size:14pt; font-weight:600;\">"+ui->comboBox->currentText()+"</span></p>");
    ui->textBrowser->setText(Admin->RetKommentTest(index));
}
