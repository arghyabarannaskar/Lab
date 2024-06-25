package Transaction;

public class Transaction {
    private String memberId;
    private String bookId;
    private static final String MARKER = "xxxx";

    public Transaction(String memberId, String bookId) {
        this.memberId = memberId;
        this.bookId = bookId;
    }

    public String getMemberId() {
        return memberId;
    }

    public String getBookId() {
        return bookId;
    }

    public void setMemberId(String memberId) {
        this.memberId = memberId;
    }

    public void markReturned() {
        memberId = MARKER;
    }
}


