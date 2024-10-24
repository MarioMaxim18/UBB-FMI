package domain;

public class Entity {
    protected int id;

    public Entity(int id){
        this.id = id;
    }

    void setID(int id){
        this.id = id;
    }

    int getID(){
        return this.id;

    }
}
