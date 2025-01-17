package domain;

public class Itinerary {
    private String name;
    private String continent;
    private String description;
    private String placesToVisit;

    public Itinerary(String name, String continent, String description, String placesToVisit) {
        this.name = name;
        this.continent = continent;
        this.description = description;
        this.placesToVisit = placesToVisit;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPlacesToVisit() {
        return placesToVisit;
    }

    public void setPlacesToVisit(String placesToVisit) {
        this.placesToVisit = placesToVisit;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public String getContinent() {
        return continent;
    }

    public void setContinent(String continent) {
        this.continent = continent;
    }

    @Override
    public String toString() {
        return  name + " | " +continent + " | " + description;
    }
}
