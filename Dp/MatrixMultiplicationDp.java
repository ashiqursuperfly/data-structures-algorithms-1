import java.util.ArrayList;
import java.util.Scanner;

class Matrix
{
    int row;
    int col;

    public Matrix(int row, int col) {
        this.row = row;
        this.col = col;
    }
}
public class MatrixMultiplicationDp {

    public static void main(String[] args) {
	// write your code here

        ArrayList<Matrix> matrices=new ArrayList<>();
        ArrayList<Integer> dimensions=new ArrayList<>();

        Scanner sc=new Scanner(System.in);

        System.out.println("Please Enter Matrix Dimensions . When you are done,enter any letter 'a-z' to stop. ");
        while(sc.hasNextInt())
        {
            dimensions.add(sc.nextInt());
        }
        for (int i = 0; i <dimensions.size()-1 ; i++) {
           // System.out.println(dimensions.get(i)+" "+dimensions.get(i+1));
            matrices.add(new Matrix(dimensions.get(i),dimensions.get(i+1)));
        }

        int row=matrices.size(),col=matrices.size();

        int [][] table=new int[row][col];

        for(int r=0;r<row;r++)
        {
            for (int c=0;c<col;c++)
            {
                if(r==c)table[r][c]=0;
                if(r>c)table[r][c]=-1;

            }
        }
        int startJ=1;
        int startI=0;
        int i,j;
        for (i=startI;;)
        {
            for (j=startJ;j<row;j++,i++)
            {
                int min=Integer.MAX_VALUE;
                for (int k=i;k<j;k++)
                {
                    table[i][j] = table[i][k] + table[k + 1][j] + matrices.get(i).row * matrices.get(k).col *matrices.get(j).col;
                 //   System.out.println("K="+k+" :"+table[i][j]);
                    if(k==i)min=table[i][j];
                    else if(table[i][j]<min)min=table[i][j];

                }
                table[i][j]=min;
               // System.out.println(" M ["+i+","+j+"]" +" :"+table[i][j]);


            }
            //System.out.println("-");
            if(i==0 && j==row+1)break;
            startJ++;
            i=startI;

        }
        System.out.println(table[0][row-1]);
    }
}
