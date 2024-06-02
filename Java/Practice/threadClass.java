class A extends Thread {
    public void run() {
        int i;
        for (i = 0; i < 10; i++) {
            System.out.println("A" + i);
        }
    }
}

class B extends Thread {
    public void run() {
        int i;
        for (i = 0; i < 10; i++) {
            System.out.println("B"+i);
        }
    }
}

public class threadClass {
    public static void main(String[] args) {
        A t1 = new A();
        B t2 = new B();

        t1.start();
        t2.start();
    }
}
