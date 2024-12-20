package filter;

import domain.Appointment;
import domain.Dentist;

public class FilterAppointmentByDentist implements AbstractFilter<Appointment> {
    private Dentist dentist;

    public FilterAppointmentByDentist(Dentist dentist) {
        this.dentist = dentist;
    }

    @Override
    public boolean accept(Appointment appointment) {
        return appointment.getDentist().getName().equals(dentist.getName());
    }
}
