package domain;

public class Appointment implements Identifiable {
    private int id;
    private int time;
    private Dentist dentist;

    public Appointment(Dentist dentist, int id, int time) {
        this.dentist = dentist;
        this.id = id;
        this.time = time;
    }

    @Override
    public int getId() {
        return id;
    }

    public int getTime() {
        return time;
    }

    public Dentist getDentist() {
        return dentist;
    }

    @Override
    public void setId(int id) {
        this.id = id;
    }

    public void setTime(int time) {
        this.time = time;
    }

    public void setDentist(Dentist dentist) {
        this.dentist = dentist;
    }

    @Override
    public String toString() {
        return "dentist: " + dentist.getName() + ", id: " + id + ", time: " + time;
    }
}