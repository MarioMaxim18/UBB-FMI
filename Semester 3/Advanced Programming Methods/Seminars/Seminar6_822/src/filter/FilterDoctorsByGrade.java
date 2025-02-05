package filter;

import domain.Doctor;
import domain.Entity;

public class FilterDoctorsByGrade implements AbstractFilter {
    private double grade;
    public FilterDoctorsByGrade(double grade){
        this.grade=grade;

    }
    public boolean accept(Entity e) {
        if (e instanceof Doctor) {
            Doctor d = (Doctor) e;
            if (d.getGrade()>grade)
                return true;
        }
        return false;

    }

}
