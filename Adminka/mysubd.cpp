#include "mysubd.h"

MySUBD::MySUBD()
{
    testlist.tablenames=new MyListLink<QString>(COPY_MODE);
    testlist.testnames=new MyListLink<QString>(COPY_MODE);
    status=false;
    port=0;
}
