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

class ImageData;

class ImageLabelerGUI : public QMainWindow
{
	Q_OBJECT

public:
	explicit ImageLabelerGUI(ImageLabeler *core, QMainWindow *parent = 0);
	~ImageLabelerGUI();

	void setRootDirectory(const QString &str);
    void setImageFormat(const QString &str);
	void setFilepath(const QString &str);
	void setImage(const QString &str);
	void setComment(const QString &str);
    void resetButtons();
    void disableButtons();

private slots:

    void on_skipButton_clicked();
	void on_saveAndNextButton_clicked();
	void on_cancelButton_clicked();
    void on_directoryButton_clicked();

    ImageData check_buttons();  //return image data for current button setup
    bool validate_buttons(ImageData currImage); //make sure all fields are selected
    void on_notTarget_clicked();

    void on_formatButton_clicked();

private:
	Ui::ImageLabelerGUI *ui;
	ImageLabeler *model;
	QPixmap image;
};

#endif // IMAGELABELERGUI_H
