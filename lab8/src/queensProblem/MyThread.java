package queensProblem;

import java.util.concurrent.ExecutorService;

public class MyThread extends Thread {
    private ExecutorService tpe;
    private final int[] spots;
    private final int step;

    MyThread(ExecutorService tpe, int[] spots, int step) {
        this.tpe = tpe;
        this.spots = spots;
        this.step = step;
    }

    public void run() {
        if(step == Main.N) {
            printQueens();
            tpe.shutdown();
            return;
        }

        for(int i = 0; i < Main.N; i++) {
            int[] newSpots = spots.clone();
            newSpots[step] = i;

            if(validPos(newSpots)) {
                tpe.submit(new MyThread(tpe, newSpots, step + 1));
            }
        }
    }

    private void printQueens() {
        StringBuilder buffer = new StringBuilder();

        for (int i = 0; i < Main.N; ++i) {
            for (int j = 0; j < Main.N; ++j) {
                if (j == spots[i]) {
                    buffer.append("X");
                }
                else {
                    buffer.append("O");
                }
            }

            buffer.append("\n");
        }

        System.out.println(buffer);
    }

    private boolean validPos(int[] spots) {
        for(int i = 0; i < step; i++) {
            for(int j = i + 1; j <= step; j++) {
                if  (
                        (spots[i] == spots[j]) || //aceeasi linie
                        (i - spots[i] == j - spots[j]) || //aceeasi diagonala jos
                        (i + spots[i] == j + spots[j]) // aceeasi diagonala sus
                    )
                    return false;
            }
        }
        return true;
    }
}