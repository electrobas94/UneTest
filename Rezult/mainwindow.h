#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void ActivBdRow(int currentRow);
    void ActivFRow(int currentRow);
    ~MainWindow();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_9_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_listWidget_currentRowChanged(int currentRow);

    void on_pushButton_7_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_6_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_activated(const QString &arg1);

    void on_listWidget_2_currentRowChanged(int currentRow);

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_2_clicked();

    void on_listWidget_3_currentRowChanged(int currentRow);

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_clicked();

    void on_listWidget_activated(const QModelIndex &index);

    void on_listWidget_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
