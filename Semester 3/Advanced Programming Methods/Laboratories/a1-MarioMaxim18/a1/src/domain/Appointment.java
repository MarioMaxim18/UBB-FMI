package domain;

public class Appointment {
    protected int id;
    protected int time;
    protected Dentist dentist;

    public Appointment(Dentist dentist,  int id, int time) {
        this.dentist = dentist;
        this.id = id;
        this.time = time;
    }

    public int getId() {
        return id;
    }

    public int getTime() {
        return time;
    }

    public Dentist getDentist() {
        return dentist;
    }

    public void setId(int id) {
        this.id = id;
    }

    public void setTime(int time) {
        this.time = time;
    }

    public void setDentist(Dentist dentist) {
        this.dentist = dentist;
    }

    public String tooString()  {
        return "Dentist: " +  dentist.getName() + " " +  "Id: " + id + " " + "time: " + time;
    }
}
