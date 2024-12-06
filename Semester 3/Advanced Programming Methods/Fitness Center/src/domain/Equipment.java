package domain;

abstract public class Equipment {
    private int serialNumber;
    private boolean maintenance;

    public Equipment(int serialNumber, boolean maintenance) {
        this.serialNumber = serialNumber;
        this.maintenance = maintenance;
    }

    public int getSerialNumber() {
        return serialNumber;
    }

    public void setSerialNumber(int serialNumber) {
        this.serialNumber = serialNumber;
    }

    public boolean getMaintenance() {
        return maintenance;
    }

    public void setMaintenance(boolean maintenance) {
        this.maintenance = maintenance;
    }

    public abstract double computePrice();

    @Override
    public String toString() {
        return "serialNumber: " + serialNumber + ", maintenance: " + maintenance;
    }
}
