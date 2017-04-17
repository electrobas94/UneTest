#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QLabel>
#include <QLineEdit>
#include "myadmin.h"
#include "mytest.h"
#include "myprintrezult.h"

namespace Ui {
class Form;
}


class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(MyTest *test, MyAdmin *Admin, QWidget *parent = 0);
    ~Form();

    void PrintInfo(MyTest *test, QVBoxLayout *verticalLayout_4)
    {
        quint8  countP=test->pravils->Count();// оличиство правил(подразумевается что интервалы не дублируется)

        test->pravils->First();
        for(int i=0; i<countP; i++)//проходим по правилам
        {
            int sum=0;//сумма балов по данному правилу
            test->pravils->Current()->voprosnums->First();
            for(int  j=0; j<test->pravils->Current()->voprosnums->Count(); j++)//считамем баллы по правилу
            {
                test->VoprosList->SetCurrentToIndex(*(test->pravils->Current()->voprosnums->Current()));
                sum+=test->VoprosList->Current()->GetSumPoints();
                test->pravils->Current()->voprosnums->Next();
            }

            quint8  countI=test->pravils->Current()->intervals->Count();

            test->pravils->Current()->intervals->First();

            for(int  j=0; j<countI; j++)//о интервалам
            {
                if(sum>=test->pravils->Current()->intervals->Current()->ot && sum<=test->pravils->Current()->intervals->Current()->doo)
                {
                    MyPrintRezult *rezultt=new MyPrintRezult(test->pravils->Current()->intervals->Current()->attrib);
                    RezulTest *rez=new RezulTest();
                    rezultt->SetText(test->pravils->Current()->intervals->Current()->text);
                    rezultt->SetHead(test->pravils->Current()->intervals->Current()->line);
                    rezultt->SetPoint(sum);
                    //rezultt->attrib=test->pravils->Current()->intervals->Current()->attrib;

                    rez->sum=sum;
                    rez->info=test->pravils->Current()->intervals->Current()->text;
                    rez->head=test->pravils->Current()->intervals->Current()->line;
                    rez->attrib=test->pravils->Current()->intervals->Current()->attrib;


                    quint16 att=test->pravils->Current()->intervals->Current()->attrib;

                    quint16 att2=att;

                    att2/=10;// обновляем информации о необходимости выносить в график
                    if(att2%10==1 && (att%10==1 || att%10==3) )
                       rez->graf=true;
                    else
                        rez->graf=false;

                    test->rezult->Add(rez);


                    att%=10;
                    if(att==1 || att==3)
                        verticalLayout_4->addWidget(rezultt->Widget());



                }

                 test->pravils->Current()->intervals->Next();
            }
             test->pravils->Next();
        }
    }

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Form *ui;
};

#endif // FORM_H
