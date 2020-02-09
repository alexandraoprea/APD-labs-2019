package doubleVectorElements;

import static java.lang.Math.ceil;
import static java.lang.Math.min;

public class MyThread extends Thread {
    private final int v[];
    private final int tid;
    private final double N;
    private final double P;

    MyThread(int[]v, int tid, int N, int P) {
        this.v = v;
        this.tid = tid;
        this.N = (double)N;
        this.P = (double)P;
    }

    public void run() {

        final int start = tid * (int)ceil(N/P);
        final int end = min((int)N, (tid + 1) * (int)ceil(N/P));

        for(int i = start; i < end; i++) {
            v[i] = v[i] * 2;
        }

    }
}
