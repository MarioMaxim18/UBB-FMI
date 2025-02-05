package observer;

import Domain.Pizza;

import java.util.ArrayList;
import java.util.List;

public class Order extends Observable{
    List<Pizza> list_of_pizza=new ArrayList<>();
    public void addPizza(Pizza pizza){
        list_of_pizza.add(pizza);
        notifyObservers();
    }
    public List<Pizza> getAll(){
        return list_of_pizza;
    }
    public Double computeTotal(){
        Double total=0.0;
        for(Pizza pizza:list_of_pizza)
            total= pizza.getPrice()+total;
        return total;
    }
}
