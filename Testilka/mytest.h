#ifndef MYTEST_H
#define MYTEST_H

#include "myvopros.h"// один вопрос теста

//new timer
struct tim
{
    quint8 h;
    quint8 m;
    quint8 s;

    tim():h(0),m(0),s(0)
    {
    }
};
//new timer end

struct intervaL//интервал для правила
{
    quint8 type;
    double ot;
    double doo;
    QString line;
    QString text;

       quint16 attrib;
    intervaL()
    {
        ot=0;
        doo=0;
    }
};

struct prawilo//правило для группы вопросов теста
{
    MyListLink<intervaL> *intervals;
    MyListLink<quint16> *voprosnums;

    prawilo()
    {
        intervals=new MyListLink<intervaL>(LINK_MODE);
        voprosnums=new MyListLink<quint16>(COPY_MODE);
    }
};

struct RezulTest
{
    QString head;
    quint8 sum;
    quint16 attrib;
    QString info;
    bool graf;
};

class MyTest
{
public:
    //private info
    QString FIO[3];
    quint8 kurs;// if=0 препод
    MyListLink<RezulTest> *rezult;
    int sum;

    //new timer
    tim timeTest;
    quint8 attrib2;
    //new timer end

    MyListLink<prawilo> *pravils;// список правил теста
    MyListLink<MyVopros> *VoprosList;// Хранит в себе элементы теста(вопросы и варианты ответа, каждая его запись один вопрос)
    QString TestName;// Имя TEsta
    quint16 atrib;// хранит атрибуты текста
    QString Komment;// Описание самого теста
    QString Log;//данные о том кто создал тест и о том кто его редактировал(изменяется только программой при действиях пользователя)
public:
    MyTest()
    {
        atrib=0;
        rezult=new MyListLink<RezulTest>(LINK_MODE);

        VoprosList=new MyListLink<MyVopros>(LINK_MODE);
        pravils=new MyListLink<prawilo>(LINK_MODE);
    }

    void SetAtribute(quint16 na)
    {
        atrib=na;
    }

    quint16 GetAtribute()
    {
        return atrib;
    }

    void CalcAttribute(bool randvop, bool randotwet, bool gui2,bool gui3)
    {
        quint16 tmp=0;
        if(randvop)
            tmp++;
        if(randotwet)
            tmp+=2;

        tmp*=10;

        if(gui2)
            tmp++;

        if(gui3)
            tmp+=2;

        SetAtribute(tmp);
    }

    void GetCalcAttribute(QCheckBox *randvop, QCheckBox *randotwet,
                          QRadioButton *gui1, QRadioButton *gui2, QRadioButton *gui3)
    {
        quint16 tmp=GetAtribute();
        if(tmp%10==0)
            gui1->setChecked(true);
        else if(tmp%10==1)
            gui2->setChecked(true);
        else
            gui3->setChecked(true);

        tmp/=10;

        if(tmp==1 || tmp==3)
            randvop->setChecked(true);
        if(tmp==2 || tmp==3)
            randotwet->setChecked(true);

    }

    void SetTestName(QString newName)
    {
        TestName=newName;
    }

    QString GetTestName()
    {
        return TestName;
    }

    void SetKomment(QString newKom)
    {
        Komment=newKom;
    }

    QString GetKomment()
    {
        return Komment;
    }

    void AppendLog();
    void ClearLog();
};

#endif // MYTEST_H
