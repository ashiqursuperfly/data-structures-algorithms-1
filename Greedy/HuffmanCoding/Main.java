import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.Scanner;

class Node implements Comparable{

    int frequency;
    char label;

    String huffmanCode;

    Node left;
    Node right;

    public Node( char c,int frequency) {
        this.frequency = frequency;
        this.label = c;
    }

    public Node( char c, int frequency,Node left, Node right) {
        this.frequency = frequency;
        this.label = c;
        this.left = left;
        this.right = right;
    }

    @Override
    public String toString()
{
    return "Node :"+ label +"Frequency :"+frequency+" Code :"+huffmanCode;
}

    @Override
    public int compareTo(Object o) {
        Node n;
        try {
            if (o instanceof Node) n = (Node) o;
            else throw new Exception();

            if(this.frequency>n.frequency)return 1;
            else if(this.frequency<n.frequency)return -1;
            else return 0;
        }
        catch (Exception e){return -999999;}

    }
}


public class Main {

    static void findHuffmanCodes(Node source,String currentCode)
    {
        if(source.left==null &&source.right==null)
        {
            source.huffmanCode=currentCode;
            return;
        }
        findHuffmanCodes(source.left,currentCode+"0");
        findHuffmanCodes(source.right,currentCode+"1");
    }

    public static void main(String[] args) {


        Scanner input=new Scanner(System.in);
        int n=input.nextInt();
        PriorityQueue<Node> q = new PriorityQueue<>(n);
        ArrayList<Node> nodes=new ArrayList<>();

        for(int i=0;i<n;i++)
        {
            char c= input.next(".").charAt(0);
            int f=input.nextInt();
            Node newNode=new Node(c,f);
            q.add(newNode);/// O(logn)
            nodes.add(newNode);//O(1)

        }//nlogn

        while (q.size()>=2)
        {
            Node t1=q.remove();//logn
            Node t2=q.remove();//logn
            q.add(new Node('$',t1.frequency+t2.frequency,t1,t2));//logn

        }//3nlogn

        findHuffmanCodes(q.peek(),"");//logn

        for (Node node:
             nodes) {
            System.out.println(node);
        }

    }
}