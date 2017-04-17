#ifndef MYFILES_H
#define MYFILES_H
#include <QString>
#include <QFile>
#include <QDataStream>

class MyFiles
{
private:
    QFile CurrentFile;// непосредственно работаем с файлом
    QDataStream out;
public:
    MyFiles();
    void SetFileName(QString fileName);// уставновка имя файла с которым работаем
    bool OpenFile();// открываем файлик
    bool CloseFile();// закрываем файлик
    bool NewFile();// создаем новый файл, если это возможно
    bool DelFile();//удаляет созланный файл
    bool ClearFile();// очистка файла по меаду удаления и пересоздания
    bool Append(QString data);// дописываем блок данных в файл
    bool Append(qint32 data);
    bool Append(quint32 data);
    bool Append(quint16 data);
    bool Append(quint8 data);
    bool Append(double data);
    bool Append(QImage &data);

    bool ReadDataBlock(QString &data);// счтываем блок данных из файла
    bool ReadDataBlock(qint32 &data);
    bool ReadDataBlock(quint32 &data);
    bool ReadDataBlock(quint16 &data);
    bool ReadDataBlock(quint8 &data);
    bool ReadDataBlock(double &data);
    bool ReadDataBlock(QImage &data);
};

#endif // MYFILES_H
