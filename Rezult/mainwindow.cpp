#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QFileDialog>
#include "myprintrezult.h"
#include "myfiles.h"
#include "mylistlink.h"
#include "mysubd.h"
#include <QMessageBox>
#include "grafikzdraw.h"

struct RezElem
{
    QString surname;
    QString testname;
    int  date[3];
    quint8 kurs;

    bool bd;
    QString adress;
    int numer;
};

MySUBD *base;
MyListLink<MyPrintRezult> *listres;
MyListLink<RezElem> *mainlist;
MyListLink<RezElem> *mainlist2;
MyListLink<RezElem> *mainlist3;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    base=new MySUBD();

    ui->frame_9->hide();

    ui->dateEdit->setDate(QDate::currentDate());

    base->SetHost(ui->lineEdit_7->text());
    base->SetUser(ui->lineEdit_8->text());
    base->SetPass(ui->lineEdit_9->text());
    base->SetBaseName(ui->lineEdit_10->text());
    base->SetPortNumer(ui->spinBox_3->value());

    listres=new MyListLink<MyPrintRezult> (LINK_MODE);
    mainlist=new MyListLink<RezElem>(LINK_MODE);

    mainlist2=new MyListLink<RezElem>(LINK_MODE);
    mainlist3=new MyListLink<RezElem>(LINK_MODE);


    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());

    if(base->OpenConect())
        ui->pushButton_6->click();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_4_clicked()
{
    try {// что бы прога не падала если экстренно закрываеть диалог
        QStringList strL = QFileDialog::getOpenFileNames(0, "Открыть файлы результатов",
                                                         "", "Файлы ответов теста (*.REZL)");// ввод названия теста//  "", "Файлы ответов теста (*.REZL)");// ввод названия теста

        if(strL.count()==0)
            return;

        foreach (QString str, strL)
        {
            RezElem *elem=new RezElem();
            elem->adress=str;

            MyFiles mfile;
            mfile.SetFileName(str);
            mfile.OpenFile();
            //////////////////////

            mainlist->First();
            for(int i=0;i<mainlist->Count();i++){
                if(mainlist->Current()->adress==str)
                    goto mycontinue;
                mainlist->Next();
            }

            if(2>3)
            {
mycontinue:;
                continue;
            }
            qint32 countP=0;//колличество правил
            quint8 kurs=0;qint32 sum;
            QString a;

            mfile.ReadDataBlock(a);// test name
            elem->testname=a;

            elem->bd=false;// локально

            mfile.ReadDataBlock(a);// surname
            ui->lineEdit_2->setText(a);
            elem->surname=a;

            mfile.ReadDataBlock(a);//name
            mfile.ReadDataBlock(a);//

            mfile.ReadDataBlock(kurs);
            elem->kurs=kurs;

            mfile.ReadDataBlock(a);// date
            ui->lineEdit_6->setText(a);
            QStringList b=a.split('/');

            int i=0;
            foreach (QString z, b) {
                elem->date[i]=z.toUInt();
                i++;
            }

            ///////////////////////////////
            mfile.CloseFile();

            mainlist->Add(elem);
            ui->listWidget->addItem("ПК-"+elem->surname+"-"+QString::number(elem->kurs)+"k-"+a+"-"+elem->testname);

        }

    } catch (...){}// если было закрыто или зависло

}

void MainWindow::on_pushButton_9_clicked()
{
    if (QMessageBox::Yes == QMessageBox(QMessageBox::Information,
                                        "Экспорт файла в БД",
                                        "Выгрузить файл в базу данных?",
                                        QMessageBox::Yes|QMessageBox::No).exec())
    {
        QStringList tmp;
        QString tablename;

        if(!(base->RetTablesRezult(&tmp)))//получаем список таблиц
            return ;

        if(tmp.count()==0)
            tablename="r1";
        else{


            tablename=tmp.last();
            tablename.remove(0,1);
            tablename="r"+QString::number(tablename.toInt()+1);
        }

        base->CreteTableTest(tablename);

        MyFiles mfile;
        mfile.SetFileName(mainlist->Current()->adress);
        mfile.OpenFile();
        //////////////////////

        qint32 countP=0;//колличество правил
        quint8 kurs=0;qint32 sum;
        QString a;

        mfile.ReadDataBlock(a);
        base->ApendDataInTest(tablename, a); // test name

        mfile.ReadDataBlock(a);// FIO
        base->ApendDataInTest(tablename, a);

        mfile.ReadDataBlock(a);
        base->ApendDataInTest(tablename, a);

        mfile.ReadDataBlock(a);
        base->ApendDataInTest(tablename, a);

        //kurs
        mfile.ReadDataBlock(kurs);
        base->ApendDataInTest(tablename, QString::number(kurs));

        mfile.ReadDataBlock(a);// date
        base->ApendDataInTest(tablename,  a);

        mfile.ReadDataBlock(countP);
        base->ApendDataInTest(tablename, QString::number(countP));

        for(int i=0;i<countP;i++)
        {
            mfile.ReadDataBlock(a);
            base->ApendDataInTest(tablename, a);
            mfile.ReadDataBlock(a);
            base->ApendDataInTest(tablename, a);

            mfile.ReadDataBlock(kurs);
            base->ApendDataInTest(tablename, QString::number(kurs));

            quint16 aaa;
            mfile.ReadDataBlock(aaa);
            base->ApendDataInTest(tablename, QString::number(aaa));
        }


        ///////////////////////////////
        mfile.CloseFile();

        ui->pushButton_6->click();
    }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{

}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    //if(!(ui->listWidget->selectedItems().isEmpty())){
    int j=listres->Count();
    for(int i=0; i<j;i++)
    {
        listres->Last()->Widget()->deleteLater();
        listres->DeleteLastElem();
    }

    ActivFRow(currentRow);
}
//}

void MainWindow::on_pushButton_7_clicked()
{
    if(ui->frame_9->isHidden())
        ui->frame_9->show();
    else
        ui->frame_9->hide();
}

void MainWindow::on_pushButton_10_clicked()
{
    base->CloseConect();

    base->SetHost(ui->lineEdit_7->text());
    base->SetUser(ui->lineEdit_8->text());
    base->SetPass(ui->lineEdit_9->text());
    base->SetBaseName(ui->lineEdit_10->text());
    base->SetPortNumer(ui->spinBox_3->value());

    if(!(base->OpenConect()))
        QMessageBox::information(this, "Внимание", "Соединение с базой не установлено");
    ui->pushButton_6->click();
}

void MainWindow::on_pushButton_6_clicked()
{


    ui->comboBox->clear();
    ui->comboBox->addItem("");
    ui->listWidget_2->clear();
    mainlist2->Clear();


    QStringList tmp;
    if(!(base->RetTablesTest(&tmp)))//получаем список таблиц
        return;

    foreach (QString tablename, tmp)
    {
        ui->comboBox->addItem(base->RetFirstItem(tablename,1));// тест с таким именем уже существует
    }

    QStringList tmp1;// list table rezult
    if(!(base->RetTablesRezult(&tmp1)))//получаем список таблиц
        return;

    foreach (QString str, tmp1)
    {
        RezElem *elem=new RezElem();
        elem->adress=str;

        qint32 countP=0;//колличество правил
        quint8 kurs=0;qint32 sum;
        QString a;

        int number=1;


        elem->bd=true;// локально
        elem->testname=base->RetFirstItem(str,number);
        number++;

        elem->surname=base->RetFirstItem(str,number);
        number++;

        number+=2;

        elem->kurs=base->RetFirstItem(str,number).toInt();
        number++;

        QString a1=base->RetFirstItem(str,number);
        number++;
        QStringList b=a1.split('/');

        int i=0;
        foreach (QString z, b) {
            elem->date[i]=z.toInt();
            i++;
        }



        mainlist2->Add(elem);
        ui->listWidget_2->addItem("БД-"+elem->surname+"-"+QString::number(elem->kurs)+"k-"+a1+"-"+elem->testname);

        qApp->processEvents();

        //хламина потом дорассмотреть
        ui->spinBox->setValue(1);
        ui->label_2->setText("<p><span style=\" font-size:14pt; font-weight:600;\">Тест: &lt;---------------------&gt;</span></p>");
        ui->lineEdit->setText("");
        ui->lineEdit_2->setText("");
        ui->lineEdit_3->setText("");
        ui->lineEdit_6->setText("");
    }
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{

}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    //ui->lineEdit_5->setText(arg1);
}

void MainWindow::ActivFRow(int currentRow)
{
    if(ui->listWidget->count()==0)
        return;

    mainlist->SetCurrentToIndex(currentRow);

    MyFiles mfile;
    mfile.SetFileName(mainlist->Current()->adress);
    mfile.OpenFile();
    //////////////////////

    qint32 countP=0;//колличество правил
    quint8 kurs=0;qint32 sum;
    QString a;

    mfile.ReadDataBlock(a);
    ui->label_2->setText("<html><head/><body><p><span style=\" font-size:14pt; font-weight:600;\">Тест: "+a+"</span></p></body></html>");

    mfile.ReadDataBlock(a);
    ui->lineEdit_2->setText(a);

    mfile.ReadDataBlock(a);
    ui->lineEdit->setText(a);

    mfile.ReadDataBlock(a);
    ui->lineEdit_3->setText(a);

    mfile.ReadDataBlock(kurs);
    if(kurs!=0)
    {
        ui->label_6->setText(" Студент ");
        ui->spinBox->setValue(kurs);
        ui->spinBox->show();
        ui->label_7->show();
    }
    else
    {
        ui->label_6->setText(" Преподователь  ");
        //ui->spinBox->setValue(kurs);
        ui->spinBox->hide();
        ui->label_7->hide();
    }

    mfile.ReadDataBlock(a);
    ui->lineEdit_6->setText(a);


    mfile.ReadDataBlock(countP);

    for( int i=0; i<countP; i++)
    {
        //MyPrintRezult *rezultt=new MyPrintRezult();
        QString head,text; quint8 summa; quint16 attrib;

        mfile.ReadDataBlock(head);
        //        rezultt->SetHead(head);
        mfile.ReadDataBlock(text);
        //        rezultt->SetText(text);
        mfile.ReadDataBlock(summa);
        //        rezultt->SetPoint(summa);

        mfile.ReadDataBlock(attrib);
        //rezultt->attrib=attrib;

        MyPrintRezult *rezultt=new MyPrintRezult(attrib);
        rezultt->SetHead(head);
        rezultt->SetText(text);
        rezultt->SetPoint(summa);

        listres->Add(rezultt);
        //listres->Add(rezultt);
        ui->verticalLayout_6->addWidget(rezultt->Widget());
    }


    ///////////////////////////////
    mfile.CloseFile();
}

void MainWindow::ActivBdRow(int currentRow)
{
    mainlist2->SetCurrentToIndex(currentRow);


    qint32 countP=0;//колличество правил
    quint8 kurs=0;qint32 sum;
    QString a;

    int numer=1;
    ui->label_2->setText("<html><head/><body><p><span style=\" font-size:14pt; font-weight:600;\">Тест: "+
                         base->RetFirstItem(mainlist2->Current()->adress,numer)
                         +"</span></p></body></html>");

    numer++;
    ui->lineEdit_2->setText(base->RetFirstItem(mainlist2->Current()->adress,numer));
    numer++;

    ui->lineEdit->setText(base->RetFirstItem(mainlist2->Current()->adress,numer));
    numer++;

    ui->lineEdit_3->setText(base->RetFirstItem(mainlist2->Current()->adress,numer));
    numer++;

    kurs=base->RetFirstItem(mainlist2->Current()->adress,numer).toInt();
    numer++;

    if(kurs!=0)
    {
        ui->label_6->setText(" Студент ");
        ui->spinBox->setValue(kurs);
        ui->spinBox->show();
        ui->label_7->show();
    }
    else
    {
        ui->label_6->setText(" Преподователь  ");
        //ui->spinBox->setValue(kurs);
        ui->spinBox->hide();
        ui->label_7->hide();
    }

    ui->lineEdit_6->setText(base->RetFirstItem(mainlist2->Current()->adress,numer));
    numer++;


    countP=base->RetFirstItem(mainlist2->Current()->adress,numer).toInt();
    numer++;

    for( int i=0; i<countP; i++)
    {
        //MyPrintRezult *rezultt=new MyPrintRezult();
        QString head,text; int sum, attrib;

        head = base->RetFirstItem(mainlist2->Current()->adress,numer);
        numer++;

        text = base->RetFirstItem(mainlist2->Current()->adress,numer);
        numer++;

        sum = base->RetFirstItem(mainlist2->Current()->adress,numer).toInt();
        numer++;

        attrib=base->RetFirstItem(mainlist2->Current()->adress,numer).toInt();
        numer++;


        MyPrintRezult *rezultt=new MyPrintRezult(attrib);
        rezultt->SetHead(head);
        rezultt->SetText(text);
        rezultt->SetPoint(sum);
        listres->Add(rezultt);
        //listres->Add(rezultt);
        ui->verticalLayout_6->addWidget(rezultt->Widget());
    }

}

void MainWindow::on_listWidget_2_currentRowChanged(int currentRow)
{
    //if(!(ui->listWidget_2->selectedItems().isEmpty())){
    int j=listres->Count();
    for(int i=0; i<j;i++)
    {
        listres->Last()->Widget()->deleteLater();
        listres->DeleteLastElem();
    }

    ActivBdRow(currentRow);
    //}
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    ui->listWidget_3->clear();
    mainlist3->Clear();
    int j=listres->Count();
    for(int i=0; i<j;i++)
    {
        listres->Last()->Widget()->deleteLater();
        listres->DeleteLastElem();
    }

    ui->label_2->setText("<html><head/><body><p><span style=\" font-size:14pt; font-weight:600;\">Тест: &lt;---------------------&gt;</span></p></body></html>");
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_6->setText("");

    if(index==1)
        if(ui->listWidget_2->currentRow()>=0)
            ActivBdRow(ui->listWidget_2->currentRow());

    if(index==0)
        if(ui->listWidget->currentRow()>=0)
            ActivFRow(ui->listWidget->currentRow());


}

void MainWindow::on_pushButton_2_clicked()
{
    //bool fsur=false;

    ui->listWidget_3->clear();
    mainlist3->Clear();

    //if(ui->lineEdit_4->text()!="")
    {

        int count=mainlist->Count();
        mainlist->First();
        for(int i=0;i<count;i++)
        {
            if(mainlist->Current()->surname.indexOf(ui->lineEdit_4->text())==0)
            {
                if(mainlist->Current()->testname.indexOf(ui->comboBox->currentText())==0)
                {
                    int flagk=2;

                    if(ui->checkBox->isChecked())//kurs
                    {
                        flagk=0;
                        if(ui->spinBox_2->value()==mainlist->Current()->kurs)
                            flagk=3;
                    }

                    int flagd=2;

                    if(ui->checkBox_2->isChecked())//date
                    {
                        flagd=0;
                        if(ui->dateEdit->date().day()==mainlist->Current()->date[0] &&
                                ui->dateEdit->date().month()==mainlist->Current()->date[1] &&
                                ui->dateEdit->date().year()==mainlist->Current()->date[2])
                            flagd=3;
                    }

                    if(flagk!=0 && flagd!=0)

                        if(flagk>0 || flagd>0)
                            if(ui->lineEdit_4->text()!="" || ui->comboBox->currentText()!="" || flagk!=2 || flagd!=2)
                            {
                                ui->listWidget_3->addItem(ui->listWidget->item(i)->text());
                                mainlist->SetCurrentToIndex(i);
                                mainlist->Current()->numer=i;
                                mainlist3->Add(mainlist->Current());
                            }
                }
            }
            mainlist->Next();
        }


        count=mainlist2->Count();
        mainlist2->First();
        for(int i=0;i<count;i++)
        {
            if(mainlist2->Current()->surname.indexOf(ui->lineEdit_4->text())==0)
            {
                if(mainlist2->Current()->testname.indexOf(ui->comboBox->currentText())==0)
                {
                    int flagk=2;

                    if(ui->checkBox->isChecked())//kurs
                    {
                        flagk=0;
                        if(ui->spinBox_2->value()==mainlist2->Current()->kurs)
                            flagk=3;
                    }

                    int flagd=2;

                    if(ui->checkBox_2->isChecked())//date
                    {
                        flagd=0;
                        if(ui->dateEdit->date().day()==mainlist2->Current()->date[0] &&
                                ui->dateEdit->date().month()==mainlist2->Current()->date[1] &&
                                ui->dateEdit->date().year()==mainlist2->Current()->date[2])
                            flagd=3;
                    }

                    if(flagk!=0 && flagd!=0)

                        if(flagk>0 || flagd>0)
                            if(ui->lineEdit_4->text()!="" || ui->comboBox->currentText()!="" || flagk!=2 || flagd!=2)
                            {
                                ui->listWidget_3->addItem(ui->listWidget_2->item(i)->text());
                                mainlist2->SetCurrentToIndex(i);
                                mainlist2->Current()->numer=i;
                                mainlist3->Add(mainlist2->Current());

                            }
                }
            }
            mainlist2->Next();
        }
    }
}

void MainWindow::on_listWidget_3_currentRowChanged(int currentRow)
{
    // if(!(ui->listWidget_3->selectedItems().isEmpty())){
    int j=listres->Count();
    for(int i=0; i<j;i++)
    {
        listres->Last()->Widget()->deleteLater();
        listres->DeleteLastElem();
    }


    mainlist3->SetCurrentToIndex(currentRow);
    if(mainlist3->Current()->bd)
        ActivBdRow(mainlist3->Current()->numer);
    else
        ActivFRow(mainlist3->Current()->numer);
    // }
}

void MainWindow::on_pushButton_5_clicked()
{
    if(ui->listWidget->selectedItems().count()==0)
        return;

    //if(ui->listWidget->count()!=0)
    {
        if (QMessageBox::Yes == QMessageBox(QMessageBox::Information,
                                            "Удаление файла",
                                            "Удалить файл \""+mainlist->Current()->adress+"\" навсегда?",
                                            QMessageBox::Yes|QMessageBox::No).exec())
        {
            //mainlist3->Clear();
            int j=listres->Count();
            for(int i=0; i<j;i++)
            {
                listres->Last()->Widget()->deleteLater();
                listres->DeleteLastElem();
            }

            ui->label_2->setText("<html><head/><body><p><span style=\" font-size:14pt; font-weight:600;\">Тест: &lt;---------------------&gt;</span></p></body></html>");
            ui->lineEdit->setText("");
            ui->lineEdit_2->setText("");
            ui->lineEdit_3->setText("");
            ui->lineEdit_6->setText("");

            MyFiles mfile;
            mfile.SetFileName(mainlist->Current()->adress);
            mfile.DelFile();

            mainlist->DeleteCurrentElem();
            delete ui->listWidget->selectedItems().first();
        }
    }

}

void MainWindow::on_pushButton_8_clicked()
{
    if(ui->listWidget_2->selectedItems().count()==0)
        return;
    //if(ui->listWidget_2->count()!=0)
    {
        if (QMessageBox::Yes == QMessageBox(QMessageBox::Information,
                                            "Удаление результата из базы данных",
                                            "Удалить результат из базы?",
                                            QMessageBox::Yes|QMessageBox::No).exec())
        {



            base->DelTable(mainlist2->Current()->adress);
            ui->pushButton_6->click();
        }
    }


}

void MainWindow::on_pushButton_clicked()
{
    if (QMessageBox::Yes == QMessageBox(QMessageBox::Information,
                                        "Экспорт файлов в БД",
                                        "Выгрузить все файлы в базу данных?",
                                        QMessageBox::Yes|QMessageBox::No).exec())
    {

        mainlist->First();
        for(int i=0;i<mainlist->Count();i++){
            QStringList tmp;
            QString tablename;

            if(!(base->RetTablesRezult(&tmp)))//получаем список таблиц
                return ;

            if(tmp.count()==0)
                tablename="r1";
            else{


                tablename=tmp.last();
                tablename.remove(0,1);
                tablename="r"+QString::number(tablename.toInt()+1);
            }

            base->CreteTableTest(tablename);

            MyFiles mfile;
            mfile.SetFileName(mainlist->Current()->adress);
            mfile.OpenFile();
            //////////////////////

            qint32 countP=0;//колличество правил
            quint8 kurs=0;qint32 sum;
            QString a;

            mfile.ReadDataBlock(a);
            base->ApendDataInTest(tablename, a); // test name

            mfile.ReadDataBlock(a);// FIO
            base->ApendDataInTest(tablename, a);

            mfile.ReadDataBlock(a);
            base->ApendDataInTest(tablename, a);

            mfile.ReadDataBlock(a);
            base->ApendDataInTest(tablename, a);

            //kurs
            mfile.ReadDataBlock(kurs);
            base->ApendDataInTest(tablename, QString::number(kurs));

            mfile.ReadDataBlock(a);// date
            base->ApendDataInTest(tablename,  a);

            mfile.ReadDataBlock(countP);
            base->ApendDataInTest(tablename, QString::number(countP));

            for(int i=0;i<countP;i++)
            {
                mfile.ReadDataBlock(a);
                base->ApendDataInTest(tablename, a);
                mfile.ReadDataBlock(a);
                base->ApendDataInTest(tablename, a);

                mfile.ReadDataBlock(kurs);
                base->ApendDataInTest(tablename, QString::number(kurs));

                quint16 aaa;
                mfile.ReadDataBlock(aaa);
                base->ApendDataInTest(tablename, QString::number(aaa));
            }


            ///////////////////////////////
            mfile.CloseFile();

            ui->pushButton_6->click();
        }
    }
}

void MainWindow::on_listWidget_activated(const QModelIndex &index)
{

}

void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{

}

void MainWindow::on_pushButton_3_clicked()
{
    rez a;
    a.list=listres;
    GrafikzDraw* graag=new GrafikzDraw(a);
    graag->showMaximized();
    graag->on_pushButton_2_clicked();
}

void MainWindow::on_pushButton_13_clicked()
{
    if(ui->listWidget_2->selectedItems().count()==0)
        return;

    //if(ui->listWidget_2->count()!=0)
    {
        if (QMessageBox::Yes == QMessageBox(QMessageBox::Information,
                                            "Удаление результататов из базы данных",
                                            "Удалить ВСЕ результаты из базы?",
                                            QMessageBox::Yes|QMessageBox::No).exec())
        {

            mainlist2->First();
            for(int i=0;i < mainlist2->Count();i++)
            {
                base->DelTable(mainlist2->Current()->adress);
                mainlist2->Next();
            }

            ui->pushButton_6->click();
        }
    }
}

void MainWindow::on_pushButton_11_clicked()// delete current result found
{
    if(mainlist3->Count()>0)
    {
        if(ui->listWidget_3->selectedItems().count()!=0)
            if(mainlist3->Current()->bd)
            {
                if (QMessageBox::Yes == QMessageBox(QMessageBox::Information,
                                                    "Удаление результата из базы данных",
                                                    "Удалить результат из базы?",
                                                    QMessageBox::Yes|QMessageBox::No).exec())
                {



                    base->DelTable(mainlist3->Current()->adress);
                    ui->pushButton_6->click();//обновить список из бд
                    mainlist3->DeleteCurrentElem();
                    delete ui->listWidget_3->selectedItems().first();
                }
            }
            else
            {
                if (QMessageBox::Yes == QMessageBox(QMessageBox::Information,
                                                    "Удаление файла",
                                                    "Удалить файл \""+mainlist3->Current()->adress+"\" навсегда?",
                                                    QMessageBox::Yes|QMessageBox::No).exec())
                {
                    mainlist->First();

                    for(int j=0;j<mainlist->Count();j++)
                    {
                        if(mainlist3->Current()->adress==mainlist->Current()->adress)
                        {
                            mainlist->SetCurrentToIndex(j);
                            mainlist->DeleteCurrentElem();
                            delete ui->listWidget->item(j);
                            break;
                        }

                        mainlist->Next();
                    }
                    //mainlist3->Clear();
                    int j=listres->Count();
                    for(int i=0; i<j;i++)
                    {
                        listres->Last()->Widget()->deleteLater();
                        listres->DeleteLastElem();
                    }

                    ui->label_2->setText("<html><head/><body><p><span style=\" font-size:14pt; font-weight:600;\">Тест: &lt;---------------------&gt;</span></p></body></html>");
                    ui->lineEdit->setText("");
                    ui->lineEdit_2->setText("");
                    ui->lineEdit_3->setText("");
                    ui->lineEdit_6->setText("");

                    MyFiles mfile;
                    mfile.SetFileName(mainlist3->Current()->adress);
                    mfile.DelFile();

                    mainlist3->DeleteCurrentElem();
                    delete ui->listWidget_3->selectedItems().first();
                }
            }
    }
}

void MainWindow::on_pushButton_12_clicked()// удалить все результаты поиска
{
    if(mainlist3->Count()>0)
    {

        //if(ui->listWidget_3->selectedItems().count()!=0)
        if (QMessageBox::Yes == QMessageBox(QMessageBox::Information,
                                            "Удалить все найденые",
                                            "Удалить все найденые? Будут удалены локальные файлы и результаты и результаты из БД.",
                                            QMessageBox::Yes|QMessageBox::No).exec())
        {

            int j=listres->Count();
            for(int i=0; i<j;i++)
            {
                listres->Last()->Widget()->deleteLater();
                listres->DeleteLastElem();
            }

            mainlist3->First();
            for(int i=0;i<mainlist3->Count(); i++)
            {
                if(mainlist3->Current()->bd)
                {
                    base->DelTable(mainlist3->Current()->adress);
                    //ui->pushButton_6->click();//обновить список из бд
                }
                else
                {
                    mainlist->First();

                    for(int j=0;j<mainlist->Count();j++)
                    {
                        if(mainlist3->Current()->adress==mainlist->Current()->adress)
                        {
                            mainlist->SetCurrentToIndex(j);
                            mainlist->DeleteCurrentElem();
                            delete ui->listWidget->item(j);
                            break;
                        }

                        mainlist->Next();
                    }
                    //mainlist3->Clear();




                    MyFiles mfile;
                    mfile.SetFileName(mainlist3->Current()->adress);
                    mfile.DelFile();

                    //mainlist3->DeleteCurrentElem();

                }
                mainlist3->Next();
            }
            //qApp->processEvents();
            ui->pushButton_6->click();//обновить список из бд
            ui->listWidget_3->clear();
            //mainlist3->Clear();
            //qApp->processEvents();
            //ui->pushButton_2->click();

//            ui->label_2->setText("<html><head/><body><p><span style=\" font-size:14pt; font-weight:600;\">Тест: &lt;---------------------&gt;</span></p></body></html>");
//            ui->lineEdit->setText("");
//            ui->lineEdit_2->setText("");
//            ui->lineEdit_3->setText("");
//            ui->lineEdit_6->setText("");

        }
    }
}
