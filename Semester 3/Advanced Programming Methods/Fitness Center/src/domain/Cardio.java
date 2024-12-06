package domain;

public class Cardio extends Equipment {
    private int resistance;

    public Cardio(int serialNumber, boolean maintenance, int resistance) {
        super(serialNumber, maintenance);
        this.resistance = resistance;
    }

    public int getResistance() {
        return resistance;
    }

    public void setResistance(int resistance) {
        this.resistance = resistance;
    }

    @Override
    public double computePrice() {
        double price = 0;
        if (resistance < 10) {
            price = 500;
        } else {
            price = 200;
        }
        return price;
    }

    @Override
    public String toString() {
        return "Cardio machine{" + super.toString()+ ", resistance: " + resistance + ", Price: " + computePrice() + '}';
    }
}
