#ifndef IMAGELABELERGUI_H
#define IMAGELABELERGUI_H

#include <QMainWindow>
#include <QDir>
#include <QDirIterator>
#include "imagelabelercore.h"

namespace Ui {
class ImageLabelerGUI;
}

// Forward declaration
class ImageLabeler;
<<<<<<< HEAD
class ImageData;
=======
>>>>>>> 5784a4fdf9e154f445b71734d42f5ca56fae81da

class ImageLabelerGUI : public QMainWindow
{
	Q_OBJECT

public:
	explicit ImageLabelerGUI(ImageLabeler *core, QMainWindow *parent = 0);
	~ImageLabelerGUI();

	void setFilepath(const QString &str);
	void setImage(const QString &str);
	void setComment(const QString &str);

private slots:
<<<<<<< HEAD
    void on_skipButton_clicked();
	void on_saveAndNextButton_clicked();
	void on_cancelButton_clicked();
    void on_directoryButton_clicked();

    ImageData check_buttons();  //return image data for current button setup
    bool validate_buttons(ImageData currImage); //make sure all fields are selected
=======
	void on_skipButton_clicked();

	void on_saveAndNextButton_clicked();

	void on_cancelButton_clicked();
>>>>>>> 5784a4fdf9e154f445b71734d42f5ca56fae81da

private:
	Ui::ImageLabelerGUI *ui;
	ImageLabeler *model;
	QPixmap image;
};

#endif // IMAGELABELERGUI_H
