package domain;

public class Medicine {
    private String name;
    private String category;
    private String description;
    private String effects;

    public Medicine(String name, String category, String description, String effects) {
        this.name = name;
        this.category = category;
        this.description = description;
        this.effects = effects;
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

    public String getEffects() {
        return effects;
    }

    public void setEffects(String effects) {
        this.effects = effects;
    }

    @Override
    public String toString() {
        return  name + " | " + category + " | " + description;
    }
}
