#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
class QLineEdit;
class QTableWidget;
class QKeyEvent;

#include "Controller.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(Controller& ctrl, QWidget *parent = nullptr);

    void keyPressEvent(QKeyEvent *event) override;
signals:

public slots:
    void findSong();

private:
    QPushButton* m_addButton;
    QPushButton* m_findButton;
    QPushButton* m_removeButton;

    QTableWidget* m_songsTable;

    QLineEdit* m_searchEdit;

    QLineEdit* m_removeTitleEdit;
    QLineEdit* m_removeArtistEdit;

    Controller &m_controller;
    void buildUI();
};

#endif // MAINWINDOW_H
