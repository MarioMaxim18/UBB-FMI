package filter;

import domain.Dentist;

public class FilterDentistBySpecialty implements AbstractFilter<Dentist> {
    private String specialty;

    public FilterDentistBySpecialty(String specialty) {
        this.specialty = specialty;
    }

    @Override
    public boolean accept(Dentist dentist) {
        return dentist.getSpecialty().equals(specialty);
    }
}
