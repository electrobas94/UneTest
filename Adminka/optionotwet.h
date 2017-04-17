#ifndef OPTIONOTWET_H
#define OPTIONOTWET_H
#include <QDoubleSpinBox>
#include <QLabel>
#include <QPlainTextEdit>
#include <QLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QRadioButton>

struct Graf
{
    QVBoxLayout *laut;
    QHBoxLayout *laut2;
    QCheckBox *chek;//show ball
    QCheckBox *chek2;//shiw text

    QLineEdit *line;

    QDoubleSpinBox *sp1;
    QDoubleSpinBox *sp2;
    QFrame *win;
    QLabel *l1;
    QLabel *l2;
    QLabel *l3;

    QFrame *win2;
    QPlainTextEdit *text;

    // new
    QFrame *frOptions;
    QVBoxLayout *lutOption;
    QCheckBox* forGrafik;

    QLabel *titl;

    QLabel *titl2;

    QRadioButton *r1;

    QRadioButton *r2;

    QRadioButton *r3;
};

class OptionOtwet
{
public:

    OptionOtwet()
    {
        CreteGraf();
    }
    ~OptionOtwet()
    {
        DeleteGraf();
    }



    void Show()
    {
        grafic.win2->show();
    }

    QString GetLine()
    {
        return grafic.line->text();
    }

    QString GetText()
    {
        return grafic.text->toPlainText();
    }

    quint8 GetType()
    {
        quint8 tmp=0;

        if(grafic.chek->isChecked())
            tmp++;
        if(grafic.chek2->isChecked())
            tmp+=2;

        return tmp;
    }

    void Hide()
    {
        grafic.win2->hide();
    }

    double GetOt()
    {
        return grafic.sp1->value();
    }

    double GetDo()
    {
        return grafic.sp2->value();
    }

    QWidget* Widget()
    {
        return grafic.win2;
    }

    void SetLine(QString tmp)
    {
        grafic.line->setText(tmp);
    }

    void SetText(QString tmp)
    {
        grafic.text->document()->setPlainText(tmp);
    }

    void SetType(quint8 type)
    {
        if(type==0)
            return;
        if(type==1)
            grafic.chek->setChecked(true);
        if(type==3)
        {
            grafic.chek2->setChecked(true);
            grafic.chek->setChecked(true);
        }
        if(type==2)
        {
            grafic.chek2->setChecked(true);
        }

    }

    void SetOt(double tm)
    {
        grafic.sp1->setValue(tm);
    }

    void SetDo(double tm)
    {
        grafic.sp2->setValue(tm);
    }

    int GetAttrib()
    {
        int tmp=0;
        if( grafic.chek->isChecked() )
            tmp+=1000;
        if( grafic.chek2->isChecked() )
            tmp+=100;
        if( grafic.forGrafik->isChecked() )
            tmp+=10;
        if( grafic.r3->isChecked() )
            tmp+=3;
        else  if( grafic.r2->isChecked() )
            tmp+=2;
        else
            tmp+=1;

        return tmp;

    }

    void SetAttrib(int attrib)
    {
        int tmp=0;

        tmp=attrib%10;
        attrib/=10;

        switch (tmp) {
        case 1:
            grafic.r1->setChecked(true);
            break;
        case 2:
            grafic.r2->setChecked(true);
            break;
        default:
            grafic.r3->setChecked(true);
            break;
        }

        tmp=attrib%10;
        attrib/=10;
        if(tmp==1)
        {
            grafic.forGrafik->setChecked(true);
        }
        else
            grafic.forGrafik->setChecked(false);

        tmp=attrib%10;
        attrib/=10;
        if(tmp==1)
            grafic.chek2->setChecked(true);
        else
            grafic.chek2->setChecked(false);

        tmp=attrib%10;
        attrib/=10;
        if(tmp==1)
            grafic.chek->setChecked(true);
        else
            grafic.chek->setChecked(false);


    }

private:

    Graf grafic;

    void CreteGraf()
    {
        grafic.line=new QLineEdit();

        grafic.laut=new QVBoxLayout();
        grafic.laut2=new QHBoxLayout();
        grafic.chek=new QCheckBox();
        grafic.chek2=new QCheckBox();

        grafic.chek->setText("Показать бал");
        grafic.chek->setChecked(true);
        grafic.chek2->setText("Показать текст");
        grafic.chek2->setChecked(true);

        grafic.sp1=new QDoubleSpinBox();
        grafic.sp2=new QDoubleSpinBox();

        grafic.sp1->setMaximum(999999);
        grafic.sp2->setMaximum(999999);

        grafic.sp1->setMinimum(-999999);
        grafic.sp2->setMinimum(-999999);

        grafic.win=new QFrame();
        grafic.l1=new QLabel();
        grafic.l2=new QLabel();
        grafic.l3=new QLabel();

        grafic.win2=new QFrame();
        grafic.text=new QPlainTextEdit();

        grafic.l1->setText(" От");
        grafic.l2->setText(" До");
        grafic.l3->setText(" Заголовок:");

        grafic.l1->setMaximumHeight(20);
        grafic.l2->setMaximumHeight(20);
        grafic.l3->setMaximumHeight(20);

        grafic.laut->addWidget(grafic.l3);//заголовок
        grafic.laut->addWidget(grafic.line);//поле ввода
        grafic.laut->addWidget(grafic.l1);//от
        grafic.laut->addWidget(grafic.sp1);//спин
        grafic.laut->addWidget(grafic.l2);//до
        grafic.laut->addWidget(grafic.sp2);//спин
//        grafic.laut->addWidget(grafic.chek);//выводить балл
//        grafic.laut->addWidget(grafic.chek2);//выводить текст

        grafic.win->setLayout(grafic.laut);

        grafic.laut2->addWidget(grafic.win);
        grafic.laut2->addWidget(grafic.text);
        //
            grafic.frOptions=new QFrame();
            grafic.lutOption= new QVBoxLayout();
            grafic.forGrafik=new QCheckBox();
            grafic.forGrafik->setText("Отразить в графике");

            grafic.titl=new QLabel();
            grafic.titl->setText("Видимость:");
            grafic.titl->setMaximumHeight(23);

            grafic.titl2=new QLabel();
            grafic.titl2->setText("Опции:");
            grafic.titl2->setMaximumHeight(23);

            grafic.r1=new QRadioButton();
            grafic.r1->setText("Пользователи");
            grafic.r1->setStyleSheet("border: 0px solid #808090;");

            grafic.r2=new QRadioButton();
            grafic.r2->setText("Администраторы");
           grafic. r2->setStyleSheet("border: 0px solid #808090;");

            grafic.r3=new QRadioButton();
            grafic.r3->setText("Обе группы");
            grafic.r3->setChecked(true);
           grafic. r3->setStyleSheet("border: 0px solid #808090;");



            grafic.lutOption->addWidget(grafic.titl2);//выводить текст
            grafic.lutOption->addWidget(grafic.forGrafik);
            grafic.lutOption->addWidget(grafic.chek);//выводить балл
            grafic.lutOption->addWidget(grafic.chek2);//выводить текст

            grafic.lutOption->addWidget(grafic.titl);//выводить текст

            grafic.lutOption->addWidget(grafic.r1);//выводить текст
            grafic.lutOption->addWidget(grafic.r2);//выводить текст
            grafic.lutOption->addWidget(grafic.r3);//выводить текст

            grafic.frOptions->setLayout(grafic.lutOption);
            grafic.frOptions->setMinimumWidth(165);

            grafic.frOptions->setStyleSheet("border: 2px solid #808090;");
            grafic.forGrafik->setStyleSheet("border: 0px solid #808090;");

            grafic.laut2->addWidget(grafic.frOptions);
        //

        grafic.win2->setLayout(grafic.laut2);
        grafic.win2->setMinimumHeight(220);
        grafic.win2->setMaximumHeight(220);
        grafic.win->setMaximumWidth(150);
        grafic.win2->setStyleSheet("border: 0px solid #808090;");
        grafic.chek->setStyleSheet("border: 0px solid #808090;");
        grafic.chek2->setStyleSheet("border: 0px solid #808090;");
        grafic.win->setStyleSheet("border: 2px solid #808090;");
        grafic.text->setStyleSheet("border: 2px solid #808090;");
        grafic.line->setText("Параметр(Н)");
    }
public:
    void DeleteGraf()
    {
          grafic.win2->close();

          // НЕ ОЧИЩАЕТСЯ ПОТОМ РАЗОБРАТЬСЯ))

        delete grafic.chek;
        delete grafic.chek2;

        delete grafic.sp1;
        delete grafic.sp2;

        delete grafic.l1;
        delete grafic.l2;
        delete grafic.l3;
        delete grafic.text;
        delete grafic.line;

        delete grafic.laut;
        delete grafic.win;
        delete grafic.laut2;
        delete grafic.win2;

    }

};

#endif // OPTIONOTWET_H
