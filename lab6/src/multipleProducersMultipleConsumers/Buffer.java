package multipleProducersMultipleConsumers;

import java.util.concurrent.Semaphore;

/**
 * @author cristian.chilipirea
 *
 */
public class Buffer {
	private static int CAPACITY = 3;
	private int v[];
	private Semaphore semaphoreCons;
	private Semaphore semaphoreProd;
	private int id;

	Buffer() {
		v = new int[CAPACITY];
		semaphoreCons = new Semaphore(0);
		semaphoreProd = new Semaphore(CAPACITY);
		id = 0;
	}

	void put(int value)
    {
		try {
			semaphoreProd.acquire();
		}
		catch(InterruptedException e) {
			e.printStackTrace();
		}

		synchronized(Main.class) {
		    id = (id + 1) % CAPACITY;
		    v[id] = value;
        }

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

        int value;

        synchronized(Main.class) {
            value = v[id];
            id = id - 1;
            if(id < 0) {
                id = CAPACITY - 1;
            }
        }

        semaphoreProd.release();

        return value;
    }
}
