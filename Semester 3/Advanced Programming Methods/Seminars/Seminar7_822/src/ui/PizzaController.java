package ui;

import Domain.*;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import observer.Order;

public class PizzaController {
    Order order;
    @FXML
    private Button addButton;

    @FXML
    public void addButtonHandler(ActionEvent e)
    {
        Pizza margheritaPizza= new MargeritaPizza();
        Pizza capriciosaPizza= new CapriciossaPizza();

        Pizza margheritaThickCrust
                = new ThickCrust(margheritaPizza);
        Pizza margheritaThickCrustPeperonniTopping
                = new PeperonniTopping(margheritaThickCrust);
        order.addPizza(margheritaThickCrustPeperonniTopping);

    }
    public PizzaController(Order order){
        this.order=order;
    }
}
