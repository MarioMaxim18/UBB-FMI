package domain;

public class Recipe {
    private String name;
    private String cuisine;
    private String description;
    private String ingredients;

    public Recipe(String name, String cuisine, String description, String ingredients) {
        this.name = name;
        this.cuisine = cuisine;
        this.description = description;
        this.ingredients = ingredients;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getCuisine() {
        return cuisine;
    }

    public void setCuisine(String cuisine) {
        this.cuisine = cuisine;
    }

    public String getIngredients() {
        return ingredients;
    }

    public void setIngredients(String ingredients) {
        this.ingredients = ingredients;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    @Override
    public String toString() {
        return  name + " | " + cuisine + " | " + description;
    }
}
