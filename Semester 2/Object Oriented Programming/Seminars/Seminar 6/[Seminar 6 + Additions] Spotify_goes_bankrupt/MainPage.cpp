#include "MainPage.h"
#include <qDebug>

void MainPage::initializeGUI() {
	//layouts
	this->setWindowTitle("Spotify goes bankrupt");
	
	//not necessary to specify parent (i.e. this), but helps 
	//with memory management
	this->main_layout = new QHBoxLayout(this);
	this->addition_form_layout = new QFormLayout;
	this->right_side_layout = new QVBoxLayout;
	this->setLayout(this->main_layout);

	

	//The table we are displaying the media items in
	this->main_table = new QTableWidget{int(srv.getAllSongs().size()), 4};

	//set table header
	this->main_table->setHorizontalHeaderLabels({"Artist", "Title", "Duration", "Youtube link"});

	//added: set selection mode -> currently, I want to be able to select only
	//one row

	//from docs:
	//enum SelectionBehavior { SelectItems, SelectRows, SelectColumns }
	//enum SelectionMode { SingleSelection, ContiguousSelection, ExtendedSelection, MultiSelection, NoSelection }
	main_table->setSelectionBehavior(QAbstractItemView::SelectRows);
	main_table->setSelectionMode(QAbstractItemView::SingleSelection);

	//the components we use
	this->duration_Label = new QLabel{ "Duration"};
	this->artist_label = new QLabel{ "Artists"};
	this->title_label = new QLabel{ "Title"};
	this->youtube_label = new QLabel{ "Youtube link:"};
	this->title_line_edit = new QLineEdit;
	this->artist_line_edit = new QLineEdit;
	this->duration_line_edit = new QLineEdit;
	this->youtube_line_edit = new QLineEdit;
	this->add_button = new QPushButton{ "Add song" };
	this->delete_button = new QPushButton{ "Delete selected song"};


	this->addition_form_layout->addRow(this->artist_label, this->artist_line_edit);
	this->addition_form_layout->addRow(this->title_label, this->title_line_edit);
	this->addition_form_layout->addRow(this->duration_Label, this->duration_line_edit);
	this->addition_form_layout->addRow(this->youtube_label, this->youtube_line_edit);
	
	//See re: ownership transfer when addWidget is used
	//https://doc.qt.io/qt-5/qlayout.html#addItem
	this->addition_form_layout->addWidget(this->add_button);
	
	//added
	this->filter_by_title_edit = new QLineEdit;
	this->filter_by_title_edit->setPlaceholderText("Input here to filter by title");

	//added
	this->add_spin_box_group = new QGroupBox{ "Add with other components"};
	this->spin_box_group_layout = new QVBoxLayout;
	this->check_box_add_with_spinbox = new QCheckBox("I want to add with SpinBoxes");

	this->add_spin_box_group->setLayout(this->spin_box_group_layout);
	this->duration_minutes_spin_box = new QSpinBox;

	//can set min/max for value inside SpinBox
	//could be useful here, especially for seconds: 
	//make sure we don't have more than 59 seconds
	this->duration_minutes_spin_box->setMinimum(0);
	this->duration_minutes_spin_box->setMaximum(15);
	this->duration_seconds_spin_box = new QSpinBox;
	this->duration_seconds_spin_box->setMinimum(0);
	this->duration_seconds_spin_box->setMaximum(59);

	this->spin_box_group_layout->addWidget(this->check_box_add_with_spinbox);
	this->spin_box_group_layout->addWidget(this->duration_minutes_spin_box);
	this->spin_box_group_layout->addWidget(this->duration_seconds_spin_box);

	this->add_with_other_button = new QPushButton("Add song with spinbox");
	this->spin_box_group_layout->addWidget(this->add_with_other_button);

	this->right_side_layout->addLayout(this->addition_form_layout);
	this->right_side_layout->addWidget(this->add_spin_box_group);
	this->right_side_layout->addWidget(filter_by_title_edit);
	
	this->right_side_layout->addWidget(delete_button);
	undo_button = new QPushButton{ "Undo"};
	this->right_side_layout->addWidget(undo_button);

	this->main_layout->addWidget(this->main_table);
	this->main_layout->addLayout(this->right_side_layout);

}

void MainPage::connectSignalsSlots() {
	//written at seminar
	QObject::connect(this->add_button, &QPushButton::clicked, [&]() {
		QString title_text = title_line_edit->text();
		QString artist_text = artist_line_edit->text();
		QString youtube_link_text = youtube_line_edit->text();

		QString duration_text = duration_line_edit->text();
		//qDebug() << title_text << " " << artist_text << " " << duration_text.split(':').at(0).toInt();
		try {
			srv.addMediaItem(title_text.toStdString(), artist_text.toStdString(), youtube_link_text.toStdString(), duration_text.split(':').at(0).toInt(), duration_text.split(':').at(1).toInt());
			reloadData(srv.getAllSongs());
			clearLineEdits();
		}
		catch (RepoException& re) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMsg()));
		}
		});

	//added: I want to filter the table as I write in this QLineEdit
	//take QLineEdit text as parameter
	//see docs for difference between textEdited and textChanged
	QObject::connect(filter_by_title_edit, &QLineEdit::textEdited, [&](QString text) {
		qDebug() << text;
		string titleFilter = text.toStdString();
		vector<MediaItem> filteredItems = srv.filterByTitle(titleFilter);
		reloadData(filteredItems);
		});

	//added: exemplify item selection
	QObject::connect(main_table, &QTableWidget::itemSelectionChanged, [&]() {
		qDebug() << "Item selection changed";
		QList<QTableWidgetItem*> selectedItems = main_table->selectedItems();
		qDebug() << "How many selected items: " << selectedItems.size();
		});

	//added: addition using QSpinBox component
	QObject::connect(add_with_other_button, &QPushButton::clicked, this, &MainPage::addSongGUI);
		

	//added: exemplify properties of components
	//if the "I want to add with spinbox" checkbox is checked, disable the duration 
	//line edit, as we take the duration information from the spinboxes
	//else, it is enabled
	QObject::connect(check_box_add_with_spinbox, &QCheckBox::toggled, [&]() {
		duration_line_edit->setDisabled(check_box_add_with_spinbox->isChecked());
		});

	//added: Deletion based on item selected in table at click of delete button
	QObject::connect(delete_button, &QPushButton::clicked,this, &MainPage::deleteSongGUI);

	//added: Connect undo button with functionality
	QObject::connect(undo_button, &QPushButton::clicked, this, &MainPage::undoGUI);

	//added: connect shortcut: CTRL+Z to undo action
	QShortcut* shortcut = new QShortcut(QKeySequence("Ctrl+Z"), this);
	QObject::connect(shortcut, &QShortcut::activated, this, &MainPage::undoGUI);
}

void MainPage::reloadData(const vector<MediaItem>& items) {
	this->main_table->clear();
	//changed: vector given as parameter to be able to use this for filter functionality, 
	// as well
	
	//std::vector<MediaItem> items = srv.getAllSongs();
	
	//Change made from the seminar: we added correctly, but row count 
	//was set in the constructor, so item added didn't show up on reload, 
	//we had previous number of rows+1 now
	//set current row count every time reload is called
	
	this->main_table->setRowCount(items.size());

	int index = 0;
	for (auto song : items) {
		this->main_table->setItem(index, 0, new QTableWidgetItem{ QString::fromStdString(song.getArtist()) });
		this->main_table->setItem(index, 1, new QTableWidgetItem{ QString::fromStdString(song.getTitle()) });
		this->main_table->setItem(index, 2, new QTableWidgetItem{ QString::fromStdString(song.getDuration().toString()) });
		this->main_table->setItem(index, 3, new QTableWidgetItem{ QString::fromStdString(song.getYtLink()) });

		index++;
	}
}

void MainPage::clearLineEdits()
{
	this->artist_line_edit->clear();
	this->title_line_edit->clear();
	this->youtube_line_edit->clear();
	this->duration_line_edit->clear();
}

void MainPage::deleteSongGUI()
{
	//this list contains all the QTableWidgetItems that are selected
	QList<QTableWidgetItem*> selected_items = main_table->selectedItems();
	if (selected_items.isEmpty()) {
		//if nothing selected, nothing to delete: display error message
		QMessageBox::warning(this, "Error", "Nothing selected");
		return;
	}
	
	try {
		//we have something selected (haven't exited function)
		//identify data we need (artist and title) from the selectedRow
		QTableWidgetItem* item_to_delete = selected_items.at(0);
		int row = item_to_delete->row();
		string artist_to_delete = main_table->item(row, 0)->text().toStdString();
		string title_to_delete = main_table->item(row, 1)->text().toStdString();

		this->srv.deleteSong(artist_to_delete, title_to_delete);
		reloadData(this->srv.getAllSongs());
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Error", QString::fromStdString(re.getErrorMsg()));
	}
}

void MainPage::addSongGUI()
{
	//I should have the "I want to add with spinbox" option checked
	//if I want to add in this way
	if (!check_box_add_with_spinbox->isChecked())
	{
		QMessageBox::warning(this, "Error", "You have not selected addition with spinboxes.");
		return;
	}
	//get info like usual from line edits
	QString title_text = title_line_edit->text();
	QString artist_text = artist_line_edit->text();
	QString youtube_link_text = youtube_line_edit->text();

	//spinboxes have method value()
	//which returns the value in the spinbox
	//use this info to create a new media item
	ushi minutes = duration_minutes_spin_box->value();
	ushi seconds = duration_seconds_spin_box->value();

	try {
		srv.addMediaItem(artist_text.toStdString(), title_text.toStdString(), youtube_link_text.toStdString(), minutes, seconds);
		reloadData(srv.getAllSongs());
		clearLineEdits();
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Error!", QString::fromStdString(re.getErrorMsg()));
	}

}

void MainPage::undoGUI()
{
	try {
		srv.undo();
		reloadData(srv.getAllSongs());
	}
	catch (std::runtime_error& err) {
		QMessageBox::warning(this, "Error", err.what());
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Error", QString::fromStdString(re.getErrorMsg()));

	}
}
