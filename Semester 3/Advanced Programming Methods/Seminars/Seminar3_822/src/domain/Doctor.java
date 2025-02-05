package domain;

import java.util.Objects;

public class Doctor extends Entity<Integer> {
    private String name;
    private String specialty;
    private double grade;

    public Doctor(Integer id, String name, String specialty, double grade) {
        super(id);
        this.name = name;
        this.specialty = specialty;
        this.grade = grade;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Doctor doctor = (Doctor) o;
        return id == doctor.id && Double.compare(grade, doctor.grade) == 0 && Objects.equals(name, doctor.name) && Objects.equals(specialty, doctor.specialty);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, name, specialty, grade);
    }

    @Override
    public String toString() {
        return id + " " + name + " " + specialty + " " + grade;
    }

    public double getGrade() {
        return grade;
    }

    public String getName() {
        return name;
    }

    public String getSpecialty() {
        return specialty;
    }
}
