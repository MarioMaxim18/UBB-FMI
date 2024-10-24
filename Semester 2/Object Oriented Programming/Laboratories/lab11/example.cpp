#include <QApplication>
#include <QPushButton>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QPushButton button("Click me!");

    QObject::connect(&button, &QPushButton::clicked, []() {
        qDebug() << "Button clicked!";
    });

    button.show();
    return app.exec();
}