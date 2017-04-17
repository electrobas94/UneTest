#include "mycrypto.h"

CryptKod MyCrypto::RandBS()// рандомим шаг  праход
{
    srand(time(NULL));
    CryptKod tmp;
    tmp.BeginKey=rand();// устанавлвает радомый ключ
    tmp.SteepKey=rand();
    //шифруем все как положенно=)
    tmp.BeginKey=SecretCrypt(tmp.BeginKey,MAGIK_1);
    tmp.SteepKey=SecretCrypt(tmp.SteepKey,MAGIK_2);
    //указываем новые значения
    BeginKey=tmp.BeginKey;
    SteepKey=tmp.SteepKey;

    return tmp;
}

quint32 MyCrypto::SecretCrypt(quint32 data, bool flag)// выполяняет как шифровку так и дешифровку=)))
{
    if(flag)//шифруем 2 магическим
        data=data^MagicValue2;
    else//шифруем 1 магическим
        data=data^MagicValue;

    return data;
}

QString MyCrypto::Crypt(QString data)
{
    quint32 lenstr=data.length();// получаем длинну строки
    //std::string a=data.toStdString();
    for(int i=0;i<lenstr;i++)
    {
        //data[i]=data.at(i).unicode()^Key[CalcIndexKey(i)];//CalcIndexKey(i)
    }
    return data;
}

quint16 MyCrypto::CalcIndexKey(qint32 factor)
{
    CryptKod tmp;
    tmp.BeginKey=SecretCrypt(BeginKey,MAGIK_1);
    tmp.SteepKey=SecretCrypt(SteepKey,MAGIK_2);
    tmp.BeginKey%=512;// получили начало отсчета
    tmp.SteepKey%=512;// отбросили лшнюю часть
    quint64 index=tmp.BeginKey+tmp.SteepKey*factor;
    index%=512;// обрасываем часть вышедшую за границы ключа и начинаем с начала

    return index;
}
