import java.util.concurrent.Semaphore;

class Reader implements Runnable {
    private ReaderWriter readerWriter;

    public Reader(ReaderWriter readerWriter) {
        this.readerWriter = readerWriter;
    }

    public void run() {
        while (true) {
            readerWriter.read();
            try {
                Thread.sleep(1000); // Simulate delay
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                break;
            }
        }
    }
}

class Writer implements Runnable {
    private ReaderWriter readerWriter;

    public Writer(ReaderWriter readerWriter) {
        this.readerWriter = readerWriter;
    }

    public void run() {
        while (true) {
            readerWriter.write();
            try {
                Thread.sleep(2000); // Simulate delay
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                break;
            }
        }
    }
}

public class ReaderWriter {
    private Semaphore mutex = new Semaphore(1); // Semaphore for mutual exclusion
    private Semaphore db = new Semaphore(1);    // Semaphore for controlling writers
    private int readerCount = 0;                // Number of readers in critical section

    public void read() {
        try {
            mutex.acquire(); // Acquire mutex to update readerCount
            readerCount++;
            if (readerCount == 1) {
                db.acquire(); // First reader locks writer
            }
            mutex.release();

            // Reading
            System.out.println(Thread.currentThread().getName() + " is reading");

            mutex.acquire(); // Acquire mutex to update readerCount
            readerCount--;
            if (readerCount == 0) {
                db.release(); // Last reader releases writer
            }
            mutex.release();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    public void write() {
        try {
            db.acquire(); // Lock writer
            // Writing
            System.out.println(Thread.currentThread().getName() + " is writing");
            db.release(); // Release writer
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    public static void main(String[] args) {
        ReaderWriter rw = new ReaderWriter();

        // Create reader and writer threads
        Thread reader1 = new Thread(new Reader(rw), "Reader1");
        Thread reader2 = new Thread(new Reader(rw), "Reader2");
        Thread writer1 = new Thread(new Writer(rw), "Writer1");
        Thread writer2 = new Thread(new Writer(rw), "Writer2");

        // Start threads
        reader1.start();
        reader2.start();
        writer1.start();
        writer2.start();
    }
}

