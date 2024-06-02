import java.util.Scanner;

public class q1 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the increment amount: ");
        int incrementAmount = scanner.nextInt();

        int decrementAmount = 10; // Fixed decrement amount

        SharedVariable sharedVariable = new SharedVariable();

        // Create increment and decrement threads
        Thread incrementThread1 = new Thread(new IncrementTask(sharedVariable, incrementAmount));
        Thread incrementThread2 = new Thread(new IncrementTask(sharedVariable, incrementAmount));
        Thread decrementThread1 = new Thread(new DecrementTask(sharedVariable, decrementAmount));
        Thread decrementThread2 = new Thread(new DecrementTask(sharedVariable, decrementAmount));

        // Start all threads
        incrementThread1.start();
        incrementThread2.start();
        decrementThread1.start();
        decrementThread2.start();

        // Wait for all threads to finish
        try {
            incrementThread1.join();
            incrementThread2.join();
            decrementThread1.join();
            decrementThread2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // Display the final value
        System.out.println("Final value of the variable: " + sharedVariable.getValue());
        scanner.close();
    }

    static class IncrementTask implements Runnable {
        private SharedVariable sharedVariable;
        private int incrementAmount;

        public IncrementTask(SharedVariable sharedVariable, int incrementAmount) {
            this.sharedVariable = sharedVariable;
            this.incrementAmount = incrementAmount;
        }

        @Override
        public void run() {
            sharedVariable.increment(incrementAmount);
        }
    }

    static class DecrementTask implements Runnable {
        private SharedVariable sharedVariable;
        private int decrementAmount;

        public DecrementTask(SharedVariable sharedVariable, int decrementAmount) {
            this.sharedVariable = sharedVariable;
            this.decrementAmount = decrementAmount;
        }

        @Override
        public void run() {
            sharedVariable.decrement(decrementAmount);
        }
    }

    static class SharedVariable {
        private int value = 0;

        // Method to increment the value
        public void increment(int amount) {
            value += amount;
            System.out.println("Incremented by " + amount + ", new value: " + value);
        }

        // Method to decrement the value
        public void decrement(int amount) {
            value -= amount;
            System.out.println("Decremented by " + amount + ", new value: " + value);
        }

        // Method to get the current value
        public int getValue() {
            return value;
        }
    }
}
