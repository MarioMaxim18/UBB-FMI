package Domain;

public class CapriciossaPizza implements Pizza{
    @Override
    public double getPrice(){
        return 40;
    }

    @Override
    public String toString() {
        return "CapriciossaPizza{}";
    }
}
