package ui;

import Domain.Pizza;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import observer.Observer;
import observer.Order;

import java.util.List;

public class OrderController implements Observer {
    Order order;
    @FXML
    private ListView<String> orderListView;

    @FXML
    private Label priceLabel;

    @Override
    public void update() {
        List<Pizza> list = order.getAll();
        orderListView.getItems().clear();
        for (Pizza pizza : list) {
            orderListView.getItems().add(pizza.toString());
        }
        priceLabel.setText(order.computeTotal().toString());
    }

    public OrderController(Order order) {
        this.order = order;
    }
}
