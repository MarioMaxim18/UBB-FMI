package Domain;

public class PizzaDecorator implements Pizza{
    protected Pizza pizzaObject;

    public PizzaDecorator(Pizza pizzaObject) {
        this.pizzaObject = pizzaObject;
    }
    @Override
    public double getPrice(){
        return pizzaObject.getPrice();
    }

    @Override
    public String toString() {
        return pizzaObject.toString();
    }
}
