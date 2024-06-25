package MemberList;

public class MemberList {
    private Member[] members;
    private int size;
    private static final int MAX_SIZE = 100; // Maximum number of members

    public MemberList() {
        members = new Member[MAX_SIZE];
        size = 0;
    }

    public void addMember(Member member) {
        // Check if memberId already exists
        for (int i = 0; i < size; i++) {
            if (members[i].getMemberId().equals(member.getMemberId())) {
                System.out.println("Member ID already exists.");
                return;
            }
        }
        // Add member to the list
        if (size < MAX_SIZE) {
            members[size++] = member;
        } else {
            System.out.println("Member list is full.");
        }
    }

    public void showAllMembers() {
        for (int i = 0; i < size; i++) {
            System.out.println(members[i].getName() + " (" + members[i].getMemberId() + ")");
        }
    }

    public void showMemberDetails(String memberId) {
        for (int i = 0; i < size; i++) {
            if (members[i].getMemberId().equals(memberId)) {
                System.out.println("Name: " + members[i].getName());
                System.out.println("Member ID: " + members[i].getMemberId());
                System.out.println("Date of Birth: " + members[i].getDateOfBirth());
                System.out.println("Books Issued: " + members[i].getBooksIssued());
                return;
            }
        }
        System.out.println("Member not found.");
    }
}

