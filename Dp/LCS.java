import java.util.Scanner;

public class LCS {

    public static void main(String[] args) {
	// write your code here
    String strColumn;
    String strRow;

    Scanner sc=new Scanner(System.in);
    strColumn=sc.nextLine();
    strRow=sc.nextLine();
    int row=strRow.length()+1;
    int col=strColumn.length()+1;

    int C[][]=new int[row][col];
    char[][] direction=new char[row][col];


        for (int i = 1; i <row ; i++) {
            for (int j = 1; j <col ; j++) {
                if(strColumn.charAt(j-1)==strRow.charAt(i-1))
                {
                    C[i][j]=C[i-1][j-1]+1;
                    direction[i][j]='d';
                }
                else
                    {
                        C[i][j]=Integer.max(C[i-1][j],C[i][j-1]);
                        if(C[i][j]==C[i-1][j])direction[i][j]='u';
                        else if(C[i][j]==C[i][j-1])direction[i][j]='l';

                    }
            }
        }
        int i=0,j=0;
        StringBuffer lcs=new StringBuffer();
        for(i=row-1,j=col-1;;)
        {

           // System.out.println("i="+i+"j="+j);
                if(direction[i][j]=='d')
                {
                    //System.out.println("d");
                    lcs.append(strRow.charAt(i-1));
                    i--;
                    j--;
                }
                else if(direction[i][j]=='u')
                {
                    //System.out.println("u" );
                    i--;
                }
                else if(direction[i][j]=='l')
                {
                    //System.out.println("l");
                    j--;
                }

                if(i==0 || j==0)break;


        }
        System.out.println(lcs.reverse());

    }
    //ABCDGH” and “AEDFHR

    //AGGTAB” and “GXTXAYB” is “GTAB”
}
