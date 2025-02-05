package domain;

public class Patient extends Entity<Integer> {
    private String name;
    private int address;

    public Patient(Integer id, String name, int address) {
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
