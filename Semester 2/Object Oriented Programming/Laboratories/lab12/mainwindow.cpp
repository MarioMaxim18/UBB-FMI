#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi();
}

void MainWindow::setupUi() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    QStringList headers = {"Title", "Author", "Year", "Price", "Quantity"};

    tableWidget = new QTableWidget(0, 5, this);
    tableWidget->setHorizontalHeaderLabels(headers);
    mainLayout->addWidget(tableWidget);

    QFormLayout *formLayout = new QFormLayout();
    titleEdit = new QLineEdit(this);
    authorEdit = new QLineEdit(this);
    yearEdit = new QLineEdit(this);
    priceEdit = new QLineEdit(this);
    quantityEdit = new QLineEdit(this);
    formLayout->addRow("Title:", titleEdit);
    formLayout->addRow("Author:", authorEdit);
    formLayout->addRow("Year:", yearEdit);
    formLayout->addRow("Price:", priceEdit);
    formLayout->addRow("Quantity:", quantityEdit);
    mainLayout->addLayout(formLayout);

    addButton = new QPushButton("Add", this);
    QObject::connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddButtonClicked);
    mainLayout->addWidget(addButton);
}

void MainWindow::onAddButtonClicked() {
//    if (!validateInput()) {
//        QMessageBox::warning(this, "Input validation", "Please enter a valid year");
//        return;
//        }

    Book book(titleEdit->text(), authorEdit->text(), yearEdit->text().toInt(), priceEdit->text().toDouble(), quantityEdit->text().toInt());
//    books.append(book);

    int currentRow = tableWidget->rowCount();
    tableWidget->insertRow(currentRow);

    tableWidget->setItem(currentRow, 0, new QTableWidgetItem(book.getTitle()));
    tableWidget->setItem(currentRow, 1, new QTableWidgetItem(book.getAuthor()));
    tableWidget->setItem(currentRow, 2, new QTableWidgetItem(QString::number(book.getYear())));
    tableWidget->setItem(currentRow, 3, new QTableWidgetItem(QString::number(book.getPrice())));
    tableWidget->setItem(currentRow, 4, new QTableWidgetItem(QString::number(book.getQuantity())));

    titleEdit->clear();
    authorEdit->clear();
    yearEdit->clear();
    priceEdit->clear();
    quantityEdit->clear();
}

//bool MainWindow::validateInput() {
//    bool ok;
//    int year = yearEdit->text().toInt(&ok);
//    return ok && year > 0;
//}

MainWindow::~MainWindow() {
}
