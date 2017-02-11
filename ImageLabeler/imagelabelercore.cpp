#include "imagelabelercore.h"
#include <QApplication>
#include "imagelabelergui.h"
<<<<<<< HEAD
#include <QFile>
#include <QTextStream>
=======
>>>>>>> 5784a4fdf9e154f445b71734d42f5ca56fae81da

#define DEBUG

#ifdef DEBUG
#include <QDebug>
#endif // QDebug
<<<<<<< HEAD
class ImageData;
=======
>>>>>>> 5784a4fdf9e154f445b71734d42f5ca56fae81da

ImageLabeler::ImageLabeler(int argc, char **argv) :
	app(new QApplication(argc, argv)),
	gui(new ImageLabelerGUI(this)),
	dirIter(nullptr),
	rootDirectory(""),
<<<<<<< HEAD
    imageFormat(""),
    imageNumber(1),
    rootDirectoryName("")

=======
	imageFormat("")
>>>>>>> 5784a4fdf9e154f445b71734d42f5ca56fae81da
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

<<<<<<< HEAD
int ImageLabeler::run()
=======
ImageLabeler::run()
>>>>>>> 5784a4fdf9e154f445b71734d42f5ca56fae81da
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
<<<<<<< HEAD
    rootDirectoryName = dir;
=======
>>>>>>> 5784a4fdf9e154f445b71734d42f5ca56fae81da
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
<<<<<<< HEAD
void ImageLabeler::moveToProcessedDir(){ //move process images to seperate directory and rename to correspond with its JSON
    QDir d = QDir(dirIter->filePath());
    QString currNum = QString::fromStdString(std::to_string(imageNumber));
    d.rename(dirIter->filePath(), rootDirectoryName + "/Processed/" + dirIter->fileName());

}

void ImageLabeler::saveData(ImageData currImage) //outputs data to file in JSON format
{
    QString line;
    QString currNum = QString::fromStdString(std::to_string(imageNumber)); //"unique"
    ++imageNumber;
    QFile file ( rootDirectoryName + "/Processed/" + currNum + ".txt" );  //FIX: hardcoded directory for JSON.

    line.append("{\n\t\"image\": ");
    line.append(rootDirectoryName + "/Processed/" + dirIter->fileName());
    line.append("\n\t\"shape\": \"");
    line.append( currImage.shape );
    line.append( "\",\n");
    line.append("\t\"shapeColor\": \"");
    line.append( currImage.shapeColor );
    line.append( "\",\n");
    line.append("\t\"letter\": \"");
    line.append( currImage.letter );
    line.append( "\",\n");
    line.append("\t\"letterColor\": \"");
    line.append( currImage.letterColor );
    line.append( "\",\n");
    line.append("\t\"orientation\": \"");
    line.append( currImage.orientation );
    line.append( "\",\n}");

    if ( file.open( QIODevice::ReadWrite) )
    {
    QTextStream stream( &file );
    stream << line << endl;
    file.close();
    }
}
=======
>>>>>>> 5784a4fdf9e154f445b71734d42f5ca56fae81da
