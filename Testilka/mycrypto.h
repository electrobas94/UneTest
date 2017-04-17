#ifndef MYCRYPTO_H
#define MYCRYPTO_H
#define MAGIK_1 false
#define MAGIK_2 true
#include <QString>
#include <time.h>
#include <stdlib.h>

struct CryptKod
{
    quint32 BeginKey=0;// начала отсчета по ключу
    quint32 SteepKey=0;
};

class MyCrypto
{
private:
#include "KeyKripto.h"// тут ключ, большой и толстый=))
    quint64 MagicValue=5074383972495287069;// число для быстрого шифрования блока первичного ключа
    quint64 MagicValue2=960980975461517416;

    quint32 BeginKey=0;// начала отсчета по ключу
    quint32 SteepKey=1;// шаг прохода по ключу
    quint32 SecretCrypt(quint32 data, bool flag=MAGIK_1);// втутрення функция для шифрования шага  начала
    quint16 CalcIndexKey(qint32 factor);// функция вычисления индекса ключа при имеющемся множителе
public:
    MyCrypto()
    {
    }
    void SetBeginKey(quint32 begKey)//устаовить начала отсчета по ключу(передается шифр)
    {
        BeginKey=begKey;
    }

    void SetSteepKey(quint32 stepKey)//установить шаг прохода
    {
        SteepKey=stepKey;
    }

    void SetKey(CryptKod nkey)
    {
        SetBeginKey(nkey.BeginKey);
        SetSteepKey(nkey.SteepKey);
    }

    CryptKod RandBS();//рандомит начала отсчета и шаг прохода, затаем шифрует простым методом эту штуку и выдает в защифрованном виде назад
    QString Crypt(QString data);// и шифрует и дешфрует в двустороннем порядке
};

#endif // MYCRYPTO_H
