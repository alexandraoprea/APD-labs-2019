package sortList;

import java.io.File;
import java.io.IOException;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.Semaphore;

public class ParseInput extends Thread {
    private final int id;
    private Semaphore semaphore;
    private List<Integer> list;

    ParseInput(int id, Semaphore semaphore, List<Integer> list) {
        this.id = id;
        this.semaphore = semaphore;
        this.list = list;
    }

    @Override
    public void run() {
        try {
            Scanner scanner = new Scanner(new File("elemente" + id + ".txt"));
            while (scanner.hasNextInt()) {
                list.add(scanner.nextInt());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        semaphore.release();
    }
}