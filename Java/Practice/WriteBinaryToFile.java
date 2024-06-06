import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class WriteBinaryToFile {
    public static void main(String[] args) {
        String text = "I am awesome";

        // Convert the string to bytes using UTF-8 encoding
        byte[] bytes = text.getBytes();

        String fileName = "binaryfile.dat";

        try (BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(fileName))) {
            bos.write(bytes);
            System.out.println("Text written to the file in binary mode: " + fileName);
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }
    }
}
