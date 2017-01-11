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
	void on_skipButton_clicked();

	void on_saveAndNextButton_clicked();

	void on_cancelButton_clicked();

private:
	Ui::ImageLabelerGUI *ui;
	ImageLabeler *model;
	QPixmap image;
};

#endif // IMAGELABELERGUI_H