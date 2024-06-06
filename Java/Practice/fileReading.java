import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class fileReading{
  public static void main(String[] args) {
    // The try-with-resources statement automatically closes the reader
    try (BufferedReader reader = new BufferedReader(new FileReader("example.txt"))) {
      String line;
      while ((line = reader.readLine()) != null) {
        System.out.println(line);
      }
    } catch (IOException e) {
      System.out.println("An error occurred.");
      e.printStackTrace();
    }
  }
}

