package domain;

public class SmokeSensor extends  Sensor {
    private double length;

    public SmokeSensor(String producer, double lastRecording, double length) {
        super(producer, lastRecording);
        this.length = length;
    }

    public double getLength() {
        return length;
    }

    public void setLength(double length) {
        this.length = length;
    }

    @Override
    public double computePrice() {
        return 25.00;
    }

    @Override
    public boolean emitAlert() {
        if (getLastRecording() > 1600) {
            return true;
        }
        return false;
    }

    @Override
    public String toString() {
        return "Smoke sensor[" + super.toString() + ", Length: " + length + ", Price: " + computePrice() + ", Alert: " + emitAlert() + "]";
    }
}
