package domain;

public class Dentist implements Identifiable {
    private int id;
    protected String name;
    private String specialty;
    private double grade;

    public Dentist(int id, String name, String specialty, double grade) {
        this.id = id;
        this.name = name;
        this.specialty = specialty;
        this.grade = grade;
    }

    public Dentist() {
    }

    @Override
    public int getId() {
        return id;
    }

    @Override
    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getSpecialty() {
        return specialty;
    }

    public void setSpecialty(String specialty) {
        this.specialty = specialty;
    }

    public double getGrade() {
        return grade;
    }

    public void setGrade(double grade) {
        this.grade = grade;
    }

    @Override
    public String toString() {
        return "id: " + id + ", name: " + name + ", specialty: " + specialty + ", grade: " + grade;
    }
}