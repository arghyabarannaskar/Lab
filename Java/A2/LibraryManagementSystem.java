package LibraryManagement;

import BookList.Book;
import MemberList.Member;

public interface LibraryManagementSystem {
    // Add book to the library
    void addBook(Book book);

    // Search for a book by its ID or title
    Book searchBook(String bookId);

    // View all books in the library
    void viewAllBooks();

    // Add a new member to the library
    void addMember(Member member);

    // Search for a member by ID or name
    Member searchMember(String memberId);

    // View all members in the library
    void viewAllMembers();

    // Issue a book to a member
    void issueBook(String memberId, String bookId);

    // Return a book issued by a member
    void returnBook(String memberId, String bookId);
}
