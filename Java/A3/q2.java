package A3;

class Account {
    private String accountNumber;
    private String accountName;
    private double balance;

    public Account(String accountNumber, String accountName, double balance) {
        this.accountNumber = accountNumber;
        this.accountName = accountName;
        this.balance = balance;
    }

    public String getAccountNumber() {
        return accountNumber;
    }

    public String getAccountName() {
        return accountName;
    }

    public double getBalance() {
        return balance;
    }

    @Override
    public String toString() {
        return "Account Number: " + accountNumber + ", Name: " + accountName + ", Balance: " + balance;
    }
}

import java.util.ArrayList;
import java.util.List;

class Bank {
    private List<Account> accounts;

    public Bank() {
        this.accounts = new ArrayList<>();
    }

    public boolean addAccount(Account account) {
        for (Account acc : accounts) {
            if (acc.getAccountNumber().equals(account.getAccountNumber())) {
                return false; // Account number must be unique
            }
        }
        accounts.add(account);
        return true;
    }

    public boolean accountExists(String accountNumber) {
        for (Account acc : accounts) {
            if (acc.getAccountNumber().equals(accountNumber)) {
                return true;
            }
        }
        return false;
    }

    public Double getBalance(String accountNumber) {
        for (Account acc : accounts) {
            if (acc.getAccountNumber().equals(accountNumber)) {
                return acc.getBalance();
            }
        }
        return null; // Account not found
    }

    public void displayAllAccounts() {
        for (Account acc : accounts) {
            System.out.println(acc);
        }
    }

    public static void main(String[] args) {
        Bank bank = new Bank();
        
        // Adding accounts
        bank.addAccount(new Account("001", "John Doe", 1000.0));
        bank.addAccount(new Account("002", "Jane Smith", 2000.0));
        bank.addAccount(new Account("003", "Alice Johnson", 3000.0));

        // Display all accounts
        System.out.println("All accounts:");
        bank.displayAllAccounts();

        // Check existence of an account
        String accountToCheck = "002";
        if (bank.accountExists(accountToCheck)) {
            System.out.println("Account " + accountToCheck + " exists.");
        } else {
            System.out.println("Account " + accountToCheck + " does not exist.");
        }

        // Get balance for a specific account
        String accountToGetBalance = "003";
        Double balance = bank.getBalance(accountToGetBalance);
        if (balance != null) {
            System.out.println("The balance for account " + accountToGetBalance + " is " + balance);
        } else {
            System.out.println("Account " + accountToGetBalance + " not found.");
        }
    }
}

