#include "form.h"
#include "ui_form.h"
#include "optionotwet.h"
#include "mylistlink.h"
#include "myfiles.h"
#include <QFileDialog>
#include "otwetkey.h"//редактор ключей для теста
#include <QDesktopWidget>



OtwetKey *OtwKey;

//MyListLink<OptionOtwet> *Opitem;// список интервалов

Form::Form(quint16 count,MyTest *test, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form),
    testCur(test)
{
    ui->setupUi(this);
    OtwKey=new OtwetKey();
    OtwKey->voprosCount=count;

    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());

    ui->label_4->setText("<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">Текущий тест: "+
                         test->GetTestName()+
                         "</span></p></body></html>");
    if(test->pravils->Count()==0)
        return;

    test->pravils->First();

    for(int i=0;i<test->pravils->Count();i++)//загрузка правил
    {
        interval *Opitem=new interval();
        Opitem->countv=test->pravils->Current()->voprosnums->Count();


        // создаем список вопросов действия
        Opitem->CreteList(test->pravils->Current()->voprosnums->Count());

        test->pravils->Current()->voprosnums->First();
        for(int j=0;j<test->pravils->Current()->voprosnums->Count();j++)
        {
            Opitem->listvop[j]=*(test->pravils->Current()->voprosnums->Current());
            test->pravils->Current()->voprosnums->Next();
        }

        // intervals
        test->pravils->Current()->intervals->First();
        for(int j=0;j<test->pravils->Current()->intervals->Count();j++)
        {
            OptionOtwet *tmp2=new OptionOtwet();

            tmp2->SetDo(test->pravils->Current()->intervals->Current()->doo);
            tmp2->SetOt(test->pravils->Current()->intervals->Current()->ot);
            tmp2->SetLine(test->pravils->Current()->intervals->Current()->line);
            tmp2->SetText(test->pravils->Current()->intervals->Current()->text);
            tmp2->SetType(test->pravils->Current()->intervals->Current()->type);
            tmp2->SetAttrib(test->pravils->Current()->intervals->Current()->attrib);

            Opitem->Opitem->Add(tmp2);
            tmp2->Hide();
            ui->verticalLayout_4->addWidget(tmp2->Widget());// привязываем к выводу


            test->pravils->Current()->intervals->Next();
        }
        //intervals


        ui->comboBox->addItem("Правило "+QString::number(ui->comboBox->count()+1));
        OtwKey->PrawItems->Add(Opitem);
        //ui->comboBox->setCurrentIndex(ui->comboBox->count()-1);

        test->pravils->Next();

    }

    test->pravils->First();

    ui->listWidget->clear();
    ui->listWidget_2->clear();

    for(quint16 ii=0;ii<count;ii++)
    {
        test->pravils->Current()->voprosnums->First();

        for(int j=0;j<test->pravils->Current()->voprosnums->Count();j++)
        {
            if(*(test->pravils->Current()->voprosnums->Current())==ii)
            {
                ui->listWidget->addItem("Вопрос "+QString::number(ii+1));
                goto Next;// к новой итерации главного цикла
            }

            test->pravils->Current()->voprosnums->Next();
        }

        ui->listWidget_2->addItem("Вопрос "+QString::number(ii+1));
Next:;
    }

    OtwKey->PrawItems->First();
    OtwKey->PrawItems->Current()->ShowAll();
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_7_clicked()//добавить интервал
{
    if(OtwKey->PrawItems->Count()==0)
        return;

    OptionOtwet *OpOtw=new OptionOtwet();

    OtwKey->PrawItems->Current()->Opitem->Add(OpOtw);

    //Opitem->Add(OpOtw);
    ui->verticalLayout_4->addWidget(OpOtw->Widget());
    OpOtw->Show();
}

void Form::on_pushButton_8_clicked()//удалить интервал
{
    if(OtwKey->PrawItems->Count()==0)
        return;
    OtwKey->PrawItems->Current()->Opitem->DeleteLastElem();
}

void Form::on_pushButton_10_clicked()// кнопка сохранения в файл
{
    close();
}

void Form::on_pushButton_5_clicked()//добавить правило
{
    interval *Opitem=new interval();
    ui->comboBox->addItem("Правило "+QString::number(ui->comboBox->count()+1));
    OtwKey->PrawItems->Add(Opitem);
    ui->comboBox->setCurrentIndex(ui->comboBox->count()-1);
    OtwKey->PrawItems->Last();

    ui->listWidget->clear();
    ui->listWidget_2->clear();

    for(int i=0;i<OtwKey->voprosCount;i++)
    {
        ui->listWidget_2->addItem("Вопрос "+QString::number(i+1));
    }

}

void Form::on_pushButton_6_clicked()//удалить правило
{
    if(OtwKey->PrawItems->Count()==0)
        return;
    OtwKey->PrawItems->Current()->HideAll();//тут  возможна утечка
    OtwKey->PrawItems->Current()->Opitem->Clear();
    OtwKey->PrawItems->DeleteCurrentElem();
    ui->comboBox->removeItem(ui->comboBox->count()-1);
}

void Form::on_listWidget_2_currentRowChanged(int currentRow)
{

}

void Form::on_pushButton_3_clicked()
{
    ui->listWidget_2->clear();
    ui->listWidget->clear();

    for(int i=0;i<OtwKey->voprosCount;i++)
    {
        ui->listWidget_2->addItem("Вопрос "+QString::number(i+1));
    }
}

void Form::on_pushButton_2_clicked()
{
    ui->listWidget_2->clear();
    ui->listWidget->clear();

    for(int i=0;i<OtwKey->voprosCount;i++)
    {
        ui->listWidget->addItem("Вопрос "+QString::number(i+1));
    }
}

void Form::on_pushButton_4_clicked()
{
    if(ui->listWidget_2->count()==0 or ui->listWidget_2->currentRow()<0 or ui->listWidget_2->currentRow()>ui->listWidget_2->count())
        return;
    QString tmp=ui->listWidget_2->currentItem()->text();
    delete ui->listWidget_2->currentItem();
    ui->listWidget->addItem(tmp);

    ui->listWidget->sortItems();
}

void Form::on_pushButton_clicked()
{
    if(ui->listWidget->count()==0  or ui->listWidget->currentRow()<0 or ui->listWidget->currentRow()>ui->listWidget->count())
        return;
    QString tmp=ui->listWidget->currentItem()->text();
    delete ui->listWidget->currentItem();
    ui->listWidget_2->addItem(tmp);

    ui->listWidget_2->sortItems();
}

void Form::on_listWidget_2_clicked(const QModelIndex &index)
{
    if(testCur->VoprosList->Count()==0 or ui->listWidget_2->count()==0)
        return;


    QStringList list2 = ui->listWidget_2->currentItem()->text().split(" ");

    QString tmp=list2.last();
    //tmp=tmp.right(1);

    testCur->VoprosList->SetCurrentToIndex(tmp.toInt()-1);

    ui->textEdit->setText(testCur->VoprosList->Current()->GetText());

    QImage *image=testCur->VoprosList->Current()->GetImage();

    ui->label_3->setPixmap( QPixmap::fromImage( *image ) );
    if(image->isNull())
    {
        ui->label_3->setMaximumWidth( 188 );
        ui->label_3->setMinimumWidth( 188 );
        return;
    }

    ui->label_3->setMaximumWidth( (image->width()*188) / image->height() );
    ui->label_3->setMinimumWidth( (image->width()*188) / image->height() );

}

void Form::on_listWidget_clicked(const QModelIndex &index)
{
    if(testCur->VoprosList->Count()==0 or ui->listWidget->count()==0)
        return;

    QStringList list2 = ui->listWidget->currentItem()->text().split(" ");

    QString tmp=list2.last();

    testCur->VoprosList->SetCurrentToIndex(tmp.toInt()-1);

    ui->textEdit->setText(testCur->VoprosList->Current()->GetText());

    QImage *image=testCur->VoprosList->Current()->GetImage();

    ui->label_3->setPixmap( QPixmap::fromImage( *image ) );
    if(image->isNull())
    {
        ui->label_3->setMaximumWidth( 188 );
        ui->label_3->setMinimumWidth( 188 );
        return;
    }

    ui->label_3->setMaximumWidth( (image->width()*188) / image->height() );
    ui->label_3->setMinimumWidth( (image->width()*188) / image->height() );

}

void Form::on_comboBox_currentIndexChanged(int index)// сохраняет правило при измененении
{
    if(ui->comboBox->count()==0 or OtwKey->PrawItems->Count()==0)// нет правил
        return;

    OtwKey->SaveVopros(ui->listWidget->count());//создаем масив для вопросов

    for(int i=0;i<ui->listWidget->count();i++)
    {
        // нужно вырезать последнее число(проблема разное колво символов)
        QStringList list2 = ui->listWidget->item(i)->text().split(" ");

        QString tmp=list2.last();
        //tmp=tmp.right(1);

        OtwKey->PrawItems->Current()->listvop[i]=tmp.toInt()-1;
    }

    OtwKey->PrawItems->Current()->HideAll();
    OtwKey->PrawItems->SetCurrentToIndex(index);// новое текущее
    OtwKey->PrawItems->Current()->ShowAll();

    // заполняем новыми значениями
    ui->listWidget->clear();
    ui->listWidget_2->clear();

    for(int i=0;i<OtwKey->voprosCount;i++)
    {
        for(int j=0;j<OtwKey->PrawItems->Current()->countv;j++)
        {
            if(OtwKey->PrawItems->Current()->listvop[j]==i)
            {
                ui->listWidget->addItem("Вопрос "+QString::number(i+1));
                goto Next;// к новой итерации главного цикла
            }
        }

        ui->listWidget_2->addItem("Вопрос "+QString::number(i+1));
Next:;
    }
}

void Form::on_comboBox_activated(int index)
{

}

void Form::on_label_3_linkActivated(const QString &link)
{

}

void Form::on_pushButton_9_clicked()//принять изменения(сохраняет в текущий тест)
{

    if(ui->comboBox->count()==0 || OtwKey->PrawItems->Count()==0)// нет правил
    {
    }
    else
    {

        OtwKey->SaveVopros(ui->listWidget->count());//создаем масив для вопросов

        for(int i=0;i<ui->listWidget->count();i++)
        {
            // нужно вырезать последнее число(проблема разное колво символов)
            QStringList list2 = ui->listWidget->item(i)->text().split(" ");

            QString tmp=list2.last();
            //tmp=tmp.right(1);

            OtwKey->PrawItems->Current()->listvop[i]=tmp.toInt()-1;
        }

    }




    OtwKey->PrawItems->First();
    testCur->pravils->Clear();

    for(int i=0;i<OtwKey->PrawItems->Count();i++)// проход по правилам
    {
        prawilo *tmp=new prawilo();

        for(int j=0;j<OtwKey->PrawItems->Current()->countv;j++)// вопросом правила
        {
            tmp->voprosnums->Add(&(OtwKey->PrawItems->Current()->listvop[j]));
        }

        OtwKey->PrawItems->Current()->Opitem->First();

        for(int j=0;j<OtwKey->PrawItems->Current()->Opitem->Count();j++)//загрузка интервалов
        {
            intervaL *tmp2=new intervaL();

            tmp2->doo=OtwKey->PrawItems->Current()->Opitem->Current()->GetDo();
            tmp2->ot=OtwKey->PrawItems->Current()->Opitem->Current()->GetOt();
            tmp2->line=OtwKey->PrawItems->Current()->Opitem->Current()->GetLine();
            tmp2->text=OtwKey->PrawItems->Current()->Opitem->Current()->GetText();
            tmp2->type=OtwKey->PrawItems->Current()->Opitem->Current()->GetType();
            tmp2->attrib=OtwKey->PrawItems->Current()->Opitem->Current()->GetAttrib();

            tmp->intervals->Add(tmp2);
            OtwKey->PrawItems->Current()->Opitem->Next();
        }
        testCur->pravils->Add(tmp);

        OtwKey->PrawItems->Next();
    }
    close();
}

void Form::on_comboBox_activated(const QString &arg1)
{

}

void Form::on_pushButton_13_clicked()
{
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    OtwKey->OpenInFile(ui->comboBox,ui->verticalLayout_4, ui->listWidget, ui->listWidget_2);

}
