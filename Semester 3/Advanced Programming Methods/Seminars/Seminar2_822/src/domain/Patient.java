package domain;

public class Patient extends Entity {
    private String name;
    private int address;

    public Patient(int id, String name, int address) {
        super(id);
        this.name = name;
        this.address = address;
    }

    @Override
    public String toString() {
        return "Patient{" +
                "name='" + name + '\'' +
                ", address=" + address +
                '}';
    }
}
