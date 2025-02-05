package filter;

import domain.Doctor;
import domain.Entity;

public class FilterDoctorsBySpecialty implements AbstractFilter{

    @Override
    public boolean accept(Entity e) {
        if(e instanceof Doctor){
            Doctor d=(Doctor)e;
            if(specialty.equals(d.getSpecialty()))
                return true;
        }
        return false;
    }

    private String specialty;
    public FilterDoctorsBySpecialty(String specialty){
        this.specialty=specialty;
    }
}
