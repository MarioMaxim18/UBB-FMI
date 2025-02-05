package Repository;

import domain.Entity;
import filter.AbstractFilter;

public class FilteredRepository extends Repository {
    private AbstractFilter filter;
    public FilteredRepository(AbstractFilter filter) {
        this.filter = filter;
    }
//    @Override
//    public void add(Entity entity) {
//        if (filter.accept(entity)) {
//            entities.add(entity);
//        }

//    }

}
