#include<stdio.h>
#include<stdlib.h>

#include <iostream>
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999
using namespace std;
class ListNode
{
public:
    int item;
    ListNode * next;

    ListNode(){}
    ListNode(int item) : item(item) { next = 0; }

};

class LinkedList
{

    ListNode * list;
    int length;

public:
    LinkedList()
    {
        list=0; //initially set to NULL
        length=0;
    }

    int getLength()
    {
        return length;
    }

    int insertItem(int item) //insert at the beginning
    {
        ListNode * newNode = new ListNode() ;
        newNode->item = item ;
        newNode->next = list ; //point to previous first node
        list = newNode ; //set list to point to newnode as this is now the first node
        length++;
        return SUCCESS_VALUE ;
    }

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
        return SUCCESS_VALUE ;
    }


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
            printf("List Empty!!\n");
            return;
        }
        while(temp!=0)
        {
            printf("%d->", temp->item);
            temp = temp->next;
        }
        printf("\n");
        printf("Length: %d\n",length);
    }

    //------------write code for the functions below-----------

    int insertLast(int item)
    {
        //write your codes here
        if(length==0)
        {
            insertItem(item);
            return SUCCESS_VALUE;
        }
        ListNode * node1=list, *node2=list;
        while(node1!= nullptr)
        {
            node2=node1;
            node1=node1->next;
        }

        node2->next=new ListNode(item);
        length++;
    }

    int insertAfter(int oldItem, int newItem)///Puts newItem after the first Occurence of oldItem
    {
        //write your codes here
        ListNode * old=searchItem(oldItem);
        if(old== 0)
        {
            cout<<"OLD Item Not Found On the Existing List\n";
            return NULL_VALUE;
        }
        ListNode * temp=old->next;
        ListNode * newNode =new ListNode(newItem);
        old->next=newNode;
        newNode->next=temp;
        length++;

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

    int deleteFirst()
    {
        //write your codes here
        if(length==0)
            return NULL_VALUE;
        ListNode * temp=list;
        list=list->next;
        length--;
        delete temp;
        return SUCCESS_VALUE;
    }


    ~LinkedList()
    {
        //write your codes here
        ListNode * node1, *node2=0;
        node1 = list;
        while(node1!= nullptr)
        {
            node2 = node1;
            node1 = node2->next;
            delete node2;
        }
    }

};

int main(void)
{
    LinkedList ll;
    //for(int i=0;i<20;i++,ll.insertItem(i));
    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. InsertLast(int item). 5.getItemAt(int pos) 6.deleteFirst 7.insertAfter(int old,int new) "
                       "9. Print. 10. exit.\n ");
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
            int item=0;
            scanf("%d",&item);
            ll.insertLast(item);
        }
        else if(ch==5) {
            int pos = 0;
            scanf("%d", &pos);
            if (ll.getItemAt(pos) != nullptr)cout <<"Item At :"<<pos<<" = "<< ll.getItemAt(pos)->item << endl;

        }
        else if(ch==6)ll.deleteFirst();
        else if(ch==7)
        {
            int o=0,n=0;

            scanf("%d%d",&o,&n);
            ll.insertAfter(o,n);
        }
        else if(ch==9)
        {
            ll.printList();
        }
        else if(ch==10)
        {
            break;
        }
    }

}
