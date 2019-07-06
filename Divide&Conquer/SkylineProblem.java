import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

class Point implements Comparable
{
    int x;
    int y;
    Point(int x, int y) {
        this.x = x;
        this.y = y;
    }
    @Override
    public String toString()
    {
        return "["+x+","+y+"]";
    }
    @Override
    public int compareTo(Object o) {
        Point rhs;
        if(o instanceof Point)rhs=(Point)o;
        else return -9999999;
        if(x>rhs.x)return 1;
        else if(x<rhs.x)return -1;
        else return 0;

    }
}
public class SkylineProblem {

    public static ArrayList<Point> findSkyline(ArrayList<Point> xSortedPointList){

        if (xSortedPointList.size()<=1){
            return xSortedPointList;
        }


        ArrayList<Point> leftPoints=new ArrayList<>();
        ArrayList<Point> rightPoints=new ArrayList<>();


        for (int i=0;i<xSortedPointList.size()/2;i++){
            leftPoints.add(xSortedPointList.get(i));
        }
        for (int i=xSortedPointList.size()/2;i<xSortedPointList.size();i++){
            rightPoints.add(xSortedPointList.get(i));
        }


        ArrayList<Point> leftSkylinePoints=findSkyline(leftPoints);


        int minY=leftSkylinePoints.get(0).y;///=MAX_INT
        for (int i=0;i<leftSkylinePoints.size();i++){
            if (leftSkylinePoints.get(i).y<minY){
                minY=leftSkylinePoints.get(i).y;
            }
        }
        for (int i=rightPoints.size() -1; i >=0; i--){
            if (rightPoints.get(i).y>=minY){
                rightPoints.remove(i);
            }
        }
        ArrayList<Point> rightSkylinePoints=findSkyline(rightPoints);

        System.out.println("MinimumY: "+minY);

        System.out.print("Left: ");
        for (int i=0;i<leftSkylinePoints.size();i++){
            System.out.print("("+leftSkylinePoints.get(i).x+","+leftSkylinePoints.get(i).y+") ");
        }
        //System.out.println();
        System.out.print("Right: ");
        for (int i=0;i<rightSkylinePoints.size();i++){
            System.out.print("("+rightSkylinePoints.get(i).x+","+rightSkylinePoints.get(i).y+") ");
        }
        System.out.println();
        System.out.println();


        leftSkylinePoints.addAll(rightSkylinePoints);
        return leftSkylinePoints;
    }

    public static void main(String[] args) {
	// write your code here
        Scanner sc=new Scanner(System.in);
        ArrayList<Point> points=new ArrayList<>();
        int n=sc.nextInt();
        for (int i=0;i<n;i++)
        {
            int tempX=sc.nextInt();
            int tempY=sc.nextInt();
            points.add(new Point(tempX,tempY));

        }
        Collections.sort(points);
        ArrayList<Point> skylinePoints= findSkyline(points);
                for (Point p:
             skylinePoints) {
             System.out.println(p);
        }


    }
}
