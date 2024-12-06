package domain;

public class TemperatureSensor extends Sensor {
    private double diameter;

    public TemperatureSensor(String producer, double lastRecording, double diameter) {
        super(producer, lastRecording);
        this.diameter = diameter;
    }

    public double getDiameter() {
        return diameter;
    }

    public void setDiameter(int diameter) {
        this.diameter = diameter;
    }

    @Override
    public double computePrice() {
        double basePrice = 9;
        if (diameter < 3) {
            basePrice += 8;
        }
        return basePrice;
    }

    @Override
     public boolean emitAlert() {
        if (getLastRecording() < 10 || getLastRecording() > 35) {
            return true;
        }
        return false;
    }

    @Override
    public String toString() {
        return "Temperature sensor[" + super.toString() + ", Diameter: " + diameter + ", Price: " + computePrice() + ", Alert: " + emitAlert() + "]";
    }
}
