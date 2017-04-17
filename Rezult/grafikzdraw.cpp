#include "grafikzdraw.h"
#include "ui_grafikzdraw.h"

#include <QMessageBox>


//MyTest *testt;

GrafikzDraw::GrafikzDraw(rez testrez, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GrafikzDraw)
{
    ui->setupUi(this);

    //testt=test;

    ui->pushButton_2->hide();

    listrez=testrez.list;
}

GrafikzDraw::~GrafikzDraw()
{
    delete ui;
}

//void GrafikzDraw::on_pushButton_clicked()
//{
//    close();
//}

void GrafikzDraw::on_pushButton_2_clicked()
{
    ui->listWidget->clear();
    if(listrez->Count()==0)
    {
        close();
        return;
    }

    int max=listrez->First()->val->text().toInt();

    for(int i=0;i<listrez->Count();i++)
    {
        if ( max<listrez->Current()->val->text().toInt() )
            max=listrez->Current()->val->text().toInt();
        listrez->Next();
    }
    double koff=800/max;

    struct MyPoint
    {
        int x;
        int y;

        MyPoint():x(0),y(0)
        {}
    };

    MyPoint BegLine;
    MyPoint EndLine;

    QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView);
    QPen pen2(Qt::darkGreen, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);//
    QPainterPath path;
    QFont font("Times", 15, false);

    listrez->First();
    bool flag=false; // check for invalid grafik
int num=1;
    for(int i=0;i<listrez->Count();i++)
    {
        if(listrez->Current()->Widget()==NULL)
        {
            listrez->Next();
            continue;
        }
        quint16 tmm=listrez->Current()->attrib;
        tmm/=10;
        if ( tmm%10 ==0 )
        {
            listrez->Next();
            continue;
        }

        flag=true;

        EndLine.y+=40;
        EndLine.x=listrez->Current()->val->text().toInt()*koff;

        scene->addLine(BegLine.x, BegLine.y, EndLine.x, EndLine.y, pen2);

        BegLine.x=EndLine.x;
        BegLine.y=EndLine.y;


        path.addText(EndLine.x, EndLine.y, font,  "     №"+QString::number(num)+" - "+listrez->Current()->val->text() );

        ui->listWidget->addItem("№"+QString::number(num)+" - "+listrez->Current()->header->text());

        scene->addPath(path, QPen(QBrush(Qt::black), 1), QBrush(Qt::black));

    num++;
        listrez->Next();
    }


    scene->addLine(BegLine.x, BegLine.y, 0, EndLine.y+40, pen2);



    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing);
    ui->graphicsView->setScene(scene);//Добавляем в наш GraphicsView нарисованную сцену.

    if ( !( flag ) )
    {
        QMessageBox msgBox;
        msgBox.setText("Данный тест не содержит графической информации");
        msgBox.exec();

        close();
    }
}
