package ParallelBinarySearch;

import java.util.concurrent.CyclicBarrier;

public class Main {
    public static void main(String args[]) {
        int N = 10;
        int P = 4;
        int v[] = new int[N];
        int x = 5;
        int res;

        CyclicBarrier barrier= new CyclicBarrier(P);
        MyThread threads[] = new MyThread[P];

        for(int i = 0; i < N; i++) {
            v[i] = i;
        }

        for(int i = 0; i < P; i++){
            threads[i] = new MyThread(N, P, v, i, x, barrier);
        }

        for (int i = 0; i < P; i++)
            threads[i].start();

        for (int i = 0; i < P; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        res = MyThread.getResult();

        if(res != -1) {
            System.out.println("Element found at position " + res);
        }
        else {
            System.out.println("Element not found!");
        }
    }
}
