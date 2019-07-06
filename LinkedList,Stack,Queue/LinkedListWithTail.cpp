#include<stdio.h>
#include<stdlib.h>
#include<iostream>

#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

using namespace std;
class ListNode
{
public:
    int item;
    ListNode * next;
};

class LinkedListWithTail
{

    ListNode * list;
    ListNode * tail;
    int length;

public:
    LinkedListWithTail()
    {
        list = 0;  //initially set to NULL
        tail = 0;
        length=0;
    }

    int getLength()
    {
        return length;
    }

    //add required codes to set up tail pointer
    int insertItem(int item) //insert at the beginning
    {
        ListNode * newNode ;
        newNode = new ListNode() ;
        newNode->item = item ;
        newNode->next = list ; //point to previous first node
        list = newNode ; //set list to point to newnode as this is now the first node
        length++;
        if(length==1) {
            tail = list;
        }
        //printf("Current TAil item is: %d",tail->item);
        return SUCCESS_VALUE;
    }

    //add required codes to set up tail pointer
    int deleteItem(int item)
    {
        ListNode *temp, *prev ;
        temp = list ; //start at the beginning
        while (temp != 0)
        {
            if (temp->item == item) break ;
            prev = temp;
            temp = temp->next ; //move to next node
        }
        if (temp == 0) return NULL_VALUE ; //item not found to delete
        if (temp == list) //delete the first node
        {
            list = list->next ;
            delete temp;
            length--;
        }
        else
        {
            prev->next = temp->next ;
            delete temp;
            length--;
        }
        ListNode * n1=list,*n2=0;
        while(n1!=0) {
            n2=n1;
            n1 = n1->next;
        }
        tail=n2;
        //printf("Current TAil item is: %d",tail->item);
        return SUCCESS_VALUE ;
    }

    //add required codes to set up tail pointer
    ListNode * searchItem(int item)
    {
        ListNode * temp ;
        temp = list ; //start at the beginning
        while (temp != 0)
        {
            if (temp->item == item) return temp ;
            temp = temp->next ; //move to next node
        }
        return 0 ; //0 means invalid pointer in C, also called NULL value in C
    }

    void printList()
    {
        ListNode * temp;
        temp = list;
        if(length==0)
        {
            printf("List Empty !!\n");
            return;
        }
        while(temp!=0)
        {
            printf("%d->", temp->item);
            temp = temp->next;
        }
        printf("\n");
        printf("Length: %d\n",getLength());
    }

    //------------write code for the functions below-----------
    int insertLast(int item)
    {
        //write your codes here
        ListNode * nodeNew=new ListNode();
        nodeNew->item=item;
        tail->next=nodeNew;
        tail=nodeNew;
        length++;
       // printf("Current TAil item is: %d\n",tail->item);
    }

    ListNode * getItemAt(int pos)
    {
        //write your codes here
        ListNode * n1=list,*n2=list;
        if(pos>length || length==0)
        {
            printf("Invalid Index\n");
            return nullptr;
        }
        for(int i=1;i<=pos;i++)
        {
            n2=n1;
            n1=n1->next;
            if(n1==nullptr)break;
        }
        return n2;

    }

    int deleteLast()
    {
        //write your codes here
        if(length==0)return NULL_VALUE;

        ListNode * temp=list,*temp2=list;
        while(temp->next!= nullptr)
        {
            temp2=temp;
            temp=temp->next;

           // printf("x");
        }
        length--;
        delete tail;
        temp2->next=0;
        tail=temp2;
        if(length==0)
        {
            list=0;
            tail=0;
        }
       // printf("Current TAil item is: %d\n",tail->item);
        return SUCCESS_VALUE;
    }
};

int main(void)
{
    LinkedListWithTail ll;
    //for(int i=0;i<10;i++,ll.insertItem(i));
    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. InsertLast(int item). 5.DeleteLast 6.getItemAt(int pos) 7. Print. 8. exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            ll.insertItem(item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            ll.deleteItem(item);

        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            ListNode * res = ll.searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int item;
            scanf("%d", &item);
            ll.insertLast(item);
        }
        else if(ch==5)
        {
            ll.deleteLast();
        }
        else if(ch==6)
        {
            int pos = 0;
            scanf("%d", &pos);
            if (ll.getItemAt(pos) != nullptr)cout <<"Item At :"<<pos<<" = "<< ll.getItemAt(pos)->item << endl;
        }
        else if(ch==7)
        {
            ll.printList();
        }
        else if(ch==8)
        {
            break;
        }
    }

}
