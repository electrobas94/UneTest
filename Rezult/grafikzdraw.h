#ifndef GRAFIKZDRAW_H
#define GRAFIKZDRAW_H

#include <QWidget>
#include "myprintrezult.h"
#include "myfiles.h"
#include "mylistlink.h"
#include "mysubd.h"

struct rez
{
    MyListLink<MyPrintRezult> *list;
};

namespace Ui {
class GrafikzDraw;
}

class GrafikzDraw : public QWidget
{
    Q_OBJECT

public:
    explicit GrafikzDraw(rez testrez, QWidget *parent = 0);
    ~GrafikzDraw();
    MyListLink<MyPrintRezult> *listrez;

public slots:
    void on_pushButton_2_clicked();

private:
    Ui::GrafikzDraw *ui;
};

#endif // GRAFIKZDRAW_H
