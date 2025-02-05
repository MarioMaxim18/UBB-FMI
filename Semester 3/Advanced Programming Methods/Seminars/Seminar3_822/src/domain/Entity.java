package domain;

public class Entity<ID> {
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
