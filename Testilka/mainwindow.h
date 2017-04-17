#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_action_2_triggered();

    void on_pushButton_5_clicked();

    void on_pushButton_pressed();

    void on_pushButtonNew_clicked();

    void on_listWidget_clicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_tabWidget_2_currentChanged(int index);

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_checkBox_clicked();

    void on_checkBox_clicked(bool checked);

    void on_pushButton_12_clicked();

    void on_pushAddVop_clicked();

    void on_pushAddOtw_clicked();

    void on_textBrowser_2_selectionChanged();

    void on_pushButton_13_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_17_clicked();

    void on_spinBox_2_valueChanged(int arg1);

    void on_pushButton_19_clicked();

    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_pushButton_21_clicked();

    void on_buttonBox_accepted();

    void on_pushButton_25_clicked();

    void on_pushButton_23_clicked();

    void on_pushRemVop_clicked();

    void on_listWidget_itemSelectionChanged();

    void on_pushRemOtw_clicked();

    void on_tabWidget_2_tabCloseRequested(int index);

    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_32_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_33_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_listWidget_currentRowChanged(int currentRow);

    void on_centralWidget_destroyed();

    void on_pushButton_35_clicked();

    void on_comboBox_2_currentIndexChanged(int index);

    void on_comboBox_activated(const QString &arg1);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_activated(int index);

public:
    Ui::MainWindow *ui;

public slots:

    void replyFinished();
    void replyFinishedForPost();

    void onTimeout();
};

#endif // MAINWINDOW_H
