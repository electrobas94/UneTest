#ifndef MYPRINTREZULT_H
#define MYPRINTREZULT_H
#include <QPlainTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QLayout>

class MyPrintRezult
{
public:
    quint16 attrib;
    QPlainTextEdit *text; //описание поля
    QLabel * header;//заголовок интервала
    QLineEdit *val; // бал
    QWidget *frame;
    QHBoxLayout *lautH;
    QVBoxLayout *lautV;
    QFrame *wiget;
    QWidget *hspacer;

    void CreteGafick(quint16 type)
    {
        frame=new QFrame();
        lautH=new QHBoxLayout();
        lautV=new QVBoxLayout();

        text=new QPlainTextEdit();
        header=new QLabel();

        val =new QLineEdit();

        wiget=new QFrame();
        hspacer=new QWidget();

        lautH->addWidget(header);
        lautH->addWidget(val);
        lautH->addWidget(hspacer);

        wiget->setLayout(lautH);

        quint16 tmp , tmp2;
        tmp=attrib;
        tmp/=100;

        tmp2=tmp;//%=10;// показ текста
        tmp%=10;

        tmp2/=10;
        tmp2%=10;
        if(tmp2==1)
            lautV->addWidget(wiget);
        if(tmp==1)
            lautV->addWidget(text);

        frame->setLayout(lautV);

        // settings
        //val->show();
        val->setMinimumWidth(40);
        header->setMinimumWidth(100);

        val->setMaximumWidth(40);
        header->setMaximumWidth(250);
        header->setMaximumHeight(33);
        header->setMinimumWidth(400);
        wiget->setStyleSheet("border: 2px solid #808090;");
        text->setStyleSheet("border: 2px solid #808090;");
        frame->setStyleSheet("border: 0px solid #808090;");

        hspacer->setStyleSheet("border: 0px solid #808090;");
        hspacer->setMinimumWidth(  400);//местто спасера
        text->setMinimumHeight(70);
        //hspacer->setSizePolicy(QSizePolicy::Maximum);

//        int tmp=0;
//        tmp=attrib%10;
//        if(tmp==1 || tmp==3)
//             frame->show();
    }

public:
    MyPrintRezult(quint16 type)
    {
        attrib=type;
        CreteGafick(type);
    }

    void SetText(QString textt)
    {
        text->setPlainText(textt);
    }

    void SetHead(QString textt)
    {
        header->setText(textt);
    }

    void SetPoint(int vall)
    {
        val->setText(QString::number(vall));
    }
    ~MyPrintRezult()
    {
        delete text; //описание поля
        delete header;//заголовок интервала
        delete hspacer;
        delete val; // бал


        delete lautH;
        delete wiget;
        delete lautV;

        delete frame;
    }

    QWidget *Widget()
    {
        return frame;
    }
};

#endif // MYPRINTREZULT_H
