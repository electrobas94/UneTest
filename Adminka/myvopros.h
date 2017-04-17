#ifndef MYVOPROS_H
#define MYVOPROS_H
//#include <QString>
#include <QPixmap>
#include "mylistlink.h"//динамический список
#include "myotwet.h"// вариат ответа


class MyVopros
{
private:
    QString Text;// текст вопроса
    QImage Image;// изображение к вопросу
    quint8 TypeOtwet;// тип вариантов ответа и в какой форме они представлены(checkbox, radiobox  и тд)
public:
    MyListLink<MyOtwet> *OtwetList;//список содержащий варианты ответа к тесту

    MyVopros()
    {
        TypeOtwet=0;
        OtwetList= new MyListLink<MyOtwet>(LINK_MODE);
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

    ~MyVopros();// при удалении вызывает очистку списка вариантов ответа
};

#endif // MYVOPROS_H

