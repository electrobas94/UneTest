#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "mytest.h"


namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(quint16 count , MyTest *test, QWidget *parent = 0);
    ~Form();
    quint16 voprosCount;
    MyTest *testCur;
private slots:
    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_listWidget_2_currentRowChanged(int currentRow);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_listWidget_2_clicked(const QModelIndex &index);

    void on_listWidget_clicked(const QModelIndex &index);

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_activated(int index);

    void on_label_3_linkActivated(const QString &link);

    void on_pushButton_9_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_13_clicked();

private:
    Ui::Form *ui;
};

#endif // FORM_H
