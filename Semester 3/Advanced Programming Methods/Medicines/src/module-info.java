module com.example.demo {
    requires java.sql;
    requires javafx.controls;
    requires javafx.fxml;
    requires org.xerial.sqlitejdbc;
    requires jdk.jdi;
    requires java.desktop;

    opens gui to javafx.fxml;
    exports gui;
}