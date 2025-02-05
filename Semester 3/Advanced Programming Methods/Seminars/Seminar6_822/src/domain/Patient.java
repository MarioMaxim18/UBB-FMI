package domain;

public class Patient extends Entity<Integer> {
    private String name;
    private String address;

    public Patient(Integer id, String name, String address) {
        super(id);
        this.name = name;
        this.address = address;
    }

    public String getName() {
        return name;
    }

    @Override
    public String toString() {
        return "Patient{" +
                "name='" + name + '\'' +
                ", address=" + address +
                '}';
    }
}
