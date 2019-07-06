import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;
class Point2D
{
    int x;
    int y;

    public Point2D(int x, int y) {
        this.x = x;
        this.y = y;
    }
    public double distance(Point2D rhs)
    {
        return Math.sqrt(((x-rhs.x)*(x-rhs.x)) + ((y-rhs.y)*(y-rhs.y)));
    }
    @Override
    public String toString()
        {
            return "["+x+","+y+"]";
        }


}
class xComparator implements Comparator<Point2D>
{

    @Override
    public int compare(Point2D o1, Point2D o2) {
        Point2D rhs;
        Point2D lhs;
        rhs=(Point2D)o1;
        lhs=(Point2D)o2;

        return Integer.compare(lhs.x, rhs.x);

    }

    @Override
    public boolean equals(Object obj) {
        return false;
    }
}
class yComparator implements Comparator<Point2D>
{

    @Override
    public int compare(Point2D o1, Point2D o2) {
        Point2D rhs;
        Point2D lhs;
        rhs=(Point2D)o1;
        lhs=(Point2D)o2;

        return Integer.compare(lhs.y, rhs.y);

    }

    @Override
    public boolean equals(Object obj) {
        return false;
    }
}

public class ClosestPairOfPoints {

    public static ArrayList<Point2D> closestPair(ArrayList<Point2D> points)
    {
        //TODO: Creating Px(sorted on x) and Py(sorted on y)
        ArrayList<Point2D> Px= points;
        Collections.sort(Px,new xComparator());
        ArrayList<Point2D> Py=points;
        Collections.sort(Py,new yComparator());

        return closestPairRec(Px,Py);


    }

    private static ArrayList<Point2D> bruteForce(ArrayList<Point2D> P)
    {
        double min=Double.MAX_VALUE;
        ArrayList<Point2D> closest=new ArrayList<>();
        for (int i = 0; i < P.size(); ++i) {
            for (int j = i + 1; j < P.size(); ++j) {
                if (P.get(i).distance(P.get(j)) < min) {
                    min = P.get(i).distance(P.get(j));
                    closest.clear();
                    closest.add(P.get(i));
                    closest.add(P.get(j));
                }
            }
        }
        return closest;
    }
    private static ArrayList<Point2D> closestPairRec(ArrayList<Point2D> Px, ArrayList<Point2D> Py) {

        if(Px.size()<=3)
        {
            //TODO: if size <=3 bruteforce method is much efficient than DnC
            return bruteForce(Px);
        }

        /*TODO:Dividing Px,Py into left and right sublists
         Lx-sorted left half based on x-coordinate
         Ly-sorted left half based on y-coordinate
         Rx-sorted right half based on x-coordinate
         Ry-sorted right half based on y-coordinate
        */
        ArrayList<Point2D> Lx=new ArrayList<>();
        ArrayList<Point2D> Ly=new ArrayList<>();
        ArrayList<Point2D> Rx=new ArrayList<>();
        ArrayList<Point2D> Ry=new ArrayList<>();
        int mid=Px.size()/2;

        for (int i=0;i<mid;i++)
        {
            Lx.add(Px.get(i));
            Ly.add(Px.get(i));
        }
        for (int i = mid; i <Px.size() ; i++) {

            Rx.add(Px.get(i));
            Ry.add(Px.get(i));
        }
        Collections.sort(Ly,new yComparator());
        Collections.sort(Ry,new yComparator());



        //TODO: finding the closest pair of points lying on the left half
        ArrayList<Point2D> leftClosest= closestPairRec(Lx,Ly);
        double dLeft=leftClosest.get(0).distance(leftClosest.get(1));
        //TODO: finding the closest pair of points lying on the right half
        ArrayList<Point2D> rightClosest= closestPairRec(Rx,Ry);
        double dRight=rightClosest.get(0).distance(rightClosest.get(1));

        //TODO:finding the minimum distance delta between the two results
        double delta = Math.min(dLeft,dRight);

        //TODO: Case 1 : Both of the points lie in either left or right Half(in this case delta is the our desired closest distance)
        //TODO: Case 2: One lies on the left and one is on the right i.e the points are split

        //TODO:Finding the closest pair of Split Points
        ArrayList<Point2D> splitClosest=closestPairSplit(Px,Py,delta);

        double dSplit;
        if(splitClosest.size()!=0)dSplit=splitClosest.get(0).distance(splitClosest.get(1));
        else dSplit=Double.MAX_VALUE;
        //Print The Best of the 3 possible Answers
        double answer=Math.min(dLeft,Math.min(dRight,dSplit));

        if(Double.compare(answer,dLeft)==0)return leftClosest;
        else if(Double.compare(answer,dRight)==0)return rightClosest;
        else return splitClosest;


    }


    private static ArrayList<Point2D> closestPairSplit(ArrayList<Point2D> Px, ArrayList<Point2D> Py, double delta) {
    //TODO:This Method Finds the closest pair of Split Points
        int mid=Px.size()/2;
        int x_=Px.get(mid-1).x;
        ArrayList<Point2D> Sy=new ArrayList<>();
        //TODO:Finding Rectangular Strip,Sy(O(n)).
        // x_=maximum of Lx or the Boundary of the strip
        //TODO:Sy is basically a Set of points Having,1.(x_ - delta)<=x<=(x_ + delta) 2.Sorted Based on Y.
        for (int i = 0; i <Py.size() ; i++) {
            Point2D temp=Py.get(i);
            if((temp.x>=x_-delta) && (temp.x<=x_+delta))
            {
                Sy.add(temp);
            }
        }
        double min = delta;
        ArrayList<Point2D> splitClosest=new ArrayList<>();

        // Pick all points one by one and try the next points till the difference
        // between y coordinates is smaller than d.
        // This is a proven fact that this loop runs at most 6 times
        //Outer loop is O(n)
        //Bt inner loop is O(1)
        //So this nested loop is O(n)
        //TODO: THe next loop finds the closest points from Sy in O(n)
        //TODO:Little Different Approach(Similar to Tardos)  -->https://www.youtube.com/watch?v=jAigdwcATNw
        int iteration=0;
        for (int i = 0; i < Sy.size(); ++i) {

            for (int j = i + 1; j < Sy.size() && (Sy.get(j).y - Sy.get(i).y) < min; ++j) {
                if (Sy.get(i).distance(Sy.get(j)) < min) {
                    min = Sy.get(i).distance(Sy.get(j));
                    splitClosest.clear();

                    splitClosest.add(Sy.get(i));
                    splitClosest.add(Sy.get(j));
                }
                System.out.println("Iteration :"+iteration++);
            }

        }

        return splitClosest;
    }

    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        ArrayList<Point2D> points=new ArrayList<>();
        int n=sc.nextInt();
        for (int i=0;i<n;i++)
        {
            int tempX=sc.nextInt();
            int tempY=sc.nextInt();
            points.add(new Point2D(tempX,tempY));

        }
        for (int i=0;i<points.size();i++)
        {
            for (int j=0;j<points.size();j++)
            {
                System.out.println("Distance between Point-"+i+" & Point-"+j +"="+points.get(i).distance(points.get(j)));
            }
        }
        ArrayList<Point2D> answer=closestPair(points);
        for (Point2D p :
                answer) {
            System.out.println(p);
        }


        System.out.println(answer.get(0).distance(answer.get(1)));



    }
}
