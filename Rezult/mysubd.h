#ifndef MYSUBD_H
#define MYSUBD_H
#include <QStringList>
#include <QDebug>
#include "mysql.h"
#include <QtSql>
#include <mylistlink.h>

struct MyTestList
{
    MyListLink<QString> *tablenames;
    MyListLink<QString> *testnames;
};

class MySUBD
{
private:
    MyTestList testlist;
    bool status=false;//подключено или нет
    MYSQL_RES *res; //таблица выполнения запроса
    //    QString tableTables;//имя таблицы таблиц
    MYSQL_ROW row; // Массив полей текущей строки
    MYSQL MyBase;// се через обращени
    QString host;//
    QString user;
    QString pass; // пароль
    QString dbname; // название базы данных
    qint32 port=0; //  порт. по умолчанию (0=3306)вродекак и на лин и на вин
public:
    MySUBD();
    void SetHost(QString nhost)
    {
        host=nhost;
    }
    void SetUser(QString nuser)
    {
        user=nuser;
    }
    void SetPass(QString npass)
    {
        pass=npass;
    }
    void SetBaseName(QString ndbname)
    {
        dbname=ndbname;
    }
    void SetPortNumer(quint16 nport)
    {
        port=nport;
    }

    bool OpenConect()
    {
        mysql_init(&MyBase);  // Инициализация
        mysql_real_connect(&MyBase,
                           host.toStdString().c_str(),
                           user.toStdString().c_str(),
                           pass.toStdString().c_str(),
                           dbname.toStdString().c_str(),
                           port, NULL, 0); // соединение

        QString tmp=mysql_error(&MyBase);
        if(tmp.count()==0)
        {
            status=true;
            return true;
        }
        qDebug() << "Ошибка подключения" << mysql_error(&MyBase);
        return false;
    }

    void CloseConect()
    {
        mysql_close(&MyBase);
        status=false;
    }

    bool GetStatus()//в каком режиме база
    {
        return status;
    }

    bool RunSQLscript(QString script)//выполняет SQL запрос и вносит результат его выполнения
    {
        if(!(status))// небыло соединения
            return false;

        if (mysql_query(&MyBase, script.toStdString().c_str()) > 0)
        {
            qDebug() << mysql_error(&MyBase);
            return false;
        }
        //запись результата
        res = mysql_store_result(&MyBase);

        return true;
    }

    bool RetTables(QStringList *tablename)//возвращает список таблиц базы
    {
        if(!(RunSQLscript("SHOW TABLES;")))
            return false;
        //
        tablename->clear();

        int num_fields = mysql_num_fields(res); // количество полей
        int num_rows = mysql_num_rows(res); // и количество строк.

        for (int i = 0; i < num_rows; i++) // Вывод таблицы
        {
            row = mysql_fetch_row(res); // получаем строку

            for (int l = 0; l < num_fields; l++)
            {
                tablename->append(row[l]);
            }

        }

        return true;
    }

    bool RetTablesTest(QStringList *tablename)//возвращает список таблиц базы
    {
        if(!(RunSQLscript("SHOW TABLES LIKE 't%';")))
            return false;
        //
        tablename->clear();

        int num_fields = mysql_num_fields(res); // количество полей
        int num_rows = mysql_num_rows(res); // и количество строк.

        for (int i = 0; i < num_rows; i++) // Вывод таблицы
        {
            row = mysql_fetch_row(res); // получаем строку

            for (int l = 0; l < num_fields; l++)
            {
                tablename->append(row[l]);
            }

        }

        return true;
    }

    bool RetTablesRezult(QStringList *tablename)//возвращает список таблиц базы
    {
        if(!(RunSQLscript("SHOW TABLES LIKE 'r%';")))
            return false;
        //
        tablename->clear();

        int num_fields = mysql_num_fields(res); // количество полей
        int num_rows = mysql_num_rows(res); // и количество строк.

        for (int i = 0; i < num_rows; i++) // Вывод таблицы
        {
            row = mysql_fetch_row(res); // получаем строку

            for (int l = 0; l < num_fields; l++)
            {
                tablename->append(row[l]);
            }

        }

        return true;
    }


    bool CreteTableTest(QString tablename)//создание таблицы теста
    {
        return RunSQLscript("CREATE TABLE IF NOT EXISTS `"+tablename+"` ("
                            "`key` INT NOT NULL AUTO_INCREMENT,"
                            "`data` TEXT NULL,"
                            "PRIMARY KEY (`key`));");
    }


    bool ApendDataInTest(QString tablename, QString data)//добавление нового поля в таблицу
    {
//        const char* str=data.toStdString().c_str();
//        QString tmp2="";

//        for(int i=0;;i++)
//        {
//            if(str[i]=='\0')
//                break;
//            if(str[i]=='\'')
//                tmp2+='\\';
//            tmp2+=str[i];
//        }
        for(int i=0;i<data.count();i++)
        {
            if(data[i]=='\'')
            {
                data.insert(i,'\\');
                i++;
            }
        }
        return RunSQLscript("INSERT INTO `"+tablename+"` (`data`) VALUES ('"+data+"');");//
    }

    QString RetFirstItem(QString tablename, quint16 num)//возвращает первую найденую строку
    {
        QString key=QString::number(num);

        if(!(RunSQLscript("SELECT `data` FROM "+tablename+" where `key` = "+key+";")))
            return "FaLsE--1";

        row = mysql_fetch_row(res); // получаем строку
        return row[0];// список таблиц в стринг лист будет
    }

    bool GetTest()// строит список имени тестов и список имени тестов с одинаковыми номерами
    {
        if(!(RunSQLscript("SHOW TABLES LIKE 't%';")))
            return false;
        //
        //tablename->clear();
        testlist.tablenames->Clear();
        testlist.testnames->Clear();

        int num_fields = mysql_num_fields(res); // количество полей
        int num_rows = mysql_num_rows(res); // и количество строк.

        for (int i = 0; i < num_rows; i++) // Вывод таблицы
        {
            row = mysql_fetch_row(res); // получаем строку

            for (int l = 0; l < num_fields; l++)
            {
                QString tmp=row[l];
                testlist.tablenames->Add(&tmp);
            }

        }

        testlist.tablenames->First();
        for(int i=0; i<testlist.tablenames->Count();i++)
        {
            QString a=RetFirstItem(*(testlist.tablenames->Current()),1);
            testlist.testnames->Add(&a);
            testlist.tablenames->Next();
        }

        return true;
    }

    QString RetTableName(int index)//возвращает имя таблицы теста по индексу в списке
    {
        testlist.tablenames->SetCurrentToIndex(index);
        return *(testlist.tablenames->Current());
    }

    QString RetTestName(int index)//возвращает имя  теста по индексу в списке
    {
        testlist.testnames->SetCurrentToIndex(index);
        return *(testlist.testnames->Current());
    }

    void RetTableNames(QStringList &list)//возвращает список имен таблиц тестов
    {
        testlist.tablenames->First();
        for(int i=0;i<testlist.tablenames->Count();i++)
        {
            list.append(*(testlist.tablenames->Current()));
            testlist.tablenames->Next();
        }
    }

    void RetTestNames(QStringList &list)// возвращает список тестов которые есть в БД на данный момент
    {
        testlist.testnames->First();
        for(int i=0;i<testlist.testnames->Count();i++)
        {
            list.append(*(testlist.testnames->Current()));
            testlist.testnames->Next();
        }
    }

    bool DelTable(QString tablename)
    {
        return RunSQLscript("DROP TABLE `"+tablename+"`;");
    }
};

#endif // MYSUBD_H
