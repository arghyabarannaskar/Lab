package BookList;

public class Book {
    private String bookId;
    private String title;
    private int totalCopies;
    private int availableCopies;

    public Book(String bookId, String title, int totalCopies, int availableCopies) {
        this.bookId = bookId;
        this.title = title;
        this.totalCopies = totalCopies;
        this.availableCopies = availableCopies;
    }

    public String getBookId() {
        return bookId;
    }

    public String getTitle() {
        return title;
    }

    public int getTotalCopies() {
        return totalCopies;
    }

    public int getAvailableCopies() {
        return availableCopies;
    }

    public void increaseCopies(int copies) {
        totalCopies += copies;
        availableCopies += copies;
    }

    public void decreaseCopies(int copies) {
        totalCopies -= copies;
        availableCopies -= copies;
    }
}
