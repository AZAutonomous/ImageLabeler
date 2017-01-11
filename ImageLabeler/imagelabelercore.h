#ifndef IMAGELABELERCORE_H
#define IMAGELABELERCORE_H

#include <QApplication>
#include <QDir>
#include "wrappingqdiriterator.h"
#include "imagelabelergui.h"

// Forward declaration
class ImageLabelerGUI;

class ImageLabeler
{
public:
	explicit ImageLabeler(int argc, char **argv);
	~ImageLabeler();

	int run();

	//void saveData(const ImageData& data); // TODO: ImageData class, JSON perhaps?
	bool loadNext(); // Return type?

	void setRootDirectory(const QString& dir);
	void setImageFormat(const QString& format);

private:
	void loadIter();

	QApplication *app;
	ImageLabelerGUI *gui;
	WrappingQDirIterator *dirIter;
	QDir rootDirectory;
	QString imageFormat;
};

#endif // IMAGELABELERCORE_H
