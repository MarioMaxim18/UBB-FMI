package domain;

public class Bacteria {
    private String name;
    private String category;
    private String description;
    private String symptoms;

    public Bacteria(String name, String category, String description, String symptoms) {
        this.name = name;
        this.description = description;
        this.category = category;
        this.symptoms = symptoms;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getCategory() {
        return category;
    }

    public void setCategory(String category) {
        this.category = category;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public String getSymptoms() {
        return symptoms;
    }

    public void setSymptoms(String symptoms) {
        this.symptoms = symptoms;
    }

    @Override
    public String toString() {
        return  name + " | " + category + " | " + description;
    }
}
