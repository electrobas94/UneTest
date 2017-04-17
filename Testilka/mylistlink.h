#ifndef MYLISTLINK_H
#define MYLISTLINK_H
#include <QString>

#define  COPY_MODE true // режим работы сиска (коирование или связи)
#define  LINK_MODE false

template <class MyType>
class MyListLink//шаблонный класс двунаправленного динамического списка
{
private:
    class MyElemListLink//класс одного элемента динамического списка и используется только в нем
    {
    public:
        MyType *elem;
        MyElemListLink *Next;
        MyElemListLink *Prev;

        MyElemListLink()
        {
            elem=NULL;
            Next=NULL;
            Prev=NULL;
        }

        ~MyElemListLink()
        {
            //delete elem;// удаляем и сам элемент данных
        }
    };

    bool flag;// метод внесения новх записей в список(1 - создает копию, 0 -вносит только адресс)
    quint32 count;// поля хранящие количество записей
    MyElemListLink *beginElem;// начальный элемент списка, о его и идет отсчет, сам постоянно является
    //  пустым и не хранит в себе данные
    MyElemListLink *last;// хранит в себе последний добавленый элемент если список не пустой,
    //служит для дoбавления новых элементов в конец списка.
    MyElemListLink *current;// текущий элемент, элемент на которым станвился проход по списку

public:
    void SetType(bool flag1)// установка для указания режима работы списка
    {
        flag=flag1;
    }

    MyListLink(bool flag1)
    {
        beginElem=new MyElemListLink();
        last=beginElem;
        current=NULL;
        flag=flag1;//указываем метод внесения записей
        count=0;
    }
    void Add(MyType *Element)// добавляет новый элемент в конец списка
    {
        last->Next=new MyElemListLink();//создаем новый элемент
        last->Next->Prev=last;// устанавливаем связь

        last=last->Next;

        if(flag)// если флаг установлен в 1, то внесение данных идет по методу опирования
        {
            last->elem=new MyType();
            MyType *tmp=last->elem;//что бы не ошибится//
            *tmp=*Element;
        }
        else// иначе вносятся адреса, но не сами данные
        {
            last->elem=Element;
        }

        if(count==0)
            current=beginElem->Next;// активируем текущий элемент первым элементом списка

        count++;// счетчик элементов
    }

    MyType *First()// возвращает первый элемент, если его нет то NULL, текущий элемент становится первым
    {
        if(count==0)//если список пустой
            return NULL;

        current=beginElem->Next;//устанавливаем первый элемент текущим
        return beginElem->Next->elem;
    }

    MyType *Last()// возвращает первый элемент, если его нет то NULL,  текущий элемент становится последним
    {
        if(count==0)//если список пустой
            return NULL;

        current=last;// последний становится текущим
        return last->elem;
    }

    MyType *Next()//Возвращает следующий элемент если он есть(иначе NULL), Изменяет положение текущего элемента списка
    {
        if(count==0)//если список пустой
            return NULL;

        if(current->Next==NULL)// если следующего элемента нету
            return NULL;

        current=current->Next;//изменяем теущий элемент
        return current->elem;
    }

    MyType *Prev()//Возвращает предидущий элемент если он есть(иначе NULL), Изменяет положение текущего элемента списка
    {
        if(count==0)//если список пустой
            return NULL;

        if(current->Prev==NULL)// если следующего элемента нету
            return NULL;

        current=current->Prev;//изменяем теущий элемент
        return current->elem;
    }

    MyType *Current()//  Возвращает текущий элемент
    {
        if(count==0)//если список пустой
            return NULL;

        return current->elem;
    }

    qint32 Count()// возвращает кол-во элементов
    {
        return count;
    }

    void Clear()// очистка списка
    {
        if(count==0)
            return;

        Last();

        quint16 tmp=count;// ибо количество изменяется в цикле

        for(int i=0;i<tmp;i++)
        {
            DeleteCurrentElem();
        }
    }

    void SetCurrentElem(MyType *Element)// добавляет новый элемент в конец списка
    {
        if(count==0)
            return;

        if(flag)// если флаг установлен в 1, то внесение данных идет по методу опирования
        {
            current->elem=new MyType();
            MyType *tmp=current->elem;//что бы не ошибится//
            *tmp=*Element;
        }
        else// иначе вносятся адреса, но не сами данные
        {
            current->elem=Element;
        }
    }

    void SetFirstElem(MyType *Element)// установка(замена элемента)
    {
        if(count==0)
            return;

        if(flag)// если флаг установлен в 1, то внесение данных идет по методу опирования
        {
            beginElem->Next->elem=new MyType();
            MyType *tmp=beginElem->Next->elem;//что бы не ошибится//
            *tmp=*Element;
        }
        else// иначе вносятся адреса, но не сами данные
        {
            beginElem->Next->elem=Element;
        }
    }

    void SetLastElem(MyType *Element)// установка(замена элемента)
    {
        if(count==0)
            return;

        if(flag)// если флаг установлен в 1, то внесение данных идет по методу опирования
        {
            last->elem=new MyType();
            MyType *tmp=last->elem;//что бы не ошибится//
            *tmp=*Element;
        }
        else// иначе вносятся адреса, но не сами данные
        {
            last->elem=Element;
        }
    }

    void DeleteLastElem()// удаялет последний элемент, текущий сбрасывается на последний элемент
    {
        if(count==0)
            return;

        if(count>1)
        {
            last=last->Prev;
            delete last->Next->elem;
            delete last->Next;
            last->Next=NULL;
        }
        else
        {
            beginElem->Next=NULL;
            delete last->elem;
            delete last;
            last=beginElem;
        }

        count--;
        Last();
    }

    void DeleteFirstElem()// удаляет первый элемент, текущий=1
    {
        if(count==0)
            return;
        beginElem->Next=beginElem->Next->Next;
        delete beginElem->Next->Prev;
        beginElem->Next->Prev=beginElem;
        count--;

        First();
    }

    void DeleteCurrentElem()//удаляет текщий элемент, текущий скидывает на предидущий
    {
        if(count==0)
            return;

        MyElemListLink *tmp;

        if(current==beginElem->Next)
        {
            beginElem->Next=current->Next;
            tmp=beginElem->Next;
            last=beginElem;
        }
        else{
            tmp= current->Prev;

            if(current->Next==NULL)
            {
                tmp->Next=NULL;
            }
            else
            {
                current->Next->Prev=tmp;
                tmp->Next=current->Next;
            }
            last=tmp;
        }
        count--;
        delete current;
        //delete current->elem;
        current = tmp;

    }

    bool SetCurrentToIndex(quint16 index)//делает текущим элемент с данным индексом(если его нет то возвращает false)
    {
        if(index>=Count())
            return false;// элемент не существует

        First();// элемент 0
        for(int i=0;i<index;i++)
            Next();
        return true;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif // MYLISTLINK_H
