import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

class Task implements Comparable
{
    int startTime=0;
    int finishTime=0;

    public Task(int startTime, int finishTime) {
        this.startTime = startTime;
        this.finishTime = finishTime;

    }
    @Override
    public String toString()
    {
        return "[ Starting Time = "+startTime+" "+"Finishing Time "+finishTime+" ]";
    }
    @Override
    public int compareTo(Object o) {
        Task rhs=(Task)o;
        if(this.finishTime>rhs.finishTime)
        {
            return 1;
        }
        else if(this.finishTime<rhs.finishTime)
        {
            return -1;
        }
        else return 0;
    }
}
public class Main {

    public static void main(String[] args) {

        Scanner input=new Scanner(System.in);
        int n=input.nextInt();

        ArrayList<Task> tasks=new ArrayList<>();
        int t1,t2;
        for(int i=0;i<n;i++) {
            t1=input.nextInt();
            t2=input.nextInt();
            tasks.add(new Task(t1,t2));//O(1)
        }
        Collections.sort(tasks);//uses MergeSort O(nlogn)
        ArrayList<Task> selected=new ArrayList<>();
        selected.add(tasks.get(0));

        for (int i=1,j=0;i<n;i++)
        {
             if((selected.get(j).finishTime<=tasks.get(i).startTime))

                 {
                     selected.add(tasks.get(i));
                     j++;
                 }
        }
        System.out.println(selected.size());
        for (Task t:
             selected) {
            System.out.println(t);
        }

    }

}