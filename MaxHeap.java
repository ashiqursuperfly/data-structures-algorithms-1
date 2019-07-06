import java.util.ArrayList;
import java.util.Scanner;

public class MaxHeap
{
    private ArrayList<Integer> list;
    public MaxHeap() {
        list = new ArrayList<>();
    }
    public MaxHeap(MaxHeap maxHeap) {
        list =new ArrayList<>(maxHeap.list);
    }
    public static MaxHeap createHeap()
    {
        MaxHeap maxHeap =new MaxHeap();
        return maxHeap;
    }
    public static MaxHeap heapify(int [] arr)
    {
        MaxHeap maxHeap =new MaxHeap();
        for (int x:
             arr) {
            maxHeap.insert(x);
        }
        return maxHeap;
    }
    public static MaxHeap meld(MaxHeap h1, MaxHeap h2)
    {
        h1.list.addAll(h2.list);
        Integer[] a=new Integer[h1.size()];
        h1.list.toArray(a);
        int arr[]=new int[h1.size()];
        for (int i = 0; i <h1.size() ; i++) {
            arr[i]=a[i];
        }
        System.out.println();
        h1.list.clear();
        h2.list.clear();
        return heapify(arr);

    }
    public static MaxHeap merge(MaxHeap h1, MaxHeap h2)
    {
        MaxHeap t1=new MaxHeap(h1);
        MaxHeap t2=new MaxHeap(h2);
        return meld(t1,t2);

    }
    private int parentPos(int pos){

        int x=(pos-1) / 2; //would've been pos/2 if array was indexed from 1
        return x;
    }
    private Integer leftChildPos(int pos) {
        int x=(2*pos)+1; //would've been 2*pos if array was indexed from 1
        if(x>=size())return null;
        return x;
    }
    private Integer rightChildPos(int pos){
        int x=(2 * pos) + 1+1;//would've been pos*2+1 if array was indexed from 1
        if(x>=size())return null;
        return x;
    }
    private void swap(int pos1,int pos2)
    {
        int tmp;
        tmp = list.get(pos1);
        list.set(pos1, list.get(pos2));
        list.set(pos2,tmp);
    }
    public void insert(int element)
    {
        list.add(element);
        siftUp(size()-1);
    }
    @Override
    public String toString()
    {
        StringBuffer out=new StringBuffer();
        System.out.println(list);
        for (int i = 0; i <= ((list.size()-1) / 2); i++ )
        {
            try {
                out.append(" PARENT : ").append(list.get(i));

                out.append(" LEFT CHILD : ").append(list.get(leftChildPos(i)));
            }catch (Exception AIOE){}
            try {
                out.append(" RIGHT CHILD :").append(list.get(rightChildPos(i))).append("\n");
            }catch (Exception AIOE){}

        }
        return out.toString();
    }
    public int size()
    {
        return list.size();
    }
    public boolean isEmpty()
    {
        return list.isEmpty();
    }
    public int delete(int pos)
    {
        swap(pos,size()-1);
        int deleted= list.remove(size()-1);

        siftDown(pos);
        return deleted;
    }
    public void deleteMax()
    {
        delete(0);
    }
    public int extractMax()
    {
        int max= list.get(0);
        swap(0,size()-1);
        list.remove(size()-1);

        siftDown(0);
        return max;
    }
    public int findMax()
    {
        return list.get(0);
    }
    private void siftUp(int pos)
    {
        if(pos==0)return;
        try {
            int current= list.get(pos);
            int parent= list.get(parentPos(pos));

            if(current>parent)
            {
                swap(pos,parentPos(pos));
                siftUp(parentPos(pos));
            }
        }
    catch (Exception e){System.out.println(e + "index "+pos);}

    }
    private void siftDown(int pos)
    {
        try {
            int leftChild=Integer.MIN_VALUE;
            if(leftChildPos(pos)!=null)leftChild = list.get(leftChildPos(pos));

            int rightChild =Integer.MIN_VALUE;
            if(rightChildPos(pos)!=null)rightChild= list.get(rightChildPos(pos));

            int parent = list.get(pos);

            if (parent < leftChild || parent < rightChild) {
                if (rightChild > leftChild) {
                    swap(rightChildPos(pos), pos);
                    siftDown(rightChildPos(pos));
                } else {
                    swap(leftChildPos(pos), pos);
//System.out.println("Swapped :"+heap.get(leftChildPos(pos))+"& "+heap.get(pos)+" Sift Down :"+leftChildPos(pos));
                    siftDown(leftChildPos(pos));
                }
            }
        }
        catch (Exception e){System.out.println(e + "index "+pos);}

    }
    public void replace(int key)
    {
        //Replaces Max Value
        list.set(0,key);
        siftDown(0);

    }
    public void increaseOrDecreaseKey(int pos,int dx)
    {
        if(pos>=size())
        {
            System.out.println("Invalid Position");
            return;
        }
        int deleted=delete(pos);
        insert(deleted+dx);
    }


}
class Test
{
    public static void main(String[]args)
    {
        Scanner input = new Scanner(System.in);

        int[] array1 = {1, 16, 5, 30, 27, 17, 20, 2, 57, 3, 90};
        int[] array2 = {12, 10, 90, 8, 17};
        MaxHeap mHeap = MaxHeap.heapify(array1);

        MaxHeap mHeap1 = MaxHeap.heapify(array1);
        MaxHeap mHeap2 = MaxHeap.heapify(array2);
        int select;

        while(true){
            System.out.println("Choose what you want to do: \n"+"1.Create Max MaxHeap  2.Insert     3.Size       4.Is Empty     5.Find Max  " +
                    "7.Heapify   8.Merge      9.Meld");
            System.out.println("11.Delete      12.Delete Max    13.Extract Max    14.Replace    15.Increase Or Decrease    16.Print    17.Exit  ");

            select = input.nextInt();
            switch (select){
                case 1:
                    MaxHeap newMaxHeap = MaxHeap.createHeap();
                    System.out.println("MaxHeap Created");
                    mHeap = newMaxHeap;
                    break;
                case 2:
                    System.out.println("Enter key to insert");
                    int key = input.nextInt();
                    mHeap.insert(key);
                    break;
                case 3:
                    System.out.println("Size of the heap : "+mHeap.size());
                    break;
                case 4:
                    if (mHeap.isEmpty()) System.out.println("Yes the heap is empty");
                    else System.out.println("No the heap is not empty");
                    break;
                case 5:
                    System.out.println("Maximum Value of the heap : "+mHeap.findMax());
                    break;
                case 7:
                    System.out.println("Heapifying Array 1");
                    mHeap= MaxHeap.heapify(array1);
                    System.out.println(mHeap);
                    break;
                case 8:
                    System.out.println("Merging Heap1 and Heap2 : ");
                    MaxHeap mergedMaxHeap = MaxHeap.merge(mHeap1, mHeap2);
                    System.out.println("MaxHeap 1 ");
                    System.out.println(mHeap1);
                    System.out.println("MaxHeap 2 ");
                    System.out.println(mHeap2);
                    System.out.println("Merged MaxHeap ");
                    System.out.println(mergedMaxHeap);
                    break;
                case 9:
                    System.out.println("Melding Heap1 and Heap2 : ");
                    MaxHeap meldedMaxHeap = MaxHeap.meld(mHeap1, mHeap2);
                    System.out.println("MaxHeap 1 ");
                    System.out.println(mHeap1);
                    System.out.println("MaxHeap 2 ");
                    System.out.println(mHeap2);
                    System.out.println("Melded MaxHeap ");
                    System.out.println(meldedMaxHeap);
                    break;

                case 11:
                    System.out.println("Enter position of the key u wish to delete");
                    int dPosition = input.nextInt();
                    System.out.println("Deleted :"+mHeap.delete(dPosition));
                    break;
                case 12:
                    mHeap.deleteMax();
                    break;
                case 13:
                    System.out.println("Extracted :"+mHeap.extractMax());
                    break;
                case 14:
                    System.out.println("Enter the value with which you want to replace the root key  ");
                    int val = input.nextInt();
                    mHeap.replace(val);
                    break;
                case 15:
                    System.out.println("Enter the Position of the key you want to increase/decrease :");
                    int p = input.nextInt();
                    System.out.println("Enter Value(+ve for increase / -ve for decrease)");
                    int k = input.nextInt();
                    mHeap.increaseOrDecreaseKey(p, k);
                    break;
                case 16:
                    System.out.println(mHeap);
                    break;
                case 17:
                    break;
            }
        }


    }
}