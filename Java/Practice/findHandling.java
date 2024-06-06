import java.io.*;

public class findHandling {
    public static void main(String[] args) {
        String fileName = "binaryfile.dat";
        
        try (BufferedInputStream bis = new BufferedInputStream(new FileInputStream(fileName))) {
            byte[] buffer = new byte[1024];
            int bytesRead;

            // Read bytes from the file into the buffer
            while ((bytesRead = bis.read(buffer)) != -1) {
                // Convert bytes to string using UTF-8 encoding
                String text = new String(buffer, 0, bytesRead, "UTF-8");
                System.out.println("Text read from file: " + text);
            }
        } catch (IOException e) {
            System.out.println("An error occurred while reading from the file.");
            e.printStackTrace();
        }
    }
}





