package domain;

abstract public class Resource {
    private String identifier;
    private String expirationDate;

    public Resource(String identifier, String expirationDate) {
        this.identifier = identifier;
        this.expirationDate = expirationDate;
    }

    public String getIdentifier() {
        return identifier;
    }

    public void setIdentifier(String identifier) {
        this.identifier = identifier;
    }

    public String getExpirationDate() {
        return expirationDate;
    }

    public void setExpirationDate(String expirationDate) {
        this.expirationDate = expirationDate;
    }

    public abstract double computeScore();

    @Override
    public String toString() {
        return "Identifier: " + identifier + ", Expiration date: " + expirationDate;
    }
}
