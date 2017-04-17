#ifndef MYTESTSAVLOD_H
#define MYTESTSAVLOD_H

#include <QMessageBox>
#include "mytest.h"
#include "myfiles.h"
#include "mysubd.h"
#include "mycrypto.h"
#include <QProgressBar>

struct TestInfo//базовое описание теста(для его загрузки)
{
    QString testname;
    QString komment;
    QString log;
    quint16 attribut;
    qint32 countvop;// количество вопросов

    quint8 attribut2;
    quint8 HMS[3];
};

struct VoprosInfo
{
    QString text;
    quint8 type;
    qint32 countOt;//количество ответов
    QImage imag;
};

class MyTestSavLod
{
public:
    MySUBD *SUBD;
    MyCrypto *Crypto;
private:
    MyFiles File;// не менять, так как при динамическом создании не работают потоковые функции

public:

    void ReadPravils(MyTest *test)
    {
        qint32 counP;
        File.ReadDataBlock(counP);

        for(int i=0;i<counP;i++)
        {
            prawilo *tmp2=new prawilo();
            qint32 counV;
            File.ReadDataBlock(counV);

            for(int j=0;j<counV;j++)
            {
                quint16 tmp;
                File.ReadDataBlock(tmp);
                tmp2->voprosnums->Add(&tmp);
            }

            qint32 counI;
            File.ReadDataBlock(counI);

            for(int j=0;j<counI;j++)
            {
                intervaL *tmp3=new intervaL();
                File.ReadDataBlock(tmp3->doo);
                File.ReadDataBlock(tmp3->ot);
                File.ReadDataBlock(tmp3->line);
                File.ReadDataBlock(tmp3->text);
                File.ReadDataBlock(tmp3->type);
                //new
                File.ReadDataBlock(tmp3->attrib); // 26.07

                tmp2->intervals->Add(tmp3);
            }

            test->pravils->Add(tmp2);

        }
        test->pravils->First();
    }

    bool SaveInFile(MyTest *test, QString filename,  QProgressBar *bar)//
    {
        CryptKod tmp= Crypto->RandBS();//генери новый шаг и отступ

        File.SetFileName(filename);
        File.NewFile();

        quint16 magic=12343212;// указывает что файл необходимого нам типа
        File.Append(magic);

        //сохраняем параметры ключа(потом можно раскидать в разные части файла)
        File.Append(tmp.BeginKey);
        File.Append(tmp.SteepKey);

        File.Append(Crypto->Crypt(test->TestName));
        File.Append(Crypto->Crypt(test->Komment));
        File.Append(Crypto->Crypt(test->Log));
        File.Append(test->GetAtribute());

        //new timer
        File.Append(test->attrib2);

        File.Append(test->timeTest.h);
        File.Append(test->timeTest.m);
        File.Append(test->timeTest.s);
        //new timer end

        File.Append(magic);//дублируем на всякий пожарный

        qint32 countv=test->VoprosList->Count();

        bar->setMaximum(countv);

        File.Append(countv);// пишем колво вопросов

        test->VoprosList->First();

        for(int i=0;i<countv;i++)
        {
            bar->setValue(i);
            File.Append(Crypto->Crypt(test->VoprosList->Current()->GetText()));//пишем текст вопроса

            //new save image

            File.Append(test->VoprosList->Current()->GetImage());
            //image end

            File.Append(test->VoprosList->Current()->GetTypotwet());// тип варианта ответа
            qint32 countT=test->VoprosList->Current()->OtwetList->Count();// колво вариантов ответа
            File.Append(countT);

            test->VoprosList->Current()->OtwetList->First();
            for(int j=0;j<countT;j++)
            {
                File.Append(Crypto->Crypt(test->VoprosList->Current()->OtwetList->Current()->GetText()));
                File.Append(test->VoprosList->Current()->OtwetList->Current()->GetMark());
                test->VoprosList->Current()->OtwetList->Next();
            }

            test->VoprosList->Next();

            qApp->processEvents();
        }

        test->pravils->First();
        File.Append(test->pravils->Count());

        for(int i=0;i<test->pravils->Count();i++)
        {
            File.Append(test->pravils->Current()->voprosnums->Count());
            test->pravils->Current()->voprosnums->First();

            for(int j=0;j<test->pravils->Current()->voprosnums->Count();j++)
            {
                File.Append(*(test->pravils->Current()->voprosnums->Current() ));
                test->pravils->Current()->voprosnums->Next();
            }

            File.Append(test->pravils->Current()->intervals->Count());
            test->pravils->Current()->intervals->First();
            for(int j=0;j<test->pravils->Current()->intervals->Count();j++)
            {
                File.Append(test->pravils->Current()->intervals->Current()->doo);
                File.Append(test->pravils->Current()->intervals->Current()->ot);
                File.Append(test->pravils->Current()->intervals->Current()->line);
                File.Append(test->pravils->Current()->intervals->Current()->text);
                File.Append(test->pravils->Current()->intervals->Current()->type);
                //new
                File.Append(test->pravils->Current()->intervals->Current()->attrib);

                test->pravils->Current()->intervals->Next();
            }

            test->pravils->Next();

        }
        File.CloseFile();

        return true;
    }

    bool ReadVoprosInfo(VoprosInfo &vopros)
    {
        File.ReadDataBlock(vopros.text);//read текст вопроса
        vopros.text=Crypto->Crypt(vopros.text);

        File.ReadDataBlock(vopros.imag);

        File.ReadDataBlock(vopros.type);// тип варианта ответа
        File.ReadDataBlock(vopros.countOt);
    }

    bool ReadOtwet(MyOtwet *otwet)
    {
        QString tmp;
        File.ReadDataBlock(tmp);
        tmp=Crypto->Crypt(tmp);

        quint16 tmp2;
        File.ReadDataBlock(tmp2);

        otwet->SetText(tmp);
        otwet->SetMarc(tmp2);
        otwet->RetGraf().spin->setValue(tmp2);
        otwet->RetGraf().tbrowser->setText(tmp);

        return true;
    }

    bool RetInfoAndOpen(TestInfo &info, QString filename)//открывает тест и выдает инфу о нем
    {
        File.SetFileName(filename);
        if(!(File.OpenFile()))// не открылся
            return false;

        quint16 magf=0,magic=12343212;// указывает что файл необходимого нам типа
        File.ReadDataBlock(magf);

        if(magf!=magic)// не файл теста, или файл поврежден
            return false;


        CryptKod tmp;
        File.ReadDataBlock(tmp.BeginKey);
        File.ReadDataBlock(tmp.SteepKey);
        Crypto->SetKey(tmp);// устанавливаем шаг и отступ

        File.ReadDataBlock(info.testname);
        info.testname=Crypto->Crypt(info.testname);

        File.ReadDataBlock(info.komment);
        info.komment=Crypto->Crypt(info.komment);

        File.ReadDataBlock(info.log);
        info.log=Crypto->Crypt(info.log);

        File.ReadDataBlock(info.attribut);
        File.ReadDataBlock(info.attribut2);

        File.ReadDataBlock(info.HMS[0]);
        File.ReadDataBlock(info.HMS[1]);
        File.ReadDataBlock(info.HMS[2]);

        File.ReadDataBlock(magf);// на случай вмешательства

        if(magf!=magic)// не файл теста, или файл поврежден
            return false;

        File.ReadDataBlock(info.countvop);// пишем колво вопросов

        return true;
    }

    bool SaveInBD(MyTest *test, QProgressBar *bar)//
    {
        CryptKod tmp = Crypto->RandBS();//генериt новый шаг и отступ

        QString tablename=CalkTableName(test->TestName);
        if(tablename=="")//перезапись не нужна
            return true;



        SUBD->CreteTableTest(tablename);

        SUBD->ApendDataInTest(tablename, test->TestName);

        SUBD->ApendDataInTest(tablename, QString::number(tmp.BeginKey));
        SUBD->ApendDataInTest(tablename, QString::number(tmp.SteepKey));

        SUBD->ApendDataInTest(tablename, Crypto->Crypt(test->TestName));
        SUBD->ApendDataInTest(tablename, Crypto->Crypt(test->Komment));
        SUBD->ApendDataInTest(tablename, Crypto->Crypt(test->Log));
        SUBD->ApendDataInTest(tablename, Crypto->Crypt(QString::number(test->GetAtribute())));

        SUBD->ApendDataInTest(tablename, Crypto->Crypt(QString::number(test->attrib2)));

        SUBD->ApendDataInTest(tablename, Crypto->Crypt(QString::number(test->timeTest.h)));
        SUBD->ApendDataInTest(tablename, Crypto->Crypt(QString::number(test->timeTest.m)));
        SUBD->ApendDataInTest(tablename, Crypto->Crypt(QString::number(test->timeTest.s)));

        qint32 countv=test->VoprosList->Count();
        bar->setMaximum(countv);

        SUBD->ApendDataInTest(tablename, Crypto->Crypt(QString::number(countv)));// пишем колво вопросов

        test->VoprosList->First();

        for(int i=0;i<countv;i++)// вопросы
        {
            bar->setValue(i);
            SUBD->ApendDataInTest(tablename,
                                  Crypto->Crypt(test->VoprosList->Current()->GetText()));//пишем текст вопроса



//           QImage *image= test->VoprosList->Current()->GetImage();
//                    QByteArray ba;
//            QBuffer buffer(&ba);
//            buffer.open(QIODevice::WriteOnly);
//            image->save(&buffer, "PNG"); // writes image into ba in PNG format

//            QString img=QString::fromUtf8(ba);


//            SUBD->ApendDataInTest(tablename,
//                                  img);//пишем текст вопроса

            SUBD->ApendDataInTest(tablename,
                                  Crypto->Crypt(QString::number(test->VoprosList->Current()->GetTypotwet())));// тип варианта ответа

            qint32 countT=test->VoprosList->Current()->OtwetList->Count();// колво вариантов ответа
            SUBD->ApendDataInTest(tablename,
                                  Crypto->Crypt(QString::number(countT)));

            //            QImage *image=test->VoprosList->Current()->GetImage();
            //            QByteArray bArray;
            //            QBuffer buffer( &bArray );
            //            buffer.open( QIODevice::WriteOnly );
            //            image->save(&buffer, "PNG" );

            //            QString b(bArray.data());
            //            SUBD->ApendDataInTest(tablename,
            //                                  b);

            test->VoprosList->Current()->OtwetList->First();
            for(int j=0;j<countT;j++)// варианты ответа к вопросу
            {
                SUBD->ApendDataInTest(tablename,
                                      Crypto->Crypt(test->VoprosList->Current()->OtwetList->Current()->GetText()));
                SUBD->ApendDataInTest(tablename,
                                      Crypto->Crypt(QString::number(test->VoprosList->Current()->OtwetList->Current()->GetMark())));

                test->VoprosList->Current()->OtwetList->Next();
            }

            test->VoprosList->Next();

            qApp->processEvents();
        }

        // prawills

        test->pravils->First();
        SUBD->ApendDataInTest(tablename,
                              Crypto->Crypt(QString::number(test->pravils->Count() )  ));

        for(int i=0;i<test->pravils->Count();i++)
        {
            SUBD->ApendDataInTest(tablename,
                                  Crypto->Crypt(QString::number(test->pravils->Current()->voprosnums->Count()) ));
            test->pravils->Current()->voprosnums->First();

            for(int j=0;j<test->pravils->Current()->voprosnums->Count();j++)
            {
                SUBD->ApendDataInTest(tablename,
                                      Crypto->Crypt(QString::number(*(test->pravils->Current()->voprosnums->Current() ))));
                test->pravils->Current()->voprosnums->Next();
            }

            SUBD->ApendDataInTest(tablename,
                                  Crypto->Crypt(QString::number(test->pravils->Current()->intervals->Count())));

            test->pravils->Current()->intervals->First();
            for(int j=0;j<test->pravils->Current()->intervals->Count();j++)
            {
                SUBD->ApendDataInTest(tablename,
                                      Crypto->Crypt(QString::number(test->pravils->Current()->intervals->Current()->doo)));
                SUBD->ApendDataInTest(tablename,
                                      Crypto->Crypt(QString::number(test->pravils->Current()->intervals->Current()->ot)));
                SUBD->ApendDataInTest(tablename,
                                      Crypto->Crypt(test->pravils->Current()->intervals->Current()->line));
                SUBD->ApendDataInTest(tablename,
                                      Crypto->Crypt(test->pravils->Current()->intervals->Current()->text));
                SUBD->ApendDataInTest(tablename,
                                      Crypto->Crypt(QString::number(test->pravils->Current()->intervals->Current()->type)));

                SUBD->ApendDataInTest(tablename,
                                      Crypto->Crypt(QString::number(test->pravils->Current()->intervals->Current()->attrib)));

                test->pravils->Current()->intervals->Next();
            }

            test->pravils->Next();
        }
        return true;
    }
private:
    QString CalkTableName(QString testname)//вычислене имя новой таблицы(если ретурн "" - значит перезапись?)
    {
        QStringList tmp;
        if(!(SUBD->RetTablesTest(&tmp)))//получаем список таблиц
            return "-1";

        if(tmp.count()==0)
            return ("t1");

        foreach (QString tablename, tmp)
        {
            if(testname==SUBD->RetFirstItem(tablename,1))// тест с таким именем уже существует
            {
                QMessageBox msgBox;
                msgBox.addButton(QMessageBox::Ok);
                msgBox.addButton(QMessageBox::Cancel);
                msgBox.setText("Тест с таким именем уже есть в Базе.\n Смените имя или презапишите его.\n Перезаписать?");

                int selection = msgBox.exec();
                if(selection == QMessageBox::Ok)
                {
                    SUBD->RunSQLscript("DROP TABLE `"+tablename+"`;");
                    return tablename;
                }
                else if(selection == QMessageBox::Cancel)
                {
                    return "";
                }
            }
        }

        QString tablname;
        tablname=tmp.last();
        tablname.remove(0,1);
        tablname="t"+QString::number(tablname.toInt()+1);
        return tablname;//имя t+kolwo

    }


public:
    MyTestSavLod()
    {
        SUBD=new MySUBD();
        Crypto= new MyCrypto();
        //File=new MyFiles();
    }
};
#endif // MYTESTSAVLOD_H

