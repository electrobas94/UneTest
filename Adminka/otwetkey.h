#ifndef OTWETKEY_H
#define OTWETKEY_H
#include <QFileDialog>
#include "mylistlink.h"
#include "optionotwet.h"
#include "myfiles.h"
#include <QComboBox>
#include <QLayout>
#include <QListWidget>

class interval
{
public:
    MyListLink<OptionOtwet> *Opitem=NULL;
    quint16 *listvop;
    quint16 countv;

    interval()
    {
        listvop=NULL;
        countv=0;
        Opitem = new MyListLink<OptionOtwet>(LINK_MODE);
    }

    ~interval()
    {
        Opitem->Clear();
        delete Opitem;
    }

    void CreteList(quint16 count)
    {
        countv=count;
        if(listvop!=NULL)
                delete listvop;
        listvop=new quint16[count];
    }

    void HideAll()
    {
        Opitem->First();
        for(int i=0;i<Opitem->Count();i++)
        {
            Opitem->Current()->Hide();
            Opitem->Next();
        }
        Opitem->First();
    }

    void ShowAll()
    {
        Opitem->First();
        for(int i=0;i<Opitem->Count();i++)
        {
            Opitem->Current()->Show();
            Opitem->Next();
        }
        Opitem->First();
    }
};


class OtwetKey
{
public:
    quint16 voprosCount;
    MyListLink<interval> *PrawItems;// список интервалов

    OtwetKey()
    {
        voprosCount=0;
        PrawItems= new MyListLink<interval>(LINK_MODE);
    }

    void SaveVopros(quint16 count)
    {
        PrawItems->Current()->CreteList(count);
    }

    void SaveInFile()
    {
        try {// что бы прога не падала если экстренно закрываеть диалог
            QString str = QFileDialog::getSaveFileName(0, "Сохранить набор проверки",
                                                       "", "Файлы правил проверки (*.PRAW)");// ввод названия теста

            if(str=="")
                return;

            MyFiles mfile;
            mfile.SetFileName(str);
            mfile.NewFile();

            quint16 countV=voprosCount;//количество вопросов в тесте
            quint16 countP=PrawItems->Count();//колличество правил
            quint16 countI=0;//колличество интервало(изменяется)

            PrawItems->First();
            //ui->comboBox->setCurrentIndex(0);
            mfile.Append(countV);//кол-во вопросов в тесте
            mfile.Append(countP);// колво правил пишем

            for(int i=0;i<countP;i++)//все правила
            {
                PrawItems->Current()->Opitem->First();
                countI=PrawItems->Current()->Opitem->Count();

                mfile.Append(PrawItems->Current()->countv);// колво вопросов в правиле

                // проход по списку загруженных вопросов
                for(int j=0;j<PrawItems->Current()->countv;j++)
                {
                     mfile.Append(PrawItems->Current()->listvop[j]);
                }

                mfile.Append(countI);// интервалов в правиле quint16

                for(int j=0;j<countI;j++)//проход по интервалам
                {
                    mfile.Append(PrawItems->Current()->Opitem->Current()->GetOt());// ot qint32
                    mfile.Append(PrawItems->Current()->Opitem->Current()->GetOt());// do qint32
                    mfile.Append(PrawItems->Current()->Opitem->Current()->GetLine());// line qstring
                    mfile.Append(PrawItems->Current()->Opitem->Current()->GetText());// text qstring
                    mfile.Append(PrawItems->Current()->Opitem->Current()->GetType());// type quint8

                    PrawItems->Current()->Opitem->Next();
                }

                PrawItems->Next();
            }

        mfile.CloseFile();
        } catch (...){}// если было закрыто или зависло

    }

    void OpenInFile(QComboBox *combo, QVBoxLayout *laut, QListWidget *l1, QListWidget *l2)
    {
        try {// что бы прога не падала если экстренно закрываеть диалог
            QString str = QFileDialog::getOpenFileName(0, "Открыть набор проверки",
                                                       "", "Файлы правил проверки (*.PRAW)");// ввод названия теста

            if(str=="")
                return;
//////////////
            if(PrawItems->Count()!=0)
            {
                PrawItems->Current()->HideAll();
                PrawItems->Clear();
                combo->clear();
            }

            MyFiles mfile;
            mfile.SetFileName(str);
            mfile.OpenFile();

            quint16 countV=0;//количество вопросов в тесте
            quint16 countP=0;//колличество правил
            quint16 countI=0;//колличество интервало(изменяется)

            mfile.ReadDataBlock(countV);// читаем колво вопросов
            mfile.ReadDataBlock(countP);//правил

            voprosCount=countV;

            if(countP==0)
                return;

            for(int i=0;i<countP;i++)//все правила
            {
                interval *Opitem=new interval();
                //Opitem->countv=countI;
                mfile.ReadDataBlock(Opitem->countv);// активных вопросов в правиле

                mfile.ReadDataBlock(countI);//читаем колво интервалов

                // создаем список вопросов действия
                Opitem->CreteList(Opitem->countv);

                for(int j=0;j<Opitem->countv;j++)
                {
                    mfile.ReadDataBlock(Opitem->listvop[j]);
                }

                for(int j=0;j<countI;j++)//проход по интервалам
                {
                    OptionOtwet *tmp2=new OptionOtwet();
                    double tmp=0;

                    mfile.ReadDataBlock(tmp);
                    tmp2->SetOt(tmp);

                    mfile.ReadDataBlock(tmp);
                    tmp2->SetDo(tmp);

                    QString sstr;
                    mfile.ReadDataBlock(sstr);
                    tmp2->SetLine(sstr);

                    mfile.ReadDataBlock(sstr);
                    tmp2->SetText(sstr);

                    quint8 df;
                    mfile.ReadDataBlock(df);
                    tmp2->SetType(df);

                    Opitem->Opitem->Add(tmp2);

                    tmp2->Hide();
                    laut->addWidget(tmp2->Widget());// привязываем к выводу

                }


                combo->addItem("Правило "+QString::number(combo->count()+1));
                PrawItems->Add(Opitem);

            }

            for(quint16 ii=0;ii<countV;ii++)
            {
                for(int j=0;j<PrawItems->Current()->countv;j++)
                {
                    if(PrawItems->Current()->listvop[j]==ii)
                    {
                        l1->addItem("Вопрос "+QString::number(ii+1));
                        goto Next;// к новой итерации главного цикла
                    }

                }

                l2->addItem("Вопрос "+QString::number(ii+1));
                Next:;
            }


             PrawItems->First();
             PrawItems->Current()->ShowAll();

             mfile.CloseFile();
//////////////////





        } catch (...){}// если было закрыто или зависло

    }
};

#endif // OTWETKEY_H
