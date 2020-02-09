package ParallelBinarySearch;

import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

import static java.lang.Math.ceil;
import static java.lang.Math.min;
import static java.lang.Math.floor;

public class MyThread extends Thread {
    static int offset = 0;
    static int result = -1;
    static int stop = 0;
    static int N;
    int tid;
    int P;
    int v[];
    int x;
    CyclicBarrier barrier;

    static int getResult() {
        return result;
    }

    MyThread(int N, int P, int v[], int tid, int x, CyclicBarrier barrier) {
        this.N = N;
        this.P = P;
        this.v = v;
        this.tid = tid;
        this.x = x;
        this.barrier = barrier;
    }

    public void run() {

        while (N > 0 && stop == 0) {
            try {
                barrier.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }

            int start = (tid * (int)floor((float) N / P)) + offset;
            int end = (int) min(N - 1, (tid + 1) * ceil((float) N / P)) + offset;

            if (v[start] == x) {
                result = start;
                stop = 1;
            }

            if (v[end] == x) {
                result = end;
                stop = 1;
            }

            if (x > v[start] && x < v[end]) {
                offset = offset + start + 1;
                N = end - start - 1;
            }

            try {
                barrier.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }
        }
    }
}