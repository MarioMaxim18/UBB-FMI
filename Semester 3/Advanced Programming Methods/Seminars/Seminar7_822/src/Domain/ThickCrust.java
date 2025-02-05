package Domain;

public class ThickCrust extends PizzaDecorator{
    //only one object of this type

    public ThickCrust(Pizza pizzaObject) {
        super(pizzaObject);
    }

    @Override
    public double getPrice(){
        return super.getPrice()+5;
    }

    @Override
    public String toString() {
        return super.toString()+" ThickCrust";
    }
}
