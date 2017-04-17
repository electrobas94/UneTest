#ifndef MYELEMLISTLINK_H
#define MYELEMLISTLINK_H
#include <QString>

template <class MyType>

class MyElemListLink//шаблонный класс одного элемента динамического списка и используется только в нем
{
public:
    MyType *elem;
    MyElemListLink<MyType> *Next;
    MyElemListLink<MyType> *Prev;
    MyElemListLink()
    {
        elem=NULL;
        Next=NULL;
        Prev=NULL;
    }
};

#endif // MYELEMLISTLINK_H
