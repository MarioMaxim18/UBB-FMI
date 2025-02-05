package filter;

import domain.Entity;

public interface AbstractFilter {
    boolean accept(Entity e);

}
