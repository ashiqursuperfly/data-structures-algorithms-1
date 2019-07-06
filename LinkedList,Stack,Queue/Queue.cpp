#include<stdio.h>
#include<stdlib.h>
#include "LinkedListTail.h"


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

class Queue
{

public:
    LinkedListWithTail ll;
    Queue(){}
    void enqueue(int item)
    {
       ll.insertItem(item);
        ll.printList();
    }
    int dequeue()
    {
      return ll.deleteLast();
    }
};

int main(void)
{
    Queue qu;
    while(1)
    {
        printf("1. Enque. 2. Deque. 3. Exit. \n");
        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            qu.enqueue(item);

        }
        else if(ch==2)
        {
            int item=qu.dequeue();
            qu.ll.printList();
            if(item!=NULL_VALUE)printf("Dequeued :%d\n",item);
            else printf("Queue Empty !\n");
        }
        else if(ch==3)
        {
            break;
        }
    }

}

