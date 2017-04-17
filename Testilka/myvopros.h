#ifndef MYVOPROS_H
#define MYVOPROS_H
//#include <QString>
#include <QPixmap>
#include "mylistlink.h"//динамический список
#include "myotwet.h"// вариат ответа
#include <QButtonGroup>
#include <QMainWindow>


class MyVopros
{
private:
    //QButtonGroup* group1;
    QString Text;// текст вопроса
    QImage Image;// изображение к вопросу
    quint8 TypeOtwet=0;// тип вариантов ответа и в какой форме они представлены(checkbox, radiobox  и тд)
public:
    MyListLink<MyOtwet> *OtwetList;//список содержащий варианты ответа к тесту

    MyVopros()
    {
        //group1= new QButtonGroup();
        OtwetList= new MyListLink<MyOtwet>(LINK_MODE);
    }

    void ReSetGroup()
    {
        if(TypeOtwet!=0)
            return;
        //OtwetList->First()->GetRadio()->setChecked(true);
        QRadioButton **masrad=new QRadioButton *[OtwetList->Count()];
        for(int i=0;i<OtwetList->Count();i++)
        {
            masrad[i]=OtwetList->Current()->GetRadio();
            OtwetList->Next();
        }

        int j=OtwetList->Count();

        for(int i =0;i<j;i++)
            for(int ii =i;ii<j;ii++)
            {
                if(ii==i)
                    continue;
                QObject::connect(masrad[i], SIGNAL(clicked(bool)), masrad[ii], SLOT(toggle()));
                QObject::connect(masrad[ii], SIGNAL(clicked(bool)), masrad[i], SLOT(toggle()));
            }

    }

    void SetText(QString str)// установка текста вопроса
    {
        Text=str;
    }

    QString GetText()
    {
        return Text;
    }

    QImage* GetImage()
    {
        return &Image;
    }

    void ClearOtwetGraf()// очищает фиджеты ответов, оставляя только данные
    {
        OtwetList->First();
        for(int i=0;i<OtwetList->Count();i++)
        {
            OtwetList->Current()->DeleteGrafic();
            OtwetList->Next();
        }
        OtwetList->First();
    }

    void SetImage(QImage &img)//установить изображение
    {
        Image=img;
    }

    void SetTypotwet(quint8 newType)// тип ответа
    {
        TypeOtwet=newType;
    }

    quint8 GetTypotwet()
    {
        return TypeOtwet;
    }

    int GetSumPoints()
    {
        int sum=0;
        OtwetList->First();
        for(int i=0; i<OtwetList->Count(); i++)//проходим по всем ответам
        {
            if(OtwetList->Current()->GetChek())
                sum+=OtwetList->Current()->GetMark();//заменить для знакового типа данных
            OtwetList->Next();
        }

        return sum;
    }

    ~MyVopros();// при удалении вызывает очистку списка вариантов ответа
};

#endif // MYVOPROS_H

