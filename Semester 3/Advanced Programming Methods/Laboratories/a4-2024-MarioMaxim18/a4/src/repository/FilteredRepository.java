package repository;

import domain.Identifiable;
import filter.AbstractFilter;
import java.util.ArrayList;
import java.util.List;

public class FilteredRepository<T extends Identifiable> extends MemoryRepository<T> {
    private AbstractFilter<T> filter;

    public FilteredRepository(AbstractFilter<T> filter) {
        if (filter == null) {
            throw new IllegalArgumentException("Filter cannot be null");
        }
        this.filter = filter;
    }

    public void setFilter(AbstractFilter<T> filter) {
        if (filter == null) {
            throw new IllegalArgumentException("Filter cannot be null");
        }
        this.filter = filter;
    }

    @Override
    public Iterable<T> getAllAppointments() {
        List<T> filteredList = new ArrayList<>();
        for (T entity : super.getAllAppointments()) {
            if (filter.accept(entity)) {
                filteredList.add(entity);
            }
        }
        return filteredList;
    }

    @Override
    public Iterable<T> getAllDentists() {
        List<T> filteredList = new ArrayList<>();
        for (T entity : super.getAllDentists()) {
            if (filter.accept(entity)) {
                filteredList.add(entity);
            }
        }
        return filteredList;
    }
}
