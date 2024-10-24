#include "mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi();
}

void MainWindow::setupUi() {
    this->setWindowTitle("To-Do List Application");
    this->resize(400, 300);

    QWidget *mainWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(mainWidget);

    inputLine = new QLineEdit(this);
    layout->addWidget(inputLine);

    addButton = new QPushButton("Add", this);
    QObject::connect(addButton, &QPushButton::clicked, this, &MainWindow::addItem);
    layout->addWidget(addButton);

    todoList = new QListWidget(this);
    layout->addWidget(todoList);

    removeButton = new QPushButton("Remove", this);
    QObject::connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeItem);
    layout->addWidget(removeButton);

    clearAllButton = new QPushButton("Clear All", this);
    QObject::connect(clearAllButton, &QPushButton::clicked, this, &MainWindow::clearAllItems);
    layout->addWidget(clearAllButton);

    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);
}

void MainWindow::addItem() {
    QString itemText = inputLine->text();
    if (itemText.isEmpty()) {
        QMessageBox::warning(this, "Warning", "The to-do item cannot be empty.");
    } else {
        todoList->addItem(itemText);
        inputLine->clear();
    }
}

void MainWindow::removeItem() {
    QListWidgetItem *item = todoList->currentItem();
    if (!item) {
        QMessageBox::warning(this, "Warning", "Please select an item to remove.");
    } else {
        delete todoList->takeItem(todoList->row(item));
    }
}

void MainWindow::clearAllItems() {
    todoList->clear();
}

MainWindow::~MainWindow() {}