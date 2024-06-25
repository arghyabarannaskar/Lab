package MemberList;

public class Member {
    private String memberId;
    private String name;
    private String dateOfBirth;
    private int booksIssued;

    public Member(String memberId, String name, String dateOfBirth) {
        this.memberId = memberId;
        this.name = name;
        this.dateOfBirth = dateOfBirth;
        this.booksIssued = 0;
    }

    public String getMemberId() {
        return memberId;
    }

    public String getName() {
        return name;
    }

    public String getDateOfBirth() {
        return dateOfBirth;
    }

    public int getBooksIssued() {
        return booksIssued;
    }

    public void incrementBooksIssued() {
        booksIssued++;
    }

    public void decrementBooksIssued() {
        booksIssued--;
    }
}

