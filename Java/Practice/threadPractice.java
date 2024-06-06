// class Mythread extends Thread {
//     private String id;

//     public Mythread(String id) {
//         this.id = id;
//     }
//     public void run() {
//         System.out.println(this.id);
//     }
// }

class Mythread implements Runnable {
    public void run(){
        System.out.println(Thread);
    }
}



public class threadPractice {
    public static void main(String[] args) {
        int n = 8;
        for(int i = 0; i<n; i++){
            Mythread obj = new Mythread("1");
            Mythread obj2 = new Mythread("2");
            obj.start();
            obj2.start();
        }
    }
}
