#include<iostream>
using namespace std;
#define LIST_INIT_SIZE 2
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

int deleteLast();
int listMaxSize;
int * list;
int length;


void initializeList()
{
    listMaxSize = LIST_INIT_SIZE;
    list = (int*)malloc(sizeof(int)*listMaxSize) ;
    length = 0 ;
}
int getLength()
{
    return length;
}
int searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i] == item ) return i;
    }
    return NULL_VALUE;
}

int insertItem(int newitem)
{
    ///Add Logic to Promote clear()
    if(list==nullptr){
        initializeList();
    }
    if (length == listMaxSize)
    {
        int * tempList ;
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;
        tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ; //make list to point to new memory


    }
    list[length] = newitem ; //store new item
    length++ ;
    return SUCCESS_VALUE ;
}

int insertItemAt(int pos,int item)
{


    if(pos>=length)
    {
        printf("Invalid Index!\n");
        return NULL_VALUE;
    }

    insertItem(item);
        /*if (length != 1) {///swap only if
            list[length - 1] = list[length - 1] ^ list[pos];
            list[pos] = list[length - 1] ^ list[pos];
            list[length - 1] = list[length - 1] ^ list[pos];
            return SUCCESS_VALUE;
        }*/
    if(pos!=length-1) {
        for (int i = length - 1; i > pos; i--) {
            int temp = list[i - 1];
            list[i - 1] = list[i];
            list[i] = temp;

        }
    }
    return SUCCESS_VALUE;
}
void shrink()
{
    int * tempList ;
    listMaxSize =(int)(0.5 * listMaxSize) ;
    tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
    int i;
    for( i = 0; i < length ; i++ )
    {
        tempList[i] = list[i] ; 
    }
    free(list) ;
    list = tempList ;
}
int deleteItemAt(int position) //version 1, preserves order of items
{
    if ( position >= length ) return NULL_VALUE;

    if(position!=length-1) {
        for (int i = position; i < length; i++) {
            list[i]=list[i+1];
        }
        length--;
    }
    else
    {
        deleteLast();
    }

    if(length<=listMaxSize/2 && length>=LIST_INIT_SIZE)shrink();
    return SUCCESS_VALUE ;
}
/*int deleteItemAt(int position) //version 2, do not preserve order of items
{
    if ( position >= length ) return NULL_VALUE;
    list[position] = list[length-1] ;
    length-- ;
    if(length<=listMaxSize/2 && length>=LIST_INIT_SIZE)shrink();
    return SUCCESS_VALUE ;
}
*/
void clear()
{
    listMaxSize=0;
    free(list);
   length=0;
    list=nullptr;

}
void deleteAll()
{
    int * tempList ;
    listMaxSize =LIST_INIT_SIZE ;
    length=0;
    tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
    free(list);
    list=tempList;
}
int deleteItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE ) return NULL_VALUE;
    deleteItemAt(position) ; ///**which Ensures shrink() to be invoked(if Necessary) since shrink() is Called inside deleteItemAt
    return SUCCESS_VALUE ;
}

int deleteLast()
{
    if(length!=0) {
        int temp=list[length-1];
        deleteItemAt(length - 1); ///**which Ensures shrink() to be invoked(if Necessary) since shrink() is Called inside deleteItemAt
        return temp;///promotes task 7 at ease
    }
    return NULL_VALUE;
}
void printList()
{
    int i;
    if(list== nullptr)cout<<"LIST IS EMPTY :(! \n";
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}



////Main Function for First 6 Tasks ////


int main(void)
{
    initializeList();
    for(int i=1;i<20;i=i+2,insertItem(i));
    while(1)
    {
        printf("1. Insert new item. 2. Delete item at. 3. Delete item.\n");
        printf("4. Insert New Item at(pos,item). 5. Print. 6.DeleteLast 7.DeleteAll 8.Clear 9.exit \n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2)
        {
            int pos;
            scanf("%d", &pos);
            deleteItemAt(pos);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch==4)
        {
            int item,pos;
            scanf("%d%d",&pos,&item);
            insertItemAt(pos,item);
        }
        else if(ch==5)
        {
            printList();
        }
        else if(ch==6)
        {
           deleteLast();
        }
        else if(ch==7) {
            deleteAll();
        }
        else if(ch==8)
        {
            clear();
        }
        else if(ch==9)
        {
            break;
        }
    }

}



////Main Function for Task 7 ////
/*
int main()
{
    string s;
    cin>>s;
    int ans=0;
    for(int i=0;i<s.length();i++)
    {
        if(s[i]-'0'>=0 && s[i]-'0'<=9)insertItem(s[i]-'0');
        else
        {
            int temp2=deleteLast();
            int temp1=deleteLast();
            ///temp2 must be taken earlier to maintain '-' or '/' correctly
            if(temp2==NULL_VALUE || temp1 ==NULL_VALUE)
            {
                cout<<"Invalid Expression"<<endl;
                return 0;
            }

            if(s[i]=='+')
            {
                 ans=temp1+temp2;
                insertItem(ans);
            }
            if(s[i]=='-')
            {
                ans=temp1-temp2;
                insertItem(ans);
            }
            if(s[i]=='*')
            {
                 ans=temp1*temp2;
                 insertItem(ans);
            }
            if(s[i]=='/')
            {
                if(temp2==0)
                {
                    cout<<"Cant Divide by Zero!!"<<endl;
                }
                else {
                    ans = temp1 / temp2;
                    insertItem(ans);
                }
            }
        }
    }
    if(length>1)cout<<"Invalid Expression"<<endl;
    else cout<<ans;
}
*/