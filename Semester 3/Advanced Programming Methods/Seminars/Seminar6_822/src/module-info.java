module Seminar6 {
    requires java.sql;
    requires javafx.controls;
    requires javafx.fxml;
    requires org.xerial.sqlitejdbc;

    opens gui to javafx.fxml;
    exports gui;
}