#include<iostream>
using namespace std;

void printArray(int arr[],int size)
{
    for(int i=0;i<size;cout<<arr[i]<<" ",i++);
    cout<<"\n";
}
void copyArray(const int src[], int dest[],int start,int end)
{
    for (int i = start,j=0; i <=end; i++,j++) {
        dest[i]=src[j];
    }
}

int merge(int sorted[],  int leftSubArray[],  int rightSubArray[],int lSize,int rSize)
{
    int nInversions=0;
    int indexL=0, indexR=0, indexSorted=0;

    int tempLeft[lSize],tempRight[rSize];
    copyArray(leftSubArray,tempLeft,0,lSize-1);
    copyArray(rightSubArray,tempRight,0,rSize-1);

    while ((indexL < lSize) && (indexR < rSize))
    {

        if (tempLeft[indexL] > tempRight[indexR])
        {
            sorted[indexSorted++] = tempRight[indexR++];
            nInversions = nInversions + (lSize  - indexL);
            // cout<<"Chosen :"<<tempRight[j-1]<<endl;

            //TODO : Print All Inversions//for(int m=i;m<lSize;m++)cout<<tempLeft[m]<<","<<tempRight[j-1]<<endl;

        }
        else
        {
            sorted[indexSorted++] = tempLeft[indexL++];
            // cout<<"Chosen :"<<tempLeft[i-1]<<endl;

        }
    }
    while (indexL < lSize) {
        sorted[indexSorted++] = tempLeft[indexL++];
    }

    while (indexR < rSize)
        sorted[indexSorted++] = tempRight[indexR++];

    return nInversions;
}

int  mergeSort(const int arr[],int startIndex,int endIndex,int sorted[]) {

    int nInversions=0;

    int currentSize = (endIndex - startIndex) + 1;
    int rightArrSize = currentSize / 2, leftArrSize = 0;

    if (currentSize % 2 == 0)leftArrSize = currentSize / 2;
    else leftArrSize = (currentSize / 2) + 1;

    int *rightSubArray = new int[rightArrSize];
    int *leftSubArray = new int[leftArrSize];

    //Forming The Left and Right SubArray
    for (int i = 0, j = 0; i < currentSize; i++) {
        if (i < leftArrSize){
            leftSubArray[i] = arr[i];
        }
        else {
            rightSubArray[j] = arr[i];
            j++;
        }
    }

    if (leftArrSize > 1) {

        nInversions=mergeSort(leftSubArray, 0, leftArrSize - 1, sorted);
        copyArray(sorted,leftSubArray,0,leftArrSize-1);


    }
    if (rightArrSize > 1) {
        nInversions+=mergeSort(rightSubArray, 0, rightArrSize - 1 ,sorted);
        copyArray(sorted,rightSubArray,0,rightArrSize-1);
    }

    nInversions+=merge(sorted,leftSubArray,rightSubArray,leftArrSize,rightArrSize);

    delete [] leftSubArray;
    delete [] rightSubArray;
    return nInversions;

}

int main()
{
    int arr[] = {5, 2, 10, 8, 1, 9, 4, 3, 6, 7};
    cout<<"Input Size\n";
    int size;
    cin>>size;
    int *sorted=new int[size];
    for(int i=0;i<size;i++)sorted[i]=-999999;
    cout<<"Number of Inversions:\n"<<mergeSort(arr,0,size-1,sorted)<<endl;
    printArray(sorted,size);
    printArray(arr,size);
    //copyArray(sorted,arr,0,size-1);
}
