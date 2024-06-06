class MyException extends Exception {
    private String message;
    public MyException(String message) {
        this.message = message;
    }

    public String getMessage(){
        return message;
    }
}

public class p{
    public static void main(String[] args) {
        try{
            throw new MyException("Exeception thrown");
        }catch(MyException e){
            System.out.println(e.getMessage());
        }
    }
}