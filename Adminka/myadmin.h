#ifndef MYADMIN_H
#define MYADMIN_H
//#include "mytest.h"
//#include "mygui.h"
//#include <mainwindow.h>
#include <QMessageBox>
#include <QComboBox>
#include <QListWidget>
#include <QInputDialog>
#include <QFileDialog>
#include <QLabel>
#include <QFormLayout>
#include <QMdiSubWindow>

#include "mytestsavlod.h"

#include <QColorDialog>

class MyAdmin// класс всея админки, он есть альфа и омега)предстовляет набор для работы всего приложения
{
private:
    QProgressBar *bar;
    QLabel *imgLabl;
    QTextBrowser *textVopros;
    QListWidget *voprosList;// список вопросов
    QTabWidget *tabw;// указатель на виджеты формы
    QVBoxLayout *otweti;// слой хранящий список ответов
public:
    MyTestSavLod *TestSavLod;//служит для загрузки и сохранения тестов и его компонентов

    //MyAdminSetting AdminSetting;// класс для раьботы с настройками приложения
    MyListLink<MyTest> *TestList;// список всех открытых тестов
    //MyGUI GUI;// все для работы с интерфейсом
    MyAdmin()
    {
        TestList=new MyListLink<MyTest>(LINK_MODE);
        TestSavLod=new MyTestSavLod();
    }

    //    ~MyAdmin();
    void SetBar(QProgressBar *newbar)
    {
        bar=newbar;
    }

    void AddTest()// меню создания теста
    {
        bool bOk;
        QString str = QInputDialog::getText( 0, "Создание теста", "Имя теста:",
                                             QLineEdit::Normal,"Новый тест",&bOk);// ввод названия теста

        if (!bOk) // отмена была нажата
            return;

        if(TestList->Count()!=0)
            if(TestList->Current()->VoprosList->Count()!=0)// список вопросов пуст
            {
                SaveVopros();
                TestList->Current()->VoprosList->Current()->ClearOtwetGraf();//удаляем ответы

                //удаляем текущую картинку
                QPixmap tmp;
                imgLabl->setPixmap(tmp);
            }

        CreteTest(str);
    }

    void CreteTest(QString name)// создает обьект нового теста в памятиы
    {
        MyTest *newTest=new MyTest();
        newTest->SetTestName(name);
        TestList->Add(newTest);
        TestList->Last();

        QWidget *tmp=new QWidget();// создаем  вкладку
        tabw->addTab(tmp, " "+name);// пробел для лучшеего отображения
        tabw->setCurrentIndex(tabw->count()-1);
    }

    void SetTabWidget(QTabWidget *newTab)
    {
        tabw=newTab;
    }

    void SetOtweti(QVBoxLayout *newOtweti)
    {
        otweti=newOtweti;
    }

    void SetTabWidget(QListWidget *newList)
    {
        voprosList=newList;
    }

    void SetTextVopros(QTextBrowser *newtext)
    {
        textVopros=newtext;
    }

    void AddVopros(bool flag_d)// добавляем новый вопрос
    {
        if(TestList->Count()==0)//тестов нету
            return;

        if(TestList->Current()->VoprosList->Count()!=0)// список вопросов пуст
        {
            SaveVopros();
            textVopros->clear();
            TestList->Current()->VoprosList->Current()->ClearOtwetGraf();//удаляем ответы
        }

        voprosList->addItem("Вопрос "+QString::number(voprosList->count()+1));// добавляем в список
        voprosList->setCurrentRow(voprosList->count()-1,QItemSelectionModel::ClearAndSelect);
        voprosList->setFocus();

        MyVopros *newVopros=new MyVopros();//добовляем новый вопрос в список
        TestList->Current()->VoprosList->Add(newVopros);// First - заменить на  Current для многодоков
        TestList->Current()->VoprosList->Last();

        imgLabl->setPixmap(QPixmap::fromImage(*(TestList->Current()->VoprosList->Current()->GetImage())));

        if(flag_d && TestList->Current()->VoprosList->Count()>1)// если включен режим переноса ответа
        {
            MyVopros *vop1=TestList->Current()->VoprosList->Prev();
            TestList->Current()->VoprosList->Last();
            MyVopros *vop2=TestList->Current()->VoprosList->Current();

            vop2->OtwetList->First();
            vop1->OtwetList->First();

            for(int i=0;i<vop1->OtwetList->Count();i++)
            {
                AddOtwet();
                vop2->OtwetList->Current()->SetText(vop1->OtwetList->Current()->GetText());
                vop2->OtwetList->Current()->SetMarc(vop1->OtwetList->Current()->GetMark());

                vop2->OtwetList->Current()->RetGraf().tbrowser->setHtml(vop1->OtwetList->Current()->GetText());
                vop2->OtwetList->Current()->RetGraf().spin->setValue(vop1->OtwetList->Current()->GetMark());

                vop2->OtwetList->Next();
                vop1->OtwetList->Next();
            }

            //SaveVopros();
            SetTypeOtwet(vop1->GetTypotwet());

            ReCalcOtwet();
        }
    }

    void ClearGraf()// очистка графики
    {
        TestList->Current()->VoprosList->Current()->ClearOtwetGraf();//удаляем ответы
        textVopros->clear();
    }

    int  ChangeVopros(quint16 nindex)//смена текущего вопроса
    {
        SaveVopros();
        //удаляем текущую картинку
        textVopros->clear();
        TestList->Current()->VoprosList->Current()->ClearOtwetGraf();//удаляем ответы
        TestList->Current()->VoprosList->SetCurrentToIndex(nindex);//переключаем текущий вопрос

        voprosList->setCurrentRow(nindex ,QItemSelectionModel::ClearAndSelect);
        voprosList->setFocus();
        return LoadVopros();
    }

    void SaveVopros()// сохраняет данные о текущем вопросе
    {
        if(TestList->Current()->VoprosList->Count()!=0)
        {
            TestList->Current()->VoprosList->Current()->SetText(textVopros->document()->toHtml());
            //TestList->Current()->VoprosList->Current()->SetImage(imgLabl->);
        }
        //textVopros->clear();//чистим
        ReCalcOtwet();
    }
    int LoadVopros()//загрузка текущего вопроса на форму
    {
        textVopros->setHtml(TestList->Current()->VoprosList->Current()->GetText());

        //  загрузка ответов
        MyListLink<MyOtwet> *tmp=TestList->Current()->VoprosList->Current()->OtwetList;

        tmp->First();
        for(int i=0;i<tmp->Count();i++)
        {
            tmp->Current()->SetType(TestList->Current()->VoprosList->Current()->GetTypotwet());
            otweti->addWidget(tmp->Current()->RetGraf().frame);
            tmp->Current()->RetGraf().frame->show();
            tmp->Next();

        }
        tmp->First();

        QImage *image=TestList->Current()->VoprosList->Current()->GetImage();

        imgLabl->setPixmap(QPixmap::fromImage( *image) );
        if(image->isNull())
            return 150;

        imgLabl->setMaximumWidth( (image->width()*150) / image->height() );
        imgLabl->setMinimumWidth( (image->width()*150) / image->height() );

        if((image->width()*150)/image->height()<100)
            return 100;
        return (image->width()*150)/image->height();
    }

    void AddOtwet()//добавляет вариант ответа
    {
        if(TestList->Count()==0)//тестов нету
            return;

        if(TestList->Current()->VoprosList->Count()==0)//вопросов нету
            return;

        MyOtwet *newOtwet=new MyOtwet();
        newOtwet->SetType(TestList->Current()->VoprosList->Current()->GetTypotwet());
        TestList->Current()->VoprosList->Current()->OtwetList->Add(newOtwet);
        otweti->addWidget(newOtwet->RetGraf().frame);
        newOtwet->RetGraf().frame->show();

        TestList->Current()->VoprosList->Current()->OtwetList->Last();
    }

    void ChangeTest(quint16 index)//смена текущего теста
    {
        if(TestList->Count()==0)
            return;

        if(TestList->Current()->VoprosList->Count()!=0)// список вопросов пуст
        {
            SaveVopros();
            TestList->Current()->VoprosList->Current()->ClearOtwetGraf();//удаляем ответы
            //удаляем текущую картинку
            QPixmap tmp;
            imgLabl->setPixmap(tmp);
        }

        voprosList->clear();// очищаем список вопросов
        textVopros->clear();//чистим

        TestList->SetCurrentToIndex(index);// указываем новый текущий тест
        LoadVoproList();//грузим список вопросов

    }

    void LoadVoproList()
    {
        if(TestList->Current()->VoprosList->Count()==0)// грузить нечего
            return;

        MyListLink<MyVopros> *tmp=TestList->Current()->VoprosList;
        tmp->First();

        for(int i=0;i<tmp->Count();i++)
        {
            voprosList->addItem("Вопрос "+QString::number(i+1));
            tmp->Next();
        }

        voprosList->setCurrentRow(0,QItemSelectionModel::ClearAndSelect);
        voprosList->setFocus();

        TestList->Current()->VoprosList->First();//переключаем текущий вопрос
        LoadVopros();
    }

    void SetTypeOtwet(quint8 type)// смена типа ответов
    {
        if(TestList->Count()==0)
            return;
        if(TestList->Current()->VoprosList->Count()==0)// грузить нечего
            return;

        TestList->Current()->VoprosList->Current()->SetTypotwet(type);

        TestList->Current()->VoprosList->Current()->ClearOtwetGraf();//удаляем ответы
        LoadVopros();
    }

    void OpenTestBD(QString tablename)
    {
        quint16 numer=2;//текущий номер поля таблицы

        if(TestList->Count()!=0)
            if(TestList->Current()->VoprosList->Count()!=0)// список вопросов пуст
            {
                SaveVopros();
                ClearGraf();
            }

        //ДАННЫЕ О ШИФРЕ
        CryptKod tmp;
        tmp.BeginKey=TestSavLod->SUBD->RetFirstItem(tablename,numer).toInt();// считываем ключи для шифрования
        numer++;
        tmp.SteepKey=TestSavLod->SUBD->RetFirstItem(tablename,numer).toInt();
        numer++;
        TestSavLod->Crypto->SetKey(tmp);// устанавливаем шаг и отступ

        //СОЗДАЕМ ТЕСТ И СЧИТЫВАЕМ ЕГО ИМЯ
        CreteTest(TestSavLod->Crypto->Crypt(TestSavLod->SUBD->RetFirstItem(tablename,numer)));// вносим тест в список и создаем вкладку новую
        MyTest *test=TestList->Current();
        numer++;

        //ОПИСАНИЕ, ЛОГ, ОТРИБУТЫ
        test->SetKomment(TestSavLod->Crypto->Crypt(TestSavLod->SUBD->RetFirstItem(tablename,numer)));//описание теста
        numer++;
        //LOG TestSavLod->SUBD->RetFirstItem(tablename,numer)
        numer++;
        quint16 atrib=TestSavLod->Crypto->Crypt(TestSavLod->SUBD->RetFirstItem(tablename,numer)).toInt();
        test->SetAtribute(atrib);
        numer++;

        //timer and new attrib 2
        test->attrib2=TestSavLod->Crypto->Crypt(TestSavLod->SUBD->RetFirstItem(tablename,numer)).toInt();
        numer++;

        test->timeTest.h=TestSavLod->Crypto->Crypt(TestSavLod->SUBD->RetFirstItem(tablename,numer)).toInt();
        numer++;
        test->timeTest.m=TestSavLod->Crypto->Crypt(TestSavLod->SUBD->RetFirstItem(tablename,numer)).toInt();
        numer++;
        test->timeTest.s=TestSavLod->Crypto->Crypt(TestSavLod->SUBD->RetFirstItem(tablename,numer)).toInt();
        numer++;

        //КОЛ_ВО ВОПРОСОВ
        quint16 contvop=TestSavLod->Crypto->Crypt(TestSavLod->SUBD->RetFirstItem(tablename,numer)).toInt();
        numer++;

        bar->setMaximum(contvop);

        //        QString a=TestSavLod->SUBD->RetFirstItem(tablename,numer);
        //        numer++;

        //        //QImage *image=test->VoprosList->Current()->GetImage();
        //        QByteArray bArray(a.toUtf8());
        //        QImage image(bArray);
        //        test->VoprosList->Current()->SetImage(image);
        //        //QBuffer buffer( &bArray );
        //        //buffer.open( QIODevice::WriteOnly );
        //        //image->save(&buffer, "PNG" );

        //        QString b(bArray.data());

        for(int i=0;i<contvop;i++)
        {
            bar->setValue(i);
            AddVopros(false);//добавляем новый вопрос
            VoprosInfo vopros;
            vopros.text=TestSavLod->Crypto->Crypt(TestSavLod->SUBD->RetFirstItem(tablename,numer));
            numer++;


            //QString tmp=TestSavLod->SUBD->RetFirstItem(tablename,numer);
            //QByteArray ba=tmp.toUtf8();

             //vopros.imag.loadFromData(ba, "PNG");

            //numer++;
            //vopros.imag;



            vopros.type=TestSavLod->Crypto->Crypt(TestSavLod->SUBD->RetFirstItem(tablename,numer)).toInt();
            numer++;
            vopros.countOt=TestSavLod->Crypto->Crypt(TestSavLod->SUBD->RetFirstItem(tablename,numer)).toInt();
            numer++;
            test->VoprosList->Current()->SetText(vopros.text);
            textVopros->setText(vopros.text);
            SetTypeOtwet(vopros.type);

            test->VoprosList->Current()->SetImage(vopros.imag);
            imgLabl->setPixmap(QPixmap::fromImage(vopros.imag));
            //test->VoprosList->Current()->SetTypotwet();

            for(int j=0;j<vopros.countOt;j++)//создаем ответы к вопросам
            {
                AddOtwet();//создаем ответ новый
                QString tmp=TestSavLod->Crypto->Crypt(TestSavLod->SUBD->RetFirstItem(tablename,numer));
                test->VoprosList->Current()->OtwetList->Current()->SetText(tmp);
                test->VoprosList->Current()->OtwetList->Current()->RetGraf().tbrowser->setText(tmp);
                numer++;

                tmp=TestSavLod->Crypto->Crypt(TestSavLod->SUBD->RetFirstItem(tablename,numer));
                test->VoprosList->Current()->OtwetList->Current()->SetMarc(tmp.toInt());
                test->VoprosList->Current()->OtwetList->Current()->RetGraf().spin->setValue(tmp.toInt());
                //TestSavLod->ReadOtwet(test->VoprosList->Current()->OtwetList->Current());
                numer++;
            }
            qApp->processEvents();
        }

        // prawils

        qint32 counP=TestSavLod->Crypto->Crypt(TestSavLod->SUBD->RetFirstItem(tablename,numer)).toInt();
        numer++;

        for(int i=0;i<counP;i++)
        {
            prawilo *tmp2=new prawilo();
            qint32 counV=TestSavLod->Crypto->Crypt(TestSavLod->SUBD->RetFirstItem(tablename,numer)).toInt();
            numer++;

            for(int j=0;j<counV;j++)
            {
                quint16 tmp=TestSavLod->Crypto->Crypt(TestSavLod->SUBD->RetFirstItem(tablename,numer)).toInt();
                numer++;
                tmp2->voprosnums->Add(&tmp);
            }

            qint32 counI=TestSavLod->Crypto->Crypt(TestSavLod->SUBD->RetFirstItem(tablename,numer)).toInt();
            numer++;

            for(int j=0;j<counI;j++)
            {
                intervaL *tmp3=new intervaL();
                tmp3->doo=TestSavLod->Crypto->Crypt(TestSavLod->SUBD->RetFirstItem(tablename,numer)).toDouble();
                numer++;
                tmp3->ot=TestSavLod->Crypto->Crypt(TestSavLod->SUBD->RetFirstItem(tablename,numer)).toDouble();
                numer++;
                tmp3->line=TestSavLod->Crypto->Crypt(TestSavLod->SUBD->RetFirstItem(tablename,numer));
                numer++;
                tmp3->text=TestSavLod->Crypto->Crypt(TestSavLod->SUBD->RetFirstItem(tablename,numer));
                numer++;
                tmp3->type=TestSavLod->Crypto->Crypt(TestSavLod->SUBD->RetFirstItem(tablename,numer)).toInt();
                numer++;
                tmp3->attrib=TestSavLod->Crypto->Crypt(TestSavLod->SUBD->RetFirstItem(tablename,numer)).toInt();
                numer++;

                tmp2->intervals->Add(tmp3);
            }

            test->pravils->Add(tmp2);

        }
        test->pravils->First();

        //end prawilas
        ReCalcOtwet();

        return;
    }

    void OpenTest()//открыть тест(как  так и локально)
    {
        if(TestList->Count()!=0)
            if(TestList->Current()->VoprosList->Count()!=0)// список вопросов пуст
            {
                SaveVopros();
                TestList->Current()->VoprosList->Current()->ClearOtwetGraf();//удаляем ответы

                //удаляем текущую картинку
                QPixmap tmp;
                imgLabl->setPixmap(tmp);
            }

        // offline режим
        try {// что бы прога не падала если экстренно закрываеть диалог
            QString str = QFileDialog::getOpenFileName(0, "Открыть тест",
                                                       "", "Файлы тестов (*.TEST)");// ввод названия теста
            if(str=="")
                return;

            TestInfo info;
            if(!(TestSavLod->RetInfoAndOpen(info,str)))// проблемы с файлом
                return;

            if(TestList->Count()!=0)
                if(TestList->Current()->VoprosList->Count()!=0)// список вопросов пуст
                {
                    SaveVopros();
                    TestList->Current()->VoprosList->Current()->ClearOtwetGraf();//удаляем ответы
                }
            CreteTest(info.testname);// вносим тест в список и создаем вкладку новую
            MyTest *test=TestList->Current();
            test->SetKomment(info.komment);//описание теста
            test->SetAtribute(info.attribut);

            test->attrib2=info.attribut2;

            test->timeTest.h=info.HMS[0];
            test->timeTest.m=info.HMS[1];
            test->timeTest.s=info.HMS[2];

            bar->setMaximum(info.countvop);

            for(int i=0;i<info.countvop;i++)
            {
                bar->setValue(i);

                AddVopros(false);//добавляем новый вопрос
                VoprosInfo vopros;
                TestSavLod->ReadVoprosInfo(vopros);
                test->VoprosList->Current()->SetText(vopros.text);




                textVopros->setText(vopros.text);

                //image
               test->VoprosList->Current()->SetImage(vopros.imag);

                //image

                SetTypeOtwet(vopros.type);
                //test->VoprosList->Current()->SetTypotwet();

                for(int j=0;j<vopros.countOt;j++)//создаем ответы к вопросам
                {
                    AddOtwet();//создаем ответ новый
                    TestSavLod->ReadOtwet(test->VoprosList->Current()->OtwetList->Current());
                }

                qApp->processEvents();
            }

            TestSavLod->ReadPravils(test);

            ReCalcOtwet();

        } catch (...)
        {
            // если было закрыто или зависло
        }
        //открываем и грузим файл теста
    }

    void SaveTest()
    {
        //delete treada;
        //treada = new MyTread(voprosList, 0);
        //treada->start();

        if(TestList->Count()==0)
            return;

        if(TestSavLod->SUBD->GetStatus())
        {
            TestSavLod->SaveInBD(TestList->Current(), bar);
        }
        else
        {
            try {// что бы прога не падала если экстренно закрываеть диалог
                QString str = QFileDialog::getSaveFileName(0, "Сохранить тест",
                                                           "", "Файлы тестов (*.TEST)");// ввод названия теста

                if(str=="")
                    return;
                TestSavLod->SaveInFile(TestList->Current(),str , bar);

            } catch (...){}// если было закрыто или зависло

        }
        TestList->Current()->VoprosList->SetCurrentToIndex(voprosList->currentRow());

    }

    void SetImageLabel(QLabel *label)
    {
        imgLabl=label;
    }

    int LoadImage()// загрузка нового изображения к вопросу
    {
        if(TestList->Count()==0)
            return 150;

        if(TestList->Current()->VoprosList->Count()==0)
            return 150;


        try {// что бы прога не падала если экстренно закрываеть диалог
            QString str = QFileDialog::getOpenFileName(0, "Открыть изображение",
                                                       "", "Файлы изображений (*.*)");// ввод названия теста
            if(str=="")
                return 150;

            QImage image(str);
            imgLabl->setMaximumWidth((image.width()*150)/image.height());
            imgLabl->setMinimumWidth((image.width()*150)/image.height());
            imgLabl->setPixmap(QPixmap::fromImage(image));
            QPixmap pix;
            pix.convertFromImage(image,Qt::AutoColor);

            TestList->Current()->VoprosList->Current()->SetImage(image);

            return (image.width()*150)/image.height();

        } catch (...)
        {
            // если было закрыто или зависло, ибо падает при нажатии на кретик
        }
        //открываем и грузим файл теста

        return 150;
    }

    void PrevivImage()
    {
        if(TestList->Count()==0)
            return;

        if(TestList->Current()->VoprosList->Count()==0)
            return;

        //    QString fileName="file.jpg"; // файл, который грузим
        //    QImage image(fileName);
        QLabel *imageLabel = new QLabel;
        //    int t=QApplication::activeWindow()->geometry().top();// узнаем размер экрана
        //    int r=QApplication::activeWindow()->geometry().right()+10;
        imageLabel->setPixmap(QPixmap::fromImage(*(TestList->Current()->VoprosList->Current()->GetImage())));
        //    imageLabel->resize(imageLabel->pixmap()->size());
        //    imageLabel->setGeometry(r, t,imageLabel->pixmap()->size().width(),imageLabel->pixmap()->size().height());
        imageLabel->setScaledContents(true);
        imageLabel->showMaximized();
    }

    void SetSUBDSetting(QString host,QString user, QString pass, QString dbname, quint16 port)//функция указания настроек базы данных
    {
        TestSavLod->SUBD->SetHost(host);
        TestSavLod->SUBD->SetUser(user);
        TestSavLod->SUBD->SetPass(pass);
        TestSavLod->SUBD->SetPortNumer(port);
        TestSavLod->SUBD->SetBaseName(dbname);
    }

    bool ConectBase()
    {
        if(TestSavLod->SUBD->OpenConect())
            return true;
        QMessageBox msgBox;
        msgBox.setText("Соединение не установлено. База недоступна.");
        msgBox.exec();
        return false;

    }

    void CloseConect()
    {
        TestSavLod->SUBD->CloseConect();
    }

    void GetListTest(QComboBox *list, QComboBox *namelist)
    {
        list->clear();
        namelist->clear();

        QStringList tmp;
        if(!(TestSavLod->SUBD->RetTablesTest(&tmp)))//получаем список таблиц
            return;

        namelist->addItems(tmp);
        foreach (QString tablename, tmp)
        {
            list->addItem(TestSavLod->SUBD->RetFirstItem(tablename,1));// тест с таким именем уже существует
        }
    }

    void DeleteVopros()
    {
        if(TestList->Count()==0)
            return;

        if(TestList->Current()->VoprosList->Count()==0)
            return;

        textVopros->clear();
        ClearGraf();

        TestList->Current()->VoprosList->DeleteCurrentElem();

        QListWidgetItem* item = voprosList->item(voprosList->count()-1);
        delete item;

        TestList->Current()->VoprosList->SetCurrentToIndex(0);//переключаем текущий вопрос

        //LoadVopros();

        voprosList->setCurrentRow(0 ,QItemSelectionModel::ClearAndSelect);//не удалять, т.к используется текущая строка

        ReCalcOtwet();

        voprosList->setCurrentRow(0 ,QItemSelectionModel::ClearAndSelect);
        voprosList->setFocus();

    }

    void DeleteOtwet()
    {
        if(TestList->Count()==0)
            return;

        if(TestList->Current()->VoprosList->Count()==0)
            return;
        if(TestList->Current()->VoprosList->Current()->OtwetList->Count()==0)
            return;

        TestList->Current()->VoprosList->Current()->OtwetList->Last()->DeleteGrafic();
        TestList->Current()->VoprosList->Current()->OtwetList->DeleteLastElem();
        ChangeVopros(voprosList->currentRow());
    }

    void DeleteTest(quint16 index)
    {
        if(TestList->Count()==0)
            return;
        if(TestList->Current()->VoprosList->Count()!=0)
        {
            voprosList->clear();
            ClearGraf();
        }

        TestList->DeleteCurrentElem();
        tabw->removeTab(index);
    }

    void RetTestList(QListWidget *list)
    {
        list->clear();
        QStringList *tmp=new QStringList();

        TestSavLod->SUBD->GetTest();//обновляем список таблиц
        TestSavLod->SUBD->RetTestNames(*tmp);

        list->addItems(*tmp);
    }

    void DelTestTable(quint16 index)
    {
        TestSavLod->SUBD->DelTable(TestSavLod->SUBD->RetTableName(index));
    }

    void ReCalcOtwet()// перерисовать
    {
        if(!(ChekExsitVopros()))
            return;

        quint16 tmp=voprosList->currentRow();

        voprosList->clear();

        ClearGraf();
        TestList->Current()->VoprosList->First();

        for(int i=0;i<TestList->Current()->VoprosList->Count();i++)
        {
            textVopros->setHtml(TestList->Current()->VoprosList->Current()->GetText());
            voprosList->addItem("Вопрос "+QString::number(i+1)+" ("+DelEndl(textVopros->toPlainText()).mid(0,20)+"...)");
            TestList->Current()->VoprosList->Next();
        }

        TestList->Current()->VoprosList->SetCurrentToIndex(tmp);
        LoadVopros();
        voprosList->setCurrentRow(tmp ,QItemSelectionModel::ClearAndSelect);
        voprosList->setFocus();

    }

    QString DelEndl(QString data)// второстипенная функция для удаления переноса на новую строку в тексте
    {
        for(int i=0;i<data.count();i++)
        {
            if(data[i]=='\n')
            {
                data.remove(i,1);
                i--;
            }
        }

        return data;
    }

    void ChangePosVopros(quint16 to)//изменяет позицию вопроса
    {
        if(!(ChekExsitVopros()))
            return;

        if((to<0) || (to>=voprosList->count()) || (to==voprosList->currentRow()))
            return;

        SaveVopros();

        textVopros->clear();
        TestList->Current()->VoprosList->Current()->ClearOtwetGraf();//удаляем ответы

        quint16 from=voprosList->currentRow();
        MyVopros *tmp=TestList->Current()->VoprosList->Current();

        TestList->Current()->VoprosList->SetCurrentToIndex(to);
        MyVopros *tmp2=TestList->Current()->VoprosList->Current();
        TestList->Current()->VoprosList->SetCurrentElem(tmp);

        TestList->Current()->VoprosList->SetCurrentToIndex(from);
        TestList->Current()->VoprosList->SetCurrentElem(tmp2);


        TestList->Current()->VoprosList->SetCurrentToIndex(to);//переключаем текущий вопрос
        voprosList->setCurrentRow(to ,QItemSelectionModel::ClearAndSelect);
        LoadVopros();

        ReCalcOtwet();
        //        voprosList->setCurrentRow(to ,QItemSelectionModel::ClearAndSelect);
        //        voprosList->setFocus();
    }

    bool ChekExsitVopros()// проверяет есть ли тест и есть ли в нем вопросы
    {
        if(TestList->Count()==0)
            return false;

        if(TestList->Current()->VoprosList->Count()==0)
            return false;

        return true;
    }

    void RandomPro(quint16 *mass, quint16 count)//неповторяемый рандом вычеркиванием
    {
        srand(time(NULL));

        bool *arra=new bool[count]{true};// потом проверить на работоспособность
        mass=new quint16[count];

        for(int i=0; i<count; i++)
        {
            quint16 tmp=rand()%count;// получаем индекс
            for(tmp;;tmp++)
            {
                if(tmp==count)
                    tmp=0;
                if(arra[tmp])
                {
                    arra[tmp]=false;
                    mass[i]=tmp;
                    break;
                }
            }
        }
    }
};

#endif // MYADMIN_H

