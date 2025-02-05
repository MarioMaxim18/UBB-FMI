package domain;

import java.io.Serializable;

public class Entity<ID> implements Serializable {
    protected ID id;

    public Entity(ID id){
        this.id = id;
    }

    public void setID(ID id){
        this.id = id;
    }

    public ID getID(){
        return this.id;
    }
}
