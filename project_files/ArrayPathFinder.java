import java.util.*;
import java.io.*; 

public class ArrayPathFinder {
   public static void main(String[] args) throws Exception {
      Scanner in = new Scanner(new File(args[0]));
      int N = in.nextInt();
      int M = in.nextInt();
      int[][] values = new int[M+2][N];
      Arrays.fill(values[0], Integer.MAX_VALUE);
      Arrays.fill(values[M+1], Integer.MAX_VALUE);
      for(int i = 1; i<M+1; i++) 
         for(int j = 0; j<N; j++) 
            values[i][j] = in.nextInt();
      String[][] paths = new String[M+2][N];
      for(String[] path : paths)
         Arrays.fill(path, "");
      for(int i = 0; i<paths.length; i++) 
         paths[i][0] += values[i][0];
      for(int j = 1; j<N; j++) 
         for(int i=1; i<M+1; i++) {
            int min = Integer.MAX_VALUE;
            int ind = 0; 
            for(int k = -1; k<=1; k++) 
               if(values[i+k][j-1]<min) {
                  ind = i+k;
                  min = values[i+k][j-1];
               }
            paths[i][j] = paths[ind][j-1] + " " + values[i][j]; 
            values[i][j] += min;

         }
      int min = Integer.MAX_VALUE;      
      int ind = 0; 
      for(int i = 0; i<M+2; i++)  
         if(values[i][N-1]<min) {
            ind = i;
            min = values[i][N-1];
         }
      System.out.println(paths[ind][N-1]); 
      System.out.println(min);
   } 
}
