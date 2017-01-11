#include "imagelabelercore.h"
#include <QApplication>
#include "imagelabelergui.h"

#define DEBUG

#ifdef DEBUG
#include <QDebug>
#endif // QDebug

ImageLabeler::ImageLabeler(int argc, char **argv) :
	app(new QApplication(argc, argv)),
	gui(new ImageLabelerGUI(this)),
	dirIter(nullptr),
	rootDirectory(""),
	imageFormat("")
{
#ifdef DEBUG
	qDebug() << "Constructor finished";
#endif
}

ImageLabeler::~ImageLabeler()
{
	delete gui;
	delete dirIter;
	delete app;
}

ImageLabeler::run()
{
	gui->show();
	return app->exec();
}

bool ImageLabeler::loadNext()
{
	QString filepath = "";

	// Error case check
	if (dirIter == nullptr) {
		return false;
	}

	// Iterate to next image, verify valid
	else if (dirIter->hasNext()) {
		filepath = dirIter->next();

		// Update GUI
		gui->setFilepath(filepath);
		gui->setImage(filepath);
//		gui->resetButtons(); // TODO
		return true;
	}

	else {
		// Update GUI
		gui->setFilepath("No images found");
		gui->setImage(""); // Directory of some placeholder image
//		gui->disableButtons(); // TODO
		return false;
	}
}


void ImageLabeler::setRootDirectory(const QString& dir)
{
	rootDirectory = QDir(dir);
	loadIter();

#ifdef DEBUG
	// Reinitialize new iter, as iter copy is disabled
	QDirIterator debugIter(rootDirectory.absolutePath(), QStringList() << "*." + imageFormat, QDir::Files, QDirIterator::NoIteratorFlags);
	qDebug() << "Root directory set to" << dir << "Detected files:";
	while (debugIter.hasNext()) {
		qDebug() << debugIter.next();
	}
#endif // DEBUG
}

void ImageLabeler::setImageFormat(const QString &format)
{
	imageFormat = format;
}

void ImageLabeler::loadIter()
{
	if (dirIter != nullptr)
		delete dirIter;
	dirIter = new WrappingQDirIterator(rootDirectory.absolutePath(), QStringList() << "*." + imageFormat, QDir::Files, QDirIterator::NoIteratorFlags);
}
