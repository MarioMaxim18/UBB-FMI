package domain;

import java.util.Objects;

public class Storage extends  Resource {
    private int capacity;
    private String type;

    public Storage(String identifier, String expirationDate, int capacity, String type) {
        super(identifier, expirationDate);
        this.capacity = capacity;
        this.type = type;
    }

    public int getCapacity() {
        return capacity;
    }

    public void setCapacity(int capacity) {
        this.capacity = capacity;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    @Override
    public double computeScore() {
        double score = 0;
        if (Objects.equals(type, "HDD")) {
            score = 70;
        } else if (Objects.equals(type, "SSD")) {
            score = 90;
        } else if (Objects.equals(type, "Hybrid")) {
            score = 80;
        }
        return score;
    }

    @Override
    public String toString() {
        return "Storage resource[" + super.toString() + ", Capacity: " + capacity + ", Type: " + type + ", Score: " + computeScore() + "]";
    }
}
