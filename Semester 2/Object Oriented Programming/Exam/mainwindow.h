#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addItem();
    void removeItem();
    void clearAllItems();

private:
    QLineEdit *inputLine;
    QPushButton *addButton;
    QListWidget *todoList;
    QPushButton *removeButton;
    QPushButton *clearAllButton;

    void setupUi();
};
