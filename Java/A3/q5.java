package A3;

import java.io.Serializable;

class Student implements Serializable {
    private static final long serialVersionUID = 1L; // To maintain version compatibility during serialization
    private int roll;
    private String name;
    private double score;

    public Student(int roll, String name, double score) {
        this.roll = roll;
        this.name = name;
        this.score = score;
    }

    public int getRoll() {
        return roll;
    }

    public String getName() {
        return name;
    }

    public double getScore() {
        return score;
    }

    @Override
    public String toString() {
        return "Roll: " + roll + ", Name: " + name + ", Score: " + score;
    }
}

import java.io.*;
import java.util.ArrayList;
import java.util.List;

class StudentSerialization {
    private static final String FILE_NAME = "students.ser";

    public static void main(String[] args) {
        List<Student> students = new ArrayList<>();
        students.add(new Student(1, "John Doe", 85.5));
        students.add(new Student(2, "Jane Smith", 92.0));
        students.add(new Student(3, "Alice Johnson", 78.5));

        // Serialize the list of students
        writeStudentsToFile(students);

        // Deserialize the list of students
        List<Student> deserializedStudents = readStudentsFromFile();

        // Display deserialized students
        System.out.println("Deserialized Students:");
        for (Student student : deserializedStudents) {
            System.out.println(student);
        }
    }

    private static void writeStudentsToFile(List<Student> students) {
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(FILE_NAME))) {
            oos.writeObject(students);
            System.out.println("Students have been serialized to " + FILE_NAME);
        } catch (IOException e) {
            System.err.println("Error while serializing students: " + e.getMessage());
        }
    }

    private static List<Student> readStudentsFromFile() {
        List<Student> students = null;
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(FILE_NAME))) {
            students = (List<Student>) ois.readObject();
            System.out.println("Students have been deserialized from " + FILE_NAME);
        } catch (IOException | ClassNotFoundException e) {
            System.err.println("Error while deserializing students: " + e.getMessage());
        }
        return students;
    }
}
