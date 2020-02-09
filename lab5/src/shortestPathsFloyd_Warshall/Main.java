package shortestPathsFloyd_Warshall;
/**
 * @author cristian.chilipirea
 *
 */
public class Main {

	public static void main(String[] args) {
		int M = 9;
		int N = 5;
		int P = 4;
		int graph[][] = { { 0, 1, M, M, M }, 
				          { 1, 0, 1, M, M }, 
				          { M, 1, 0, 1, 1 }, 
				          { M, M, 1, 0, M },
				          { M, M, 1, M, 0 } };

		int graph_par[][] = { { 0, 1, M, M, M },
							{ 1, 0, 1, M, M },
							{ M, 1, 0, 1, 1 },
							{ M, M, 1, 0, M },
							{ M, M, 1, M, 0 } };

		MyThread[] threads = new MyThread[P];
		
		// Parallelize me (You might want to keep the original code in order to compare)
		for (int k = 0; k < N; k++) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					graph[i][j] = Math.min(graph[i][k] + graph[k][j], graph[i][j]);
				}
			}
		}

		for(int i = 0; i < P; i++) {
			threads[i] = new MyThread(graph_par, i, N, P);
			threads[i].start();
		}

		for(int i = 0; i < P; i++) {
			try {
				threads[i].join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				System.out.print(graph[i][j] + " ");
			}
			System.out.println();
		}

		System.out.println();

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				System.out.print(graph_par[i][j] + " ");
			}
			System.out.println();
		}
	}
}
