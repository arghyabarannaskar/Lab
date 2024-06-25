import BookList.Book;
import BookList.BookList;
import MemberList.Member;
import MemberList.MemberList;
import Transaction.TransactionList;

public class Main {
    public static void main(String[] args) {
        // Create book list
        BookList bookList = new BookList();
        bookList.addBook(new Book("B001", "Book 1", 10, 10));
        bookList.addBook(new Book("B002", "Book 2", 5, 5));
        bookList.addBook(new Book("B003", "Book 3", 8, 8));

        // Create member list
        MemberList memberList = new MemberList();
        memberList.addMember(new Member("M001", "John Doe", "1990-01-01"));
        memberList.addMember(new Member("M002", "Jane Smith", "1985-05-15"));
        memberList.addMember(new Member("M003", "Alice Johnson", "1995-09-30"));

        // Issue book to a member
        TransactionList transactionList = new TransactionList();
        transactionList.issueBook("M001", "B001", bookList, memberList);

        // Show all books and members
        System.out.println("Books:");
        bookList.showAllBooks();
        System.out.println("\nMembers:");
        memberList.showAllMembers();

        // Return book
        transactionList.returnBook("M001", "B001", bookList, memberList);

        // Show updated book details
        System.out.println("\nAfter returning the book:");
        bookList.showBookDetails("B001");
    }
}

