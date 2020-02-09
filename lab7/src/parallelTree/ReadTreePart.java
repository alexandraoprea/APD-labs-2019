package parallelTree;

import jdk.nashorn.api.tree.Tree;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

/**
 * @author cristian.chilipirea
 *
 */
public class ReadTreePart implements Runnable {
	private TreeNode tree;
	private String fileName;
	private CyclicBarrier barrier;

	ReadTreePart(TreeNode tree, String fileName, CyclicBarrier barrier) {
		this.tree = tree;
		this.fileName = fileName;
		this.barrier = barrier;
	}

	@Override
	public void run() {
		Scanner scanner = null;
		try {
			scanner = new Scanner(new File(fileName));

			TreeNode root;

			int parentName, childName;

			while (scanner.hasNextInt()) {
				childName = scanner.nextInt();
				parentName = scanner.nextInt();

				while ((root = tree.getNode(parentName)) == null);

				root.addChild(new TreeNode(childName));
			}

		}
		catch (FileNotFoundException e) {
			e.printStackTrace();
		}

		try {
			barrier.await();
		}
		catch(InterruptedException | BrokenBarrierException e) {
			e.printStackTrace();
		}
	}
}
