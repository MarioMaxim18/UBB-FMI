package domain;

import java.util.Objects;

public class Strength extends Equipment {
    private int motionLevel;
    private String muscleGroup;

    public Strength(int serialNumber, boolean maintenance, int motionLevel, String muscleGroup) {
        super(serialNumber, maintenance);
        this.muscleGroup = muscleGroup;
        this.motionLevel = motionLevel;
    }

    public int getMotionLevel() {
        return motionLevel;
    }

    public void setMotionLevel(int motionLevel) {
        this.motionLevel = motionLevel;
    }

    public String getMuscleGroup() {
        return muscleGroup;
    }

    public void setMuscleGroup(String muscleGroup) {
        this.muscleGroup = muscleGroup;
    }

    @Override
    public double computePrice() {
        double price = 0;
        if (Objects.equals(muscleGroup, "arms") || Objects.equals(muscleGroup, "legs")) {
            price = 600;
        } else {
            price = 800;
        }
        return price;
    }

    @Override
    public String toString() {
        return "Strength training machine{" + super.toString()+ ", motionLevel: " + motionLevel + ", muscleGroup: " + muscleGroup + ", Price: " + computePrice() + '}';
    }
}
