package domain;

public class Compute extends Resource {
    private int cores;

    public Compute(String identifier, String expirationDate, int cores) {
        super(identifier, expirationDate);
        this.cores = cores;
    }

    public int getCores() {
        return cores;
    }

    public void setCores(int cores) {
        this.cores = cores;
    }

    @Override
    public double computeScore() {
        if (cores < 8) {
            return 50.00;
        }
        return 100.00;
    }

    @Override
    public String toString() {
        return "Compute resource[" + super.toString() + ", Cores: " + cores + ", Score: " + computeScore() + "]";
    }
}
