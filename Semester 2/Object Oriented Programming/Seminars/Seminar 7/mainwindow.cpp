#include "mainwindow.h"
#include <QLineEdit>
#include <QTableWidget>
#include <QLabel>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDebug>
#include <QKeyEvent>

MainWindow::MainWindow(Controller& ctrl, QWidget *parent)
    : QMainWindow{parent}
    , m_controller{ctrl}
{
    buildUI();
    connect(m_findButton, &QPushButton::clicked,
            this, &MainWindow::findSong);
}

void MainWindow::keyPressEvent(QKeyEvent *event){

    if(event->key() == Qt::Key_A){
         qDebug()<<"a was pressed!!!";
    }else{
         qDebug()<<"key press event "<<event->key()<<(int)'a' ;
    }
}

void MainWindow::findSong()
{

    QString songTitle = m_searchEdit->text();
    m_controller.add(songTitle.toStdString(),
                     songTitle.toStdString(),
                     songTitle.toStdString());
    qDebug()<<"find song function; song title "<<songTitle;
    // call the find method from the controller
    m_searchEdit->setText("");
}

void MainWindow::buildUI()
{

    QWidget* widget = new QWidget{this};
//    m_addButton = new QPushButton{"+", this};
//    m_removeButton = new QPushButton{"Remove", this};
    m_findButton = new QPushButton{"Find", this};

    m_songsTable = new QTableWidget{this};

    m_searchEdit = new QLineEdit{this};

    m_removeTitleEdit = new QLineEdit{this};
    m_removeArtistEdit = new QLineEdit{this};

    setWindowTitle("Song Management");

    // remove form layout
    QFormLayout* removeLayout = new QFormLayout{this};
    removeLayout->addRow(new QLabel{"Title"}, m_removeTitleEdit);
    removeLayout->addRow(new QLabel{"Artist"}, m_removeArtistEdit);


    // search layout
    QHBoxLayout* searchLayout = new QHBoxLayout{this};
    searchLayout->addWidget(m_searchEdit);
    searchLayout->addWidget(m_findButton);

    QVBoxLayout* rightSideLayout = new QVBoxLayout{this};
    rightSideLayout->addLayout(searchLayout);
    rightSideLayout->addLayout(removeLayout);

    QGridLayout* mainLayout = new QGridLayout{};
    mainLayout->addWidget(m_songsTable, 0, 0);
    mainLayout->addLayout(rightSideLayout, 0, 1);

    widget->setLayout(mainLayout);
    setCentralWidget(widget);

}
