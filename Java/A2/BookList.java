package BookList;

public class BookList {
    private Book[] books;
    private int size;
    private static final int MAX_SIZE = 100; // Maximum number of books

    public BookList() {
        books = new Book[MAX_SIZE];
        size = 0;
    }

    public void addBook(Book book) {
        // Check if bookId already exists
        for (int i = 0; i < size; i++) {
            if (books[i].getBookId().equals(book.getBookId())) {
                System.out.println("Book ID already exists.");
                return;
            }
        }
        // Add book to the list
        if (size < MAX_SIZE) {
            books[size++] = book;
        } else {
            System.out.println("Book list is full.");
        }
    }

    public void addCopies(String bookId, int copies) {
        for (int i = 0; i < size; i++) {
            if (books[i].getBookId().equals(bookId)) {
                books[i].increaseCopies(copies);
                return;
            }
        }
        System.out.println("Book not found.");
    }

    public void showAllBooks() {
        for (int i = 0; i < size; i++) {
            System.out.println(books[i].getTitle() + " (" + books[i].getBookId() + ")");
        }
    }

    public void showBookDetails(String bookId) {
        for (int i = 0; i < size; i++) {
            if (books[i].getBookId().equals(bookId)) {
                System.out.println("Title: " + books[i].getTitle());
                System.out.println("Book ID: " + books[i].getBookId());
                System.out.println("Total Copies: " + books[i].getTotalCopies());
                System.out.println("Available Copies: " + books[i].getAvailableCopies());
                return;
            }
        }
        System.out.println("Book not found.");
    }
}