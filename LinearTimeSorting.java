
import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;
import java.util.Scanner;




class LinearTimeSorting
{

    ArrayList<Float> bucketSort(ArrayList<Float> arr,int bucketSize) {


        float max=0;
        int divider;

        int numberOfBuckets = bucketSize;//(int) (1.5*(size));
        float min=Float.MAX_VALUE;
        ArrayList<Float> [] B=new ArrayList[numberOfBuckets];
        ArrayList<Float> nonNegative=new ArrayList<>();
        ArrayList<Float> negative=new ArrayList<>();

        for (float x:
                arr) {
            if(x>max)max=x;
            if(x<min)min=x;
            if(x>=0)nonNegative.add(x);
            else negative.add(-x);
        }

        for (int l = 0; l <numberOfBuckets ; l++) {
            B[l]=new ArrayList<>();
        }


        int size=nonNegative.size();
        divider = (int) Math.ceil( (float)(max + 1) / numberOfBuckets);


        for(int i = 0,j=0; i < size; i++) {
            j = (int) Math.floor( nonNegative.get(i) / divider );
            B[j].add(nonNegative.get(i));
        }


        for(int i = 0; i < numberOfBuckets; i++) {
            Collections.sort(B[i]);
        }


        int k = 0;
        for(int i = 0; i < numberOfBuckets; i++) {
            for(int j = 0; j < B[i].size(); j++) {
                nonNegative.set(k++, B[i].get(j));
            }
        }

        if(min>=0)return nonNegative;
        negative=bucketSort(negative,bucketSize);
        for (int  i =0;i<negative.size() ; i++) {
            nonNegative.add(0,-negative.get(i));
        }
        arr.clear();
        arr.addAll(nonNegative);
        return arr;

    }

    ArrayList<Integer> countingSort(ArrayList<Integer> arr)
    {
        int n = arr.size();

        int max=0;
        int min=Integer.MAX_VALUE;
        ArrayList<Integer> nonNegative=new ArrayList<>();
        ArrayList<Integer> negative=new ArrayList<>();

        for (int x:
                arr) {
            if(x>max)max=x;
            if(x<min)min=x;
            if(x>=0)nonNegative.add(x);
            else negative.add(-x);
        }
        max++;//since we need one more position than the max value
//        for (int x:
//             arr) {
//            if(x>=0)nonNegative.add(x);
//            else negative.add(-x);
//        }

        int output[] = new int[n];

        int countNonNegative[] = new int[max];

        for (int i=0; i<max; ++i)
            countNonNegative[i] = 0;

        for (Integer aNonNegative : nonNegative) ++countNonNegative[aNonNegative];
        for (int i=1; i<max; ++i)
            countNonNegative[i] += countNonNegative[i-1];

        for (Integer aNonNegative : nonNegative) {
            output[countNonNegative[aNonNegative] - 1] = aNonNegative;
            --countNonNegative[aNonNegative];
        }


        for (int i = 0; i<nonNegative.size(); ++i)
            nonNegative.set(i,output[i]);

        arr.clear();
        arr.addAll(nonNegative);
        if(min>=0)return arr;

        int countNegative[]=new int[-(min)];

        //System.out.println("Negative Elements sorted");
        negative=countingSort(negative);

        for (int i =0;i<negative.size() ; i++) {
            nonNegative.add(0,-negative.get(i));
        }
        arr.clear();
        arr.addAll(nonNegative);
        return arr;
    }
    public static ArrayList<Float> createRandomArray(int size)
    {
        ArrayList<Float> arr=new ArrayList<>();
        for (int i=0;i<size;i++)
        {
            Random r=new Random();
            // arr.add( r.nextInt((int) (max + 1 -min))/size +min);
            arr.add((r.nextFloat()*2-1)*size);
        }

        return arr;
    }

    // Driver method
    public static void main(String args[])
    {
        LinearTimeSorting ob = new LinearTimeSorting();

        int testArrSize;
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter test Array Size");
        testArrSize=sc.nextInt();
        ArrayList<Float> arr= LinearTimeSorting.createRandomArray(testArrSize);
        ArrayList <Integer> arr2=new ArrayList<>();
        for (float d:
             arr) {
            arr2.add((int )d);
        }
        System.out.println("Randomly Created Array of size "+testArrSize);
        System.out.println(arr);
        long s,e;
        s=System.currentTimeMillis();
        System.out.println("Sorted :");
        System.out.println(ob.countingSort(arr2));
        e=System.currentTimeMillis();
        System.out.println("Time Taken For Counting Sort (n) :"+(e-s)+"ms \n\n");

        s=System.currentTimeMillis();
        System.out.println("\n\nSorted :");
        System.out.println(ob.bucketSort(arr,(int)(1.5*testArrSize)));
        e=System.currentTimeMillis();
        System.out.println("Time Taken For Bucket Size 1.5n :"+(e-s) +"ms \n\n");

        s=System.currentTimeMillis();
        System.out.println("Sorted :");
        System.out.println(ob.bucketSort(arr,testArrSize));
        e=System.currentTimeMillis();
        System.out.println("Time Taken For Bucket Size (n) :"+(e-s)+"ms \n\n");

        s=System.currentTimeMillis();
        System.out.println("Sorted :");
        System.out.println(ob.bucketSort(arr,(int)(Math.sqrt(testArrSize))));
        e=System.currentTimeMillis();
        System.out.println("Time Taken For Bucket Size sqrt(n) :"+(e-s)+"ms \n\n");






    }
}

