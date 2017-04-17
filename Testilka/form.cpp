#include "form.h"
#include "ui_form.h"
#include "myfiles.h"
#include <QFileDialog>
#include <QDesktopWidget>
#include <QDate>
#include "grafikzdraw.h"


#include "myprintrezult.h" // вывод данных по вопросу
MyTest *testCur;
GrafikzDraw  *formGraf;
MyAdmin *admin;
Form::Form(MyTest *test, MyAdmin *Admin, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    ui->frame_2->hide();

    admin=Admin;

    formGraf=new GrafikzDraw(test);

    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());

    ui->label->setText("<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">Результаты теста: "
                       +test->GetTestName()+"</span></p></body></html>");
    testCur=test;
    int sum=0;
    test->VoprosList->First();

    for(int i=0;i<test->VoprosList->Count();i++)
    {
        test->VoprosList->Current()->OtwetList->First();
        for(int j=0;j<test->VoprosList->Current()->OtwetList->Count();j++)
        {
            if(test->VoprosList->Current()->OtwetList->Current()->GetChek())
                sum+=test->VoprosList->Current()->OtwetList->Current()->GetMark();
            test->VoprosList->Current()->OtwetList->Next();
        }
        test->VoprosList->Next();
    }
//    ui->label_2->setText("<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">Сумма: "+
//                         QString::number(sum)+
//                         "</span></p></body></html>");
//    double a=sum;
//    a/=test->VoprosList->Count();
//    ui->label_3->setText("<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">Средний бал: "
//                         +QString::number(a)+
//                         "</span></p></body></html>");

    test->sum=sum;
    PrintInfo(test, ui->verticalLayout_4);
}

Form::~Form()
{
    formGraf->close();
    delete ui;
}

void Form::on_pushButton_clicked()
{
    close();
}

void Form::on_pushButton_3_clicked()
{
    ui->frame_2->show();
    qApp->processEvents();
    admin->TestSavLod->SaveInBDRezult(testCur);
    ui->frame_2->hide();
}

void Form::on_pushButton_2_clicked()
{
    ui->frame_2->show();
    try {// что бы прога не падала если экстренно закрываеть диалог
        QString str = QFileDialog::getSaveFileName(0, "Сохранить результат",
                                                   "", "Файлы ответов теста (*.REZL)");// ввод названия теста

        if(str=="")
            return;

        MyFiles mfile;
        mfile.SetFileName(str);
        mfile.NewFile();

        mfile.Append(testCur->TestName);
        mfile.Append(testCur->FIO[0]);
        mfile.Append(testCur->FIO[1]);
        mfile.Append(testCur->FIO[2]);
        mfile.Append(testCur->kurs);

        mfile.Append(QDate::currentDate().toString("dd/MM/yyyy"));

        qint32 tmppp=testCur->rezult->Count();
        mfile.Append(tmppp);

        testCur->rezult->First();
        for(int i=0;i<testCur->rezult->Count();i++)
        {
            mfile.Append(testCur->rezult->Current()->head);
            mfile.Append(testCur->rezult->Current()->info);
           mfile.Append( testCur->rezult->Current()->sum);
           mfile.Append(testCur->rezult->Current()->attrib);

            testCur->rezult->Next();
        }

        mfile.CloseFile();
    } catch (...){}// если было закрыто или зависло

    ui->frame_2->hide();
}

void Form::on_pushButton_4_clicked()
{
    formGraf->showFullScreen();
    formGraf->on_pushButton_2_clicked();
}
