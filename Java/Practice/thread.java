class A implements Runnable {
    public void run() {
        int i;
        for (i = 0; i < 10; i++) {
            System.out.println("A" + i);
        }
    }
}

class B implements Runnable {
    public void run() {
        int i;
        for (i = 0; i < 10; i++) {
            System.out.println("B" + i);
        }
    }
}



public class thread{
    public static void main(String[] args) {
        Thread t1 = new Thread(new A());
        Thread t2 = new Thread(new B());
        // t1.setPriority(2);
        // t2.setPriority(1);
        t1.start();
        t2.start();
    }
}