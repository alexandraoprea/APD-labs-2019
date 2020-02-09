package sortList;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.Semaphore;

public class Main {
    private static final int N = 1000;
    private static final int P = 4;

    public static void main(String[] args) {
        Thread[] threads = new Thread[P];
        boolean sorted = true;

        List<Integer> list;
        Semaphore semaphore;

        for (int i = 0; i < N; i++) {
            semaphore = new Semaphore(-2);
            list = Collections.synchronizedList(new ArrayList<>());

            for (int j = 0; j < P - 1; j++) {
                threads[j] = new ParseInput(j + 1, semaphore, list);
                threads[j].start();
            }

            threads[3] = new SortingThread(semaphore, list);
            threads[3].start();

            for (Thread thread : threads) {
                try {
                    thread.join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }

            int len = list.size();

            for (int j = 1; j < len; j++) {
                if (list.get(j) < list.get(j - 1)) {
                    System.out.println("Incorrect");
                    sorted = false;
                    break;
                }
            }
        }

        if (sorted) {
            System.out.println("Correct");
        }
    }
}