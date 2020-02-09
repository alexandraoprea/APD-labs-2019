package sortList;

import java.util.Collections;
import java.util.List;
import java.util.concurrent.Semaphore;

public class SortingThread extends Thread {
    private Semaphore semaphore;
    private List<Integer> list;

    SortingThread(Semaphore semaphore, List<Integer> list) {
        this.semaphore = semaphore;
        this.list = list;
    }

    public void run() {
        try {
            semaphore.acquire();
        }
        catch(InterruptedException e) {
            e.printStackTrace();
        }

        Collections.sort(list);
    }
}
