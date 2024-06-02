import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Scanner;

public class ContinuousInputToFile {
    public static void main(String[] args) {
        String filename = "output.txt";
        String delimiter = "STOP";

        // Writing to file
        try (Scanner scanner = new Scanner(System.in);
             BufferedWriter writer = new BufferedWriter(new FileWriter(filename))) {

            System.out.println("Enter text to write to the file (type 'STOP' to finish):");

            while (true) {
                String input = scanner.nextLine();

                // Check for delimiter
                if (input.equalsIgnoreCase(delimiter)) {
                    break;
                }

                // Write input to file
                writer.write(input);
                writer.newLine();  // Write a new line
            }

            System.out.println("Data written to the file successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
        }

        // Reading from file
        System.out.println("\nReading from the file:");
        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = br.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
 
    

