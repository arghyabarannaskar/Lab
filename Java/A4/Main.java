import java.util.Scanner;

public class Main {
    public static int sharedVariable = 0;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter increment amount: ");
        int incrementAmount = scanner.nextInt();

        int decrementAmount = 10; // Fixed decrement amount

        // Create runnables for increment and decrement operations
        Runnable incrementRunnable = new IncrementRunnable(incrementAmount);
        Runnable decrementRunnable = new DecrementRunnable(decrementAmount);

        // Create threads with the runnables
        Thread incThread1 = new Thread(incrementRunnable);
        Thread incThread2 = new Thread(incrementRunnable);
        Thread decThread1 = new Thread(decrementRunnable);
        Thread decThread2 = new Thread(decrementRunnable);

        // Start all threads
        incThread1.start();
        incThread2.start();
        decThread1.start();
        decThread2.start();

        // Wait for all threads to finish
        try {
            incThread1.join();
            incThread2.join();
            decThread1.join();
            decThread2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // Display the final value
        System.out.println("Final value of the variable: " + sharedVariable);

        scanner.close();
    }

    static class IncrementRunnable implements Runnable {
        private int amount;

        public IncrementRunnable(int amount) {
            this.amount = amount;
        }

        @Override
        public void run() {
            increment(amount);
        }
    }

    static class DecrementRunnable implements Runnable {
        private int amount;

        public DecrementRunnable(int amount) {
            this.amount = amount;
        }

        @Override
        public void run() {
            decrement(amount);
        }
    }

    public static synchronized void increment(int amount) {
        sharedVariable += amount;
        System.out.println("Incremented by " + amount + ", new value: " + sharedVariable);
    }

    public static synchronized void decrement(int amount) {
        sharedVariable -= amount;
        System.out.println("Decremented by " + amount + ", new value: " + sharedVariable);
    }
}
