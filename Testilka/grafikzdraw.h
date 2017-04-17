#ifndef GRAFIKZDRAW_H
#define GRAFIKZDRAW_H
#include "mytest.h"
#include <QWidget>

namespace Ui {
class GrafikzDraw;
}

class GrafikzDraw : public QWidget
{
    Q_OBJECT

public:
    explicit GrafikzDraw(MyTest *test, QWidget *parent = 0);
    ~GrafikzDraw();

public slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:

    Ui::GrafikzDraw *ui;
};

#endif // GRAFIKZDRAW_H
