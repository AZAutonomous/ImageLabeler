#ifndef IMAGELABELERCORE_H
#define IMAGELABELERCORE_H

#include <QApplication>
#include <QDir>
#include "wrappingqdiriterator.h"
#include "imagelabelergui.h"

// Forward declaration
class ImageLabelerGUI;

class ImageData{    //image data class
   public:
   QString filepath;
   QString shape;
   QString shapeColor;
   QString letter;
   QString letterColor;
   QString orientation;
};



class ImageLabeler
{
public:
	explicit ImageLabeler(int argc, char **argv);
	~ImageLabeler();

	int run();

	// Creates a subdirectory, incrementing suffix to avoid filename collisions. Returns created filepath
	QString createSubdir(const QString &subdir_root, const QString &filename);
	void moveToSubdir(QString subdir);
	void saveData(ImageData currImage, QString subdir = "");

	bool loadNext(); // Return type?

	void setRootDirectory(QString dir);
	void setImageFormat(QString format);

	QString getCurrFilename();

private:
	void loadIter();

	QApplication *app;
	ImageLabelerGUI *gui;
	WrappingQDirIterator *dirIter;
	QDir rootDirectory;
	QString imageFormat;
};

#endif // IMAGELABELERCORE_H
