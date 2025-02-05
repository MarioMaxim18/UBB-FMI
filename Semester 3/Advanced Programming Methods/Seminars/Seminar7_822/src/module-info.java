module com.example.seminar7_822 {
    requires javafx.controls;
    requires javafx.fxml;

    opens ui to javafx.fxml;
    exports ui;
}