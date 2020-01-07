#include "controller.h"
#include "model.h"
#include "QDebug"

void Contorller::receive()
{
    int count=0;
    while(1)
    {
        while(flagReceive)
        {

            qDebug()<<"test"<<count++;
            Sleep(1000);
            if(flagReceive==2)
            {
                return;
            }
        }
    }
}
