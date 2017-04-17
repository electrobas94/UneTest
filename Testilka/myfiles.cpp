#include "myfiles.h"

MyFiles::MyFiles()
{
    out.setDevice(&CurrentFile);
    out.setVersion(QDataStream::Qt_5_1);
}

bool MyFiles::OpenFile()
{
    if(CurrentFile.isOpen())
        return false;//файл уже открыт

    if(!(CurrentFile.exists()))
        return false;// файла нету

    return CurrentFile.open(QIODevice::ReadWrite);// открываем для чения записи
}


bool MyFiles::NewFile()
{
    if(CurrentFile.isOpen())
        return false;//файл уже открыт

    if((CurrentFile.exists()))
    {
        DeleteFile();
        return CurrentFile.open(QIODevice::ReadWrite);//создаем файл
    }

    return CurrentFile.open(QIODevice::ReadWrite);//создаем файл
}

bool MyFiles::CloseFile()// закрываем файл
{
    CurrentFile.close();
}

void MyFiles::SetFileName(QString fileName)// указываем имя файла
{
    CurrentFile.setFileName(fileName);
}

bool MyFiles::DeleteFile()
{
    CloseFile();//закрываем файла если вдруг был открыт

    if(!(CurrentFile.exists()))
        return false;// файла и а уже нету

    return CurrentFile.remove();
}

bool MyFiles::ClearFile()
{
    if(!(CurrentFile.exists()))
        return false;// файла нету

    if(!(DeleteFile()))
        return false;// не удаляется файл

    return NewFile();// не создался файл заново
}

bool MyFiles::Append(QString data)
{
    if(!(CurrentFile.isOpen()))
        return false;//файл не открыт

    if(!(CurrentFile.exists()))
        return false;// файла нету

    out << data;// вносим данные в файл

    return true;
}

bool MyFiles::Append(quint16 data)
{
    if(!(CurrentFile.isOpen()))
        return false;//файл не открыт

    if(!(CurrentFile.exists()))
        return false;// файла нету

    out << data;// вносим данные в файл

    return true;
}

bool MyFiles::Append(double data)
{
    if(!(CurrentFile.isOpen()))
        return false;//файл не открыт

    if(!(CurrentFile.exists()))
        return false;// файла нету

    out << data;// вносим данные в файл

    return true;
}

bool MyFiles::Append(qint32 data)
{
    if(!(CurrentFile.isOpen()))
        return false;//файл не открыт

    if(!(CurrentFile.exists()))
        return false;// файла нету

    out << data;// вносим данные в файл

    return true;
}

bool MyFiles::Append(quint32 data)
{
    if(!(CurrentFile.isOpen()))
        return false;//файл не открыт

    if(!(CurrentFile.exists()))
        return false;// файла нету

    out << data;// вносим данные в файл

    return true;
}

bool MyFiles::Append(quint8 data)
{
    if(!(CurrentFile.isOpen()))
        return false;//файл не открыт

    if(!(CurrentFile.exists()))
        return false;// файла нету

    out << data;// вносим данные в файл

    return true;
}

bool MyFiles::Append(QImage &data)
{
    if(!(CurrentFile.isOpen()))
        return false;//файл не открыт

    if(!(CurrentFile.exists()))
        return false;// файла нету

    //out << data;// вносим данные в файл

    return true;
}

bool MyFiles::ReadDataBlock(QString &data)
{
    if(!(CurrentFile.isOpen()))
        return false;//файл не открыт

    if(!(CurrentFile.exists()))
        return false;// файла нету

    out >> data;// вносим данные в файл

    return true;
}

bool MyFiles::ReadDataBlock(qint32 &data)
{
    if(!(CurrentFile.isOpen()))
        return false;//файл не открыт

    if(!(CurrentFile.exists()))
        return false;// файла нету

    out >> data;// вносим данные в файл

    return true;
}

bool MyFiles::ReadDataBlock(double &data)
{
    if(!(CurrentFile.isOpen()))
        return false;//файл не открыт

    if(!(CurrentFile.exists()))
        return false;// файла нету

    out >> data;// вносим данные в файл

    return true;
}

bool MyFiles::ReadDataBlock(quint32 &data)
{
    if(!(CurrentFile.isOpen()))
        return false;//файл не открыт

    if(!(CurrentFile.exists()))
        return false;// файла нету

    out >> data;// вносим данные в файл

    return true;
}

bool MyFiles::ReadDataBlock(quint8 &data)
{
    if(!(CurrentFile.isOpen()))
        return false;//файл не открыт

    if(!(CurrentFile.exists()))
        return false;// файла нету

    out >> data;// вносим данные в файл

    return true;
}
//
bool MyFiles::ReadDataBlock(quint16 &data)
{
    if(!(CurrentFile.isOpen()))
        return false;//файл не открыт

    if(!(CurrentFile.exists()))
        return false;// файла нету

    out >> data;// вносим данные в файл

    return true;
}

bool MyFiles::ReadDataBlock(QImage &data)
{
    if(!(CurrentFile.isOpen()))
        return false;//файл не открыт

    if(!(CurrentFile.exists()))
        return false;// файла нету



    QByteArray barray;

    out >> barray;// вносим данные в файл
     data.loadFromData(barray, "PNG");




    return true;
}
