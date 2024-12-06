package domain;

public abstract class Sensor {
    private String producer;
    private double lastRecording;

    public Sensor(String producer, double lastRecording) {
        this.producer = producer;
        this.lastRecording = lastRecording;
    }

    public double getLastRecording() {
        return lastRecording;
    }

    public void setLastRecording(double lastRecording) {
        this.lastRecording = lastRecording;
    }

    public String getProducer() {
        return producer;
    }

    public void setProducer(String producer) {
        this.producer = producer;
    }

    public abstract double computePrice();
    public abstract boolean emitAlert();

    @Override
    public String toString() {
        return "Producer: " + producer  + ", Last recording: " + lastRecording;
    }
}
