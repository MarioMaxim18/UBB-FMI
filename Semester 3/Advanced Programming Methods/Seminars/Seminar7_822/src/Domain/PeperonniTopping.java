package Domain;

public class PeperonniTopping extends PizzaDecorator{
    public PeperonniTopping(Pizza pizzaObject) {
        super(pizzaObject);
    }

    @Override
    public double getPrice(){
        return super.getPrice()+7;
    }

    @Override
    public String toString() {
        return super.toString()+" Peperonni Topping";
    }
}
