#ifndef MYOTWET_H
#define MYOTWET_H

#include <QString>
#include <QLineEdit>
#include <QLayout>
#include <QTextBrowser>
#include <QRadioButton>
#include <QCheckBox>
#include <QSpinBox>

struct GrafOtwet
{
    QTextBrowser *tbrowser; // содержит текст ответа
    QSpinBox *spin;         // оценка за выбор данного вариана овета
                            // нужны тлько для очиски памяти в общем случае не важны
    QWidget *type;          // ссылка на тип овета(должа сконвертится)
    QFrame *frame;          //фрейм вар овеа
    QHBoxLayout *laut;      // компоновка
};

class MyOtwet
{
private:
    bool isGrag;      // указывает есть ли графика или удалена в данный момент
    QString Text;
    quint16 Marc;           //бал за выбор ответа
    GrafOtwet grafik;       //графическая состовляющая варианта ответа
public:
    MyOtwet()
    {
        isGrag=false;
        Text="";
        Marc=0;
    }

    void SetType(quint8 type)
    {
        DeleteGrafic();
        CreteGrafik(type);
    }

    GrafOtwet RetGraf()// функция возвращает графическую состовляющую ответа
    {
        return grafik;
    }

    void SetText(QString str)
    {
        Text=str;
    }

    void SetMarc(quint16 nmarc)
    {
        Marc=nmarc;
    }

    void SetData(QString str,quint16 nmarc)
    {
        SetText(str);
        SetMarc(nmarc);
    }

    void CreteGrafik(quint8 type)// создает интерфейс-панель ответа
    {
        if(isGrag)
            return;// все и так создано


        QHBoxLayout *laut=new QHBoxLayout();
        QCheckBox *checkbox;
        QRadioButton *radiobox;
        QSpinBox *spinboxint;
        QDoubleSpinBox *spinboxreal;
        QLineEdit *lineditt;
        QTextBrowser *broser;

        isGrag=true;


        QTextBrowser *text=new QTextBrowser();
        QSpinBox *spin=new QSpinBox();
        QFrame *frame=new QFrame();

        text->setHtml(Text);
        spin->setMinimum(-99999);
        spin->setMaximum(99999);
        spin->setValue(Marc);

        frame->setStyleSheet("border: 0px");
        spin->setMinimumWidth(80);
        spin->setMaximumHeight(50);
        spin->setAlignment(Qt::AlignCenter);
       // spin->setStyleSheet("border: 2px solid #808090;background-color: #f0f0f0;");
        switch (type) {
        case 0:// радиобатоны
            radiobox=new QRadioButton();
            laut->addWidget(radiobox);
            grafik.type=radiobox;
            break;
        case 1:// чекбоксы
            checkbox=new QCheckBox();
            laut->addWidget(checkbox);
            grafik.type=checkbox;
            break;
        case 2://спинбоксы целого типа
            spinboxint=new QSpinBox();
            //spinboxint->setEnabled(false);
            spinboxint->setMinimumWidth(100);
            spinboxint->setMinimumHeight(20);
            laut->addWidget(spinboxint);
            spinboxint->setMinimum(-900000);
            spinboxint->setMaximum(900000);
            grafik.type=spinboxint;
            break;
        case 3://спинбоксы дробного типа
            spinboxreal=new QDoubleSpinBox();
            spinboxreal->setMinimumWidth(100);
            spinboxreal->setMinimumHeight(20);
            spinboxreal->setMinimum(-900000);
            spinboxreal->setMaximum(900000);
            laut->addWidget(spinboxreal);
            grafik.type=spinboxreal;
            break;
        case 4://однострочные лайны
            lineditt=new QLineEdit();
            lineditt->setText("-----------------");
            lineditt->setMinimumWidth(100);
            lineditt->setMaximumWidth(100);
            lineditt->setMinimumHeight(20);
            laut->addWidget(lineditt);
            grafik.type=lineditt;
            break;
        case 5://мноострочное лайны
            broser=new QTextBrowser();
            broser->setText("--------------------------------------------------------------------------");
            broser->setMinimumWidth(100);
            broser->setMaximumWidth(100);
            broser->setMinimumHeight(50);
            laut->addWidget(broser);
            grafik.type=broser;
            break;
        default:
            break;
        }

        grafik.type->setEnabled(false);

        laut->addWidget(text);
        laut->addWidget(spin);

        text->setReadOnly(false);
        text->setMaximumHeight(50);
        frame->setMaximumHeight(55);
        frame->setMinimumHeight(55);

        frame->setLayout(laut);
        //frame->show();

        grafik.frame=frame;
        grafik.laut=laut;
        grafik.spin=spin;
        grafik.tbrowser=text;

    }

    void DeleteGrafic()
    {
        if(!(isGrag))
            return;// все удалено итака
        isGrag=false;

        //сохраняем результаты
        Text=grafik.tbrowser->toHtml();
        Marc=grafik.spin->value();

        //удаляем виджеты из памяти
        delete grafik.type;
        delete grafik.spin;
        delete grafik.tbrowser;
        delete grafik.laut;
        delete grafik.frame;
    }

    void ReDraw()
    {
        DeleteGrafic();
        CreteGrafik(1);
    }

    QString GetText()
    {
        return Text;
    }

    quint16 GetMark()
    {
        return Marc;
    }
};

#endif // MYOTWET_H
