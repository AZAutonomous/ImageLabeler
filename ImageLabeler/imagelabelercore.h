#ifndef IMAGELABELERCORE_H
#define IMAGELABELERCORE_H

#include <QApplication>
#include <QDir>
#include "wrappingqdiriterator.h"
#include "imagelabelergui.h"

// Forward declaration
class ImageLabelerGUI;

<<<<<<< HEAD
class ImageData{    //image data class
   public:
   QString filepath;
   QString shape;
   QString shapeColor;
   QString letter;
   QString letterColor;
   QString orientation;
};


=======
>>>>>>> 5784a4fdf9e154f445b71734d42f5ca56fae81da
class ImageLabeler
{
public:
	explicit ImageLabeler(int argc, char **argv);
	~ImageLabeler();

	int run();

<<<<<<< HEAD
    void saveData(ImageData currImage); // TODO: ImageData class, JSON perhaps?
=======
	//void saveData(const ImageData& data); // TODO: ImageData class, JSON perhaps?
>>>>>>> 5784a4fdf9e154f445b71734d42f5ca56fae81da
	bool loadNext(); // Return type?

	void setRootDirectory(const QString& dir);
	void setImageFormat(const QString& format);
<<<<<<< HEAD
    void moveToProcessedDir();

private:
	void loadIter();
=======

private:
	void loadIter();

>>>>>>> 5784a4fdf9e154f445b71734d42f5ca56fae81da
	QApplication *app;
	ImageLabelerGUI *gui;
	WrappingQDirIterator *dirIter;
	QDir rootDirectory;
	QString imageFormat;
<<<<<<< HEAD
    int imageNumber;
    QString rootDirectoryName;
=======
>>>>>>> 5784a4fdf9e154f445b71734d42f5ca56fae81da
};

#endif // IMAGELABELERCORE_H
