import java.io.*;

public class FileCopy {
    public static void main(String[] args) {
        String sourceFile = "source.txt"; // Path of the source text file
        String destinationFile = "destination.txt"; // Path of the destination text file

        try (BufferedReader reader = new BufferedReader(new FileReader(sourceFile));
             BufferedWriter writer = new BufferedWriter(new FileWriter(destinationFile))) {
            String line;
            // Read from the source file and write to the destination file
            while ((line = reader.readLine()) != null) {
                writer.write(line);
                writer.newLine(); // Add newline character after each line
            }

            System.out.println("File copied successfully from " + sourceFile + " to " + destinationFile);
        } catch (IOException e) {
            System.out.println("An error occurred while copying the file.");
            e.printStackTrace();
        }
    }
}

