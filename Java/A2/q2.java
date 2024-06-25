import java.util.Scanner;

class Account {
    private int bal;

    public Account(int bal) {
        this.bal = bal;
    }

    public Boolean isSufficientBalance(int w) {
        if (bal >= w)
            return true;
        else
            return false;
    }

    public void withdraw(int amt) {
        bal = bal - amt;
        System.out.println("Withdrawl money is " + amt);
        System.out.println("your current balance is " + bal);
    }
}

class Customer implements Runnable {
    private String name;
    private Account account;

    public Customer(String name, Account account) {
        this.name = name;
        this.account = account;
    }

    public void run() {
        Scanner kb = new Scanner(System.in);
        
        // synchronized (account) {
            System.out.println("Enter amount to withdraw");
            int amt = kb.nextInt();
            if (account.isSufficientBalance(amt)) {
                System.out.println(name);
                account.withdraw(amt);
            }else System.out.println("insufficient balance");
        // }
    }
}

public class q2 {
    public static void main(String[] args) {
        Account acc = new Account(1000);
        Customer c1 = new Customer("Raj", acc);
        Customer c2 = new Customer("Simran", acc);

        Thread t1 = new Thread(c1);
        Thread t2 = new Thread(c2);
        t1.start();
        t2.start();
    }
}
