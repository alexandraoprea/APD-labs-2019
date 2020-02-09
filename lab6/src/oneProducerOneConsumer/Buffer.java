package oneProducerOneConsumer;

import java.util.concurrent.Semaphore;

/**
 * @author cristian.chilipirea
 *
 */
public class Buffer {
	private int a;
	private Semaphore semaphoreCons;
	private Semaphore semaphoreProd;

	Buffer() {
		a = -1;
		semaphoreProd = new Semaphore(1);
		semaphoreCons = new Semaphore(0);
	}

	void put(int value)
	{
		try {
			semaphoreProd.acquire();
		}
		catch(InterruptedException e) {
			e.printStackTrace();
		}

		a = value;

		semaphoreCons.release();
	}

	int get()
	{
		try {
			semaphoreCons.acquire();
		}
		catch(InterruptedException e) {
			e.printStackTrace();
		}

		int val = a;

		semaphoreProd.release();

		return val;
	}
}
