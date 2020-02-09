package getPathParallel;

import java.util.ArrayList;
import java.util.concurrent.ExecutorService;

public class MyThread extends Thread {
    private ExecutorService tpe;
    private ArrayList<Integer> path;
    private final int destination;

    public MyThread(ExecutorService tpe, ArrayList<Integer> path, int destination) {
        this.tpe = tpe;
        this.path = path;
        this.destination = destination;
    }

    public void run() {

       if(path.get(path.size() -1) == destination) {
           System.out.println(path);
           tpe.shutdown();
       }

       int lastNode = path.get(path.size() - 1);
        for (int i = 0; i < Main.graph.length; i++) {
            if(Main.graph[i][0] == lastNode && !path.contains(Main.graph[i][1])) {
                ArrayList<Integer> newPath = (ArrayList<Integer>) path.clone();
                newPath.add(Main.graph[i][1]);
                tpe.submit(new MyThread(tpe, newPath, destination));
            }
       }
    }
}
