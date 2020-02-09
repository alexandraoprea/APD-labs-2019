package shortestPathsFloyd_Warshall;

import static java.lang.Math.ceil;
import static java.lang.Math.min;

public class MyThread extends Thread {
    private final int[][] graph_par;
    private final int tid;
    private final double N;
    private final double P;

    MyThread(int[][]graph, int tid, int N, int P) {
        this.graph_par = graph;
        this.tid = tid;
        this.N = (double)N;
        this.P = (double)P;
    }

    public void run() {
        final int start = tid * (int)ceil(N/P);
        final int end = min((int)N, (tid + 1) * (int)ceil(N/P));

        for (int k = start; k < end; k++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    graph_par[i][j] = Math.min(graph_par[i][k] + graph_par[k][j], graph_par[i][j]);
                }
            }
        }
    }
}
