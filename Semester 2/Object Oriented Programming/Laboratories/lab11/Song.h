#include <QMainWindow>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QListWidget>
#include <QFormLayout>

class Song {
private:
    QString title;
    QString artist;
    int duration;
    QString mediaPath;

public:
    Song(QString title, QString artist, int duration, QString mediaPath) : title(title), artist(artist), duration(duration), mediaPath(mediaPath) {}

    QString getTitle() const {
        return title;
    }

    QString getArtist() const {
        return artist;
    }

    int getDuration() const {
        return duration;
    }

    QString getMediaPath() const {
        return mediaPath;
    }
};

class MainWindow : public QMainWindow {
Q_OBJECT

private:
    QTableWidget *tableWidget;
    QLineEdit *titleEdit;
    QLineEdit *artistEdit;
    QLineEdit *durationEdit;
    QLineEdit *pathEdit;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *updateButton;
    QPushButton *clearButton;
    QListWidget *playlistWidget;

    void setupUi();

private slots:
    void addButtonClicked();
    void deleteButtonClicked();
    void moveButtonClicked();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

