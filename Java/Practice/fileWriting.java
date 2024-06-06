import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class fileWriting {
  public static void main(String[] args) {
    File myFile = new File("example.txt");
    try {
      if (myFile.createNewFile()) {
        System.out.println("File created: " + myFile.getName());
      } else {
        System.out.println("File already exists.");
      }
      try (BufferedWriter writer = new BufferedWriter(new FileWriter(myFile))) {
        writer.write("Hello, world!");
        writer.newLine(); // to add a new line
        writer.write("This is written with createNewFile.");
      }
    } catch (IOException e) {
      System.out.println("An error occurred.");
      e.printStackTrace();
    }
  }
}
