package colorGraphParallel;

import java.util.concurrent.ExecutorService;

public class MyThread extends Thread {
    private ExecutorService tpe;
    private final int[] colors;
    private final int step;

    MyThread(ExecutorService tpe, int[] colors, int step) {
        this.tpe = tpe;
        this.colors = colors;
        this.step = step;
    }

    @Override
    public void run() {
        if (step == Main.N) {
            printColors();
            tpe.shutdown();
        }

        for (int i = 0; i < Main.COLORS; i++) {
            int[] newColors = colors.clone();
            newColors[step] = i;

            if (verifyColors(newColors)) {
                tpe.submit(new MyThread(tpe, newColors, step + 1));
            }
        }
    }

    private boolean verifyColors(int[] newColors) {
        for (int i = 0; i < step; i++) {
            if (newColors[i] == newColors[step] && isEdge(i, step)) {
                return false;
            }
        }
        return true;
    }

    private boolean isEdge(int a, int b) {
        for (int i = 0; i < Main.graph.length; i++) {
            if (Main.graph[i][0] == a && Main.graph[i][1] == b)
                return true;
        }
        return false;
    }

    private void printColors() {
        StringBuilder buffer = new StringBuilder();

        for (int color : colors) {
            buffer.append(color).append(" ");
        }

        System.out.println(buffer);
    }
}