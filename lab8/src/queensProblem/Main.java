package queensProblem;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class Main {

    static final int N = 5;

    public static void main(String[] args) {
        ExecutorService tpe = Executors.newFixedThreadPool(4);
        int[] spots = new int[N];

        tpe.submit(new MyThread(tpe, spots, 0));

        try {
            tpe.awaitTermination(15,  TimeUnit.SECONDS);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
