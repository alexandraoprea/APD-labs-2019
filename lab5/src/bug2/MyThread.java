package bug2;
/**
 * @author cristian.chilipirea
 * 
 *         Why does this code not block? We took the same lock twice!
 *
 * 		   Atunci cand un thread detine lock-ul unui obiect, si incearca
 * 		   din nou sa obtina lock-ul acelui obiect, nu se produce deadlock,
 * 		   ci operatia se produce cu succes
 *
 * 		   --se numeste reentrant synchronization
 */
public class MyThread implements Runnable {
	static int i;

	@Override
	public void run() {
		synchronized (this) {
			synchronized (this) {
				i++;
			}
		}
	}
}
