#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QKeyEvent>
#include <QShortcut>
#include "service.h"
class MainPage : public QWidget {
private:
	Service& srv;
	QTableWidget* main_table;
	QLabel* title_label;
	QLabel* artist_label;
	QLabel* duration_Label;
	QLabel* youtube_label;
	
	QLineEdit* title_line_edit;
	QLineEdit* artist_line_edit;
	QLineEdit* duration_line_edit;
	QLineEdit* youtube_line_edit;
	
	//Use a line edit to filter while we are writing in it
	QLineEdit* filter_by_title_edit;

	
	QPushButton* add_button;

	//deletion will be made upon selection from table
	QPushButton* delete_button;
	QPushButton* undo_button;

	QCheckBox* check_box_add_with_spinbox;

	QGroupBox* add_spin_box_group;
	QVBoxLayout* spin_box_group_layout;
	QPushButton* add_with_spinbox_button;
	QSpinBox* duration_minutes_spin_box;
	QSpinBox* duration_seconds_spin_box;
	QPushButton* add_with_other_button;

	QHBoxLayout* main_layout;
	//Vertical layout to arrange the components on the right side
	//of the window (edits, buttons, etc)
	QVBoxLayout* right_side_layout;
	QFormLayout* addition_form_layout;


	void initializeGUI();
	void connectSignalsSlots();
	void reloadData(const vector<MediaItem>& items);
	void clearLineEdits();
	void deleteSongGUI();
	void addSongGUI();
	void undoGUI();

	//handle key pressing
	void keyPressEvent(QKeyEvent* event) override
	{
		qDebug() << event->key();
	}
public:
	MainPage(Service& _srv) :srv{ _srv } {
		initializeGUI();
		reloadData(srv.getAllSongs());
		connectSignalsSlots();
	};
};

