package ui;

import Domain.*;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import observer.Order;

public class Main extends Application {

    @Override
    public void start(Stage stage) throws Exception {

        // instantiate decorators
       /* Pizza margheritaPizza= new MargeritaPizza();
        Pizza capriciosaPizza= new CapriciossaPizza();

        Pizza margheritaThickCrust
                = new ThickCrust(margheritaPizza);
        Pizza margheritaThickCrustPeperonniTopping
                = new PeperonniTopping(margheritaThickCrust);

        System.out.println(margheritaThickCrustPeperonniTopping.toString());
        System.out
                .println(margheritaThickCrustPeperonniTopping.getPrice());

        Pizza cPThickCr= new ThickCrust(capriciosaPizza);
        Pizza cPThickCr2Toppings= new PeperonniTopping(new PeperonniTopping(cPThickCr));

        System.out.println(cPThickCr2Toppings.toString());
        System.out
                .println(cPThickCr2Toppings.getPrice());*/


        Order order = new Order();
        //pizza window
        FXMLLoader loader = new FXMLLoader(getClass().getResource("pizza_gui.fxml"));
        PizzaController pizzaController = new PizzaController(order);
        loader.setController(pizzaController);
        Scene scene = new Scene(loader.load());
        stage.setScene(scene);
        stage.show();

        //order window
        FXMLLoader loader2 = new FXMLLoader(getClass().getResource("order_gui.fxml"));
        OrderController orderController = new OrderController(order);
        order.addObserver(orderController);
        loader2.setController(orderController);
        Stage stage2 = new Stage();
        Scene scen2=new Scene(loader2.load());
        stage2.setScene(scen2);
        stage2.show();

    }

    public static void main(String[] args) {
        launch(args);
    }
}
