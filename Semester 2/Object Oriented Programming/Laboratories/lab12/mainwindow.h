#include <QApplication>
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QFormLayout>

class Book {
private:
    QString title;
    QString author;
    int year;
    int price;
    int quantity;
public:
    Book(QString title, QString author, int year, int price, int quantity) : title(title), author(author),
                                                                             year(year), price(price),
                                                                             quantity(quantity) {};

    QString getTitle() const {
        return title;
    }

    QString getAuthor() const {
        return author;
    }

    int getYear() const {
        return year;
    }

    int getPrice() const {
        return price;
    }

    int getQuantity() const {
        return quantity;
    }
};

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    QTableWidget *tableWidget;
    QLineEdit *titleEdit;
    QLineEdit *authorEdit;
    QLineEdit *yearEdit;
    QLineEdit *priceEdit;
    QLineEdit *quantityEdit;
    QPushButton *addButton;

    void setupUi();
//    bool validateInput();

private slots:
    void onAddButtonClicked();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};