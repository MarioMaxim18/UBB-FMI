package filter;

import domain.Dentist;

public class FilterDentistByGrade implements  AbstractFilter<Dentist> {
    private double grade;

    public FilterDentistByGrade(double grade) {
        this.grade = grade;
    }

    @Override
    public boolean accept(Dentist dentist) {
        return dentist.getGrade() == grade;
    }
}
