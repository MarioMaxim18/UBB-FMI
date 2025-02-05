package Domain;

public class MargeritaPizza implements Pizza{
    @Override
    public double getPrice(){
        return 30;
    }

    @Override
    public String toString() {
        return "MargeritaPizza{}";
    }
}
