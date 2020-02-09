package bug1;
/**
 * @author cristian.chilipirea
 * 
 *         Why is value set correct even though we do not use
 *         locks/synchronized?
 *
 *			In main() se apeleaza mereu run in loc de start,
 *		    deci e ca si cum rularea este secventiala
 *		    Daca se inlocuieste run cu start, atunci thread-urile vor
 *		    rula in paralel
 *		   	+ ca sa mearga trebuie sa apelez synchronized in blocul in care
 *		   	se incremeneteaza value
 *
 *         DO NOT MODIFY
 */
public class MyThread implements Runnable {
	static int value = 0;

	@Override
	public void run() {
		for (int i = 0; i < Main.N; i++) {
			synchronized (Main.class) {
				value = value + 3;
			}
		}
	}
}
