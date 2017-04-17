#ifndef MYTREAD_H
#define MYTREAD_H
// Класс для запуска потоков
#include <QThread>
//#include "myadmin.h"

class MyTread : public QThread
{
    Q_OBJECT

public:
    MyTread(QObject *parent, quint8 nfunk)
    {
        //Admin=AdminN;
        nF=nfunk;
    }
    void run();
private:
    //MyAdmin *Admin;
    quint8 nF;// хранит в себе номер необходимой функции
};


#endif // MYTREAD_H
