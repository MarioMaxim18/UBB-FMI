#include "Song.h"

//void SongController::addSong(const Song &song) {
//    allSongs.push_back(song);
//}
//
//void SongController::deleteSong(const Song &song) {
//    allSongs.push_back(song);
//}
//
//void SongController::addSongToPlaylist(const Song &song) {
//    playlistSongs.push_back(song);
//}
//
//void SongController::deleteSongFromPlaylist(const Song &song) {
//    playlistSongs.push_back(song);
//}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    setupUi();
}

void MainWindow::setupUi() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout *hLay = new QHBoxLayout();

    QWidget *leftPanel = new QWidget();
    QVBoxLayout *vLayLeft = new QVBoxLayout();

    QLabel *labelSongs = new QLabel("All songs");
    vLayLeft->addWidget(labelSongs);

    tableWidget = new QTableWidget(0,4);
    QStringList headers = {"Title", "Artist", "Duration", "Path"};
    tableWidget->setHorizontalHeaderLabels(headers);
    vLayLeft->addWidget(tableWidget);

    QFormLayout *formLayout = new QFormLayout();
    titleEdit = new QLineEdit();
    artistEdit = new QLineEdit();
    durationEdit = new QLineEdit();
    pathEdit = new QLineEdit();
    formLayout->addRow("Title:", titleEdit);
    formLayout->addRow("Artist:", artistEdit);
    formLayout->addRow("Duration:", durationEdit);
    formLayout->addRow("Path:", pathEdit);
    vLayLeft->addLayout(formLayout);

    QHBoxLayout *hLayLeft = new QHBoxLayout();

    addButton = new QPushButton{"Add"};
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addButtonClicked);
    hLayLeft->addWidget(addButton);

    deleteButton = new QPushButton{"Delete"};
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteButtonClicked);
    hLayLeft->addWidget(deleteButton);

    updateButton = new QPushButton{"Update"};
    hLayLeft->addWidget(updateButton);

    clearButton = new QPushButton{"Clear"};
    hLayLeft->addWidget(clearButton);

    vLayLeft->addLayout(hLayLeft);

    leftPanel->setLayout(vLayLeft);

    QWidget *rightPanel = new QWidget();
    QVBoxLayout *vLayRight = new QVBoxLayout();

    QLabel *label = new QLabel{"Playlist"};
    vLayRight->addWidget(label);

    playlistWidget = new QListWidget{};
    vLayRight->addWidget(playlistWidget);

    QPushButton *playButton = new QPushButton{"Play"};
    vLayRight->addWidget(playButton);

    QPushButton *nextButton = new QPushButton{"Next"};
    vLayRight->addWidget(nextButton);

    rightPanel->setLayout(vLayRight);

    hLay->addWidget(leftPanel);

    QPushButton *moveButton = new QPushButton{">"};
    connect(moveButton, &QPushButton::clicked, this, &MainWindow::moveButtonClicked);
    hLay->addWidget(moveButton);

    hLay->addWidget(rightPanel);

    centralWidget->setLayout(hLay);
    centralWidget->setWindowTitle("Playlist Qt");
}

void MainWindow::addButtonClicked() {
    Song song(titleEdit->text(), artistEdit->text(), durationEdit->text().toInt(), pathEdit->text());

    int currentRow = tableWidget->rowCount();
    tableWidget->insertRow(currentRow);
    
    tableWidget->setItem(currentRow, 0, new QTableWidgetItem(song.getTitle()));
    tableWidget->setItem(currentRow, 1, new QTableWidgetItem(song.getArtist()));
    tableWidget->setItem(currentRow, 2, new QTableWidgetItem(QString::number(song.getDuration())));
    tableWidget->setItem(currentRow, 3, new QTableWidgetItem(song.getMediaPath()));

    titleEdit->clear();
    artistEdit->clear();
    durationEdit->clear();
    pathEdit->clear();
}

void MainWindow::deleteButtonClicked() {
    int currentRow = tableWidget->currentRow();
    if (currentRow != -1) {
        tableWidget->removeRow(currentRow);
    }
}

void MainWindow::moveButtonClicked() {
    int currentRow = tableWidget->currentRow();
    if (currentRow != -1) {
        QString title = tableWidget->item(currentRow, 0)->text();
        QString artist = tableWidget->item(currentRow, 1)->text();
        QString duration = tableWidget->item(currentRow, 2)->text();

        QString songDetails = title + " - " + artist + " (" + duration + ")";
        playlistWidget->addItem(songDetails);
    }
}

MainWindow::~MainWindow() {
}

