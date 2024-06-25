package Transaction;

import BookList.BookList;
import MemberList.MemberList;

public class TransactionList {
    private Transaction[] transactions;
    private int size;
    private static final int MAX_SIZE = 100; // Maximum number of transactions

    public TransactionList() {
        transactions = new Transaction[MAX_SIZE];
        size = 0;
    }

    public void issueBook(String memberId, String bookId, BookList bookList, MemberList memberList) {
        // Check book availability
        boolean bookAvailable = false;
        for (int i = 0; i < bookList.getSize(); i++) {
            if (bookList.getBook(i).getBookId().equals(bookId) && bookList.getBook(i).getAvailableCopies() > 0) {
                bookAvailable = true;
                break;
            }
        }
        if (!bookAvailable) {
            System.out.println("Book not available.");
            return;
        }

        // Check member eligibility
        boolean memberEligible = false;
        for (int i = 0; i < memberList.getSize(); i++) {
            if (memberList.getMember(i).getMemberId().equals(memberId) && memberList.getMember(i).getBooksIssued() < 3) {
                memberEligible = true;
                break;
            }
        }
        if (!memberEligible) {
            System.out.println("Member not eligible to issue more books.");
            return;
        }
        
        // Issue book
        for (int i = 0; i < bookList.getSize(); i++) {
            if (bookList.getBook(i).getBookId().equals(bookId)) {
                bookList.getBook(i).decreaseCopies(1);
                break;
            }
        }
        for (int i = 0; i < memberList.getSize(); i++) {
            if (memberList.getMember(i).getMemberId().equals(memberId)) {
                memberList.getMember(i).incrementBooksIssued();
                break;
            }
        }
        transactions[size++] = new Transaction(memberId, bookId);
    }

    public void returnBook(String memberId, String bookId, BookList bookList, MemberList memberList) {
        for (int i = 0; i < size; i++) {
            if (transactions[i].getMemberId().equals(memberId) && transactions[i].getBookId().equals(bookId)) {
                transactions[i].markReturned();
                break;
            }
        }
        for (int i = 0; i < bookList.getSize(); i++) {
            if (bookList.getBook(i).getBookId().equals(bookId)) {
                bookList.getBook(i).increaseCopies(1);
                break;
            }
        }
        for (int i = 0; i < memberList.getSize(); i++) {
            if (memberList.getMember(i).getMemberId().equals(memberId)) {
                memberList.getMember(i).decrementBooksIssued();
                break;
            }
        }
    }
}
