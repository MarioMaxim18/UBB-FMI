package filter;

import domain.Appointment;

public class FilterAppointmentByTime implements AbstractFilter<Appointment> {
    private int time;

    public FilterAppointmentByTime(int time) {
        this.time = time;
    }

    @Override
    public boolean accept(Appointment appointment) {
        return appointment.getTime() == time;
    }
}
