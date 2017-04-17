
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myadmin.h"
#include <QThread>
#include <QSql>
#include <QtSql>
#include <form.h>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QImage>

MyAdmin *Admin=new MyAdmin();//все через интерфейс данного класса
QFrame *openTestF;
QFrame *delTestF;
QFrame *baseSetF;
QFrame *TestPropF;
Form *form2;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());



    QVBoxLayout *laut1=new QVBoxLayout();
    laut1->addWidget(ui->frame_ts);
    TestPropF=new QFrame();
    TestPropF->setLayout(laut1);

    QVBoxLayout *laut2=new QVBoxLayout();
    laut2->addWidget(ui->frame_15);
    delTestF=new QFrame();
    delTestF->setLayout(laut2);

    QVBoxLayout *laut3=new QVBoxLayout();
    laut3->addWidget(ui->frame_9);
    baseSetF=new QFrame();
    baseSetF->setLayout(laut3);

    QVBoxLayout *laut4=new QVBoxLayout();
    laut4->addWidget(ui->frame_6);
    openTestF=new QFrame();
    openTestF->setLayout(laut4);

    ui->tabWidget->removeTab(2);
    ui->frame_10->layout()->setMargin(0);
    ui->frame_10->setStyleSheet("background-color: #f0f0f0;");
    Admin->SetTabWidget(ui->tabWidget_2);//список тестов
    Admin->SetTabWidget(ui->listWidget);//список вопросов
    Admin->SetTextVopros(ui->textBrowser_2);//текст текущего вопроса
    Admin->SetImageLabel(ui->label_2);// для отображения картинки
    Admin->SetOtweti(ui->verticalLayout_4);
    Admin->SetSUBDSetting(ui->lineEdit->text(),//host
                          ui->lineEdit_2->text(),//username
                          ui->lineEdit_3->text(),//pass
                          ui->lineEdit_4->text(),//dbname
                          ui->spinBox->value());//port

    ui->statusBar->addWidget(ui->label_13);
    ui->statusBar->addWidget(ui->progressBar);
    ui->label_13->hide();
    ui->progressBar->hide();
    Admin->SetBar(ui->progressBar);


}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()// сохранить тест
{
    if(Admin->TestList->Count()==0)
        return;
    ui->label_13->show();
    ui->label_13->setText("Идет сохранение ");
    ui->progressBar->show();
    ui->progressBar->setValue(0);

    Admin->SaveTest();
    ui->centralWidget->activateWindow();//выносит окно на передний план

    ui->label_13->hide();
    ui->progressBar->hide();
}

void MainWindow::on_pushButton_3_clicked()// шифр
{
    ui->textBrowser_2->cut();
    ui->textBrowser_2->setFocus();
}

void MainWindow::on_pushButton_4_clicked()
{
    Admin->SetTypeOtwet(1);
}

void MainWindow::on_action_2_triggered()//автораскида элементов
{

}

void MainWindow::on_pushButton_5_clicked()// добавить вопрос
{
    Admin->SetTypeOtwet(0);
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
    int a=Admin->ChangeVopros(ui->listWidget->currentRow());
    ui->frame_7->setMaximumWidth(a);
    ui->frame_7->setMinimumWidth(a);
}

void MainWindow::on_pushButton_2_clicked()//add var otwet
{
    ui->textBrowser_2->paste();
    ui->textBrowser_2->setFocus();
}

void MainWindow::on_tabWidget_2_currentChanged(int index)// смена теста
{
    Admin->ChangeTest(index);
}

void MainWindow::on_pushButton_6_clicked()// открыть тест
{
    if(Admin->TestSavLod->SUBD->GetStatus())//онлайн режми
    {
        Admin->GetListTest(ui->comboBox,ui->comboBox_2);
        if(ui->comboBox_2->count()==0)
        {
            QMessageBox msgBox;
            msgBox.addButton(QMessageBox::Ok);
            msgBox.addButton(QMessageBox::Cancel);
            msgBox.setText("В текущей базе нет тестов для открытия");
            return;

        }

        openTestF->close();
        openTestF->show();

    }
    else//offline
    {
        ui->label_13->show();
        ui->label_13->setText("Идет открытие ");
        ui->progressBar->show();
        ui->progressBar->setValue(0);

        Admin->OpenTest();

        ui->centralWidget->activateWindow();//выносит окно на передний план

        ui->label_13->hide();
        ui->progressBar->hide();
    }
}

void MainWindow::on_pushButton_7_clicked()//авТОЗАГРУЗКА
{
    ui->label_13->show();
    ui->label_13->setText("Идет открытие ");
    ui->progressBar->show();
    ui->progressBar->setValue(0);

    Admin->OpenTestBD(ui->comboBox_2->itemText(ui->comboBox->currentIndex()));
    openTestF->close();

    ui->label_13->hide();
    ui->progressBar->hide();


}

void MainWindow::on_pushButton_8_clicked()//открыть изображение
{
    int tmp = Admin->LoadImage();

    ui->frame_7->setMaximumWidth(tmp);
    ui->frame_7->setMinimumWidth(tmp);
    ui->centralWidget->activateWindow();//выносит окно на передний план
}

void MainWindow::on_pushButton_9_clicked()
{
    Admin->PrevivImage();
}

void MainWindow::on_pushButton_10_clicked()//окно настроек базы
{
    Admin->SetSUBDSetting(ui->lineEdit->text(),//host
                          ui->lineEdit_2->text(),//username
                          ui->lineEdit_3->text(),//pass
                          ui->lineEdit_4->text(),//dbname
                          ui->spinBox->value());//port

    baseSetF->close();
}

void MainWindow::on_pushButton_11_clicked()
{
    baseSetF->close();
    baseSetF->show();

    QRect frect = baseSetF->frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    baseSetF->move(frect.topLeft());

}

void MainWindow::on_checkBox_clicked()
{

}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if(!checked)
    {
        Admin->CloseConect();
        ui->checkBox->setStyleSheet("image: url(:/icons/99_diagona/disconnect.png);");
        return;
    }
    if(!(Admin->ConectBase()))
    {
        ui->checkBox->setChecked(false);
        ui->checkBox->setStyleSheet("image: url(:/icons/99_diagona/disconnect.png);");
    }
    else
        ui->checkBox->setStyleSheet("image: url(:/icons/99_diagona/connect.png);");
}

void MainWindow::on_pushButton_12_clicked()
{
    ui->textBrowser_2->copy();
    ui->textBrowser_2->setFocus();
}

void MainWindow::on_pushAddVop_clicked()
{
    Admin->AddVopros(ui->checkBox_copy->isChecked());
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

    QTextCharFormat fmt;
    fmt.setFontWeight(ui->textBrowser_2->fontWeight()!=QFont::Bold ? QFont::Bold : QFont::Normal);

    QTextCursor cursor = ui->textBrowser_2->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(fmt);
    ui->textBrowser_2->mergeCurrentCharFormat(fmt);
    ui->textBrowser_2->setFocus();
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
    //fmt.setBackground(col);

    QTextCursor cursor = ui->textBrowser_2->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(fmt);
    ui->textBrowser_2->mergeCurrentCharFormat(fmt);
    //    ui->pushButton_19->setStyleSheet("background-color: rgb("+
    //                                     QString::number( col.red() )+
    //                                     QString::number( col.green() )+
    //                                     QString::number( col.blue() )+
    //                                     ");");
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
    QDesktopServices::openUrl(QUrl("http://google.com", QUrl::TolerantMode));

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
    if(ui->tabWidget_2->count()==0)
        return;

    ui->lineEdit_5->setText(Admin->TestList->Current()->GetTestName());
    ui->textEdit->setText(Admin->TestList->Current()->GetKomment());
    Admin->TestList->Current()->GetCalcAttribute(ui->checkBox_2,
                                                 ui->checkBox_3,
                                                 ui->radioButton,
                                                 ui->radioButton_2,
                                                 ui->radioButton_3);

    if(Admin->TestList->Current()->attrib2%10==1 )
        ui->checkBox_5->setChecked(true);
    else
        ui->checkBox_5->setChecked(false);

    if(Admin->TestList->Current()->attrib2>=10 )
        ui->checkBox_4->setChecked(true);
    else
        ui->checkBox_4->setChecked(false);

    QTime time(  Admin->TestList->Current()->timeTest.h,Admin->TestList->Current()->timeTest.m, Admin->TestList->Current()->timeTest.s);
    ui->timeEdit->setTime(time);

    TestPropF->close();
    TestPropF->show();

    QRect frect = TestPropF->frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    TestPropF->move(frect.topLeft());

}

void MainWindow::on_pushButton_23_clicked()
{
    if(ui->lineEdit_5->text()=="")
    {
        QMessageBox msgBox;
        msgBox.addButton(QMessageBox::Ok);
        msgBox.addButton(QMessageBox::Cancel);
        msgBox.setText("Имя не должно быть пустым");
        return;
    }

    if(ui->checkBox_5->isChecked())// image no/yes
        Admin->TestList->Current()->attrib2=1;
    else
        Admin->TestList->Current()->attrib2=0;

    if(ui->checkBox_4->isChecked())// time for test yes and no
        Admin->TestList->Current()->attrib2+=10;

    QString str;
    str=ui->timeEdit->time().toString();
    QStringList tmp=str.split(':');

    int i=0;
    foreach (QString a, tmp)
    {
        int tmp2=a.toInt();
        if(i==1)
            Admin->TestList->Current()->timeTest.m=tmp2;
        if(i==2)
            Admin->TestList->Current()->timeTest.s=tmp2;
        if(i==0)
            Admin->TestList->Current()->timeTest.h=tmp2;
        i++;
    }

    Admin->TestList->Current()->SetKomment(ui->textEdit->toPlainText());
    Admin->TestList->Current()->SetTestName(ui->lineEdit_5->text());
    Admin->TestList->Current()->CalcAttribute(ui->checkBox_2->isChecked(),
                                              ui->checkBox_3->isChecked(),
                                              ui->radioButton_2->isChecked(),
                                              ui->radioButton_3->isChecked());

    ui->tabWidget_2->setTabText(ui->tabWidget_2->currentIndex(),
                                " "+ui->lineEdit_5->text());

    TestPropF->close();
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
    if(!(Admin->TestSavLod->SUBD->GetStatus()))
        return;

    Admin->RetTestList(ui->listWidget_2);

    delTestF->close();
    delTestF->show();

    QRect frect = delTestF->frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    delTestF->move(frect.topLeft());

}

void MainWindow::on_pushButton_27_clicked()// удалить тест из базы
{
    if(ui->listWidget_2->count()==0)
        return;

    Admin->DelTestTable(ui->listWidget_2->currentRow());// удаление теста из базы
    Admin->RetTestList(ui->listWidget_2);// обновление списка
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
    if(Admin->TestList->Count()==0)
        return;
    delete form2;
    form2=new Form(Admin->TestList->Current()->VoprosList->Count(), Admin->TestList->Current());
    form2->hide();
    form2->show();
}

void MainWindow::on_pushButton_34_clicked()//Down vopros
{
    Admin->ChangePosVopros(ui->listWidget->currentRow()+1);
}

void MainWindow::on_pushButton_33_clicked()
{
    Admin->ChangePosVopros(ui->listWidget->currentRow()-1);// up вопрос
}

void MainWindow::on_centralWidget_destroyed()
{
    TestPropF->close();
    openTestF->close();
    delTestF->close();
    baseSetF->close();
    form2->close();
}

void MainWindow::on_frame_3_destroyed()
{
}

void MainWindow::on_pushButton_35_clicked()
{
    baseSetF->close();
}

void MainWindow::on_pushButton_22_clicked()
{
    openTestF->close();
}

void MainWindow::on_pushButton_24_clicked()
{
    TestPropF->close();
}

void MainWindow::on_centralWidget_destroyed(QObject *arg1)
{

}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{

}

void MainWindow::on_pushButton_20_clicked()
{
    QColor col = QColorDialog::getColor(ui->textBrowser_2->textColor(), this);
    if (!col.isValid())
        return;
    QTextCharFormat fmt;
    //fmt.setForeground(col);
    fmt.setBackground(col);

    QTextCursor cursor = ui->textBrowser_2->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(fmt);
    ui->textBrowser_2->mergeCurrentCharFormat(fmt);

    ui->textBrowser_2->setFocus();
}

void MainWindow::on_pushButton_36_clicked()
{
    ui->textBrowser_2->setText(ui->textBrowser_2->toPlainText());
}

void MainWindow::on_pushButton_37_clicked()// clear image of question
{
    if( Admin->TestList->Count()>0 )
        if(Admin->TestList->Current()->VoprosList->Count()>0)
        {
            QImage image;
            ui->frame_7->setMaximumWidth(150);
            ui->frame_7->setMinimumWidth(150);
            ui->label_2->clear();
            Admin->TestList->Current()->VoprosList->Current()->SetImage(image);
        }
}
