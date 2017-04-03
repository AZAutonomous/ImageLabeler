#include "imagelabelercore.h"
#include <QApplication>
#include "imagelabelergui.h"

#include <QFile>
#include <QTextStream>
#include <QFileInfo>

#define DEBUG

#ifdef DEBUG
#include <QDebug>
#endif // QDebug

class ImageData;

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


int ImageLabeler::run()

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
        gui->resetButtons();
		return true;
	}

	else {
		// Update GUI
		gui->setFilepath("No images found");
		gui->setImage(""); // Directory of some placeholder image
        gui->resetButtons();
		return false;
	}
}


void ImageLabeler::setRootDirectory(QString dir)
{
	// Validate directory
	if (!dir.isEmpty() && dir.right(1) != "/") {
		dir.append('/'); // Add trailing '/'
#ifdef DEBUG
	qDebug() << "Adjusted directory name to" << dir;
#endif
	}

	// Update GUI
	gui->setRootDirectory(dir);

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

void ImageLabeler::setImageFormat(QString format)
{
	// Validate input
	if (!format.isEmpty() && format.lastIndexOf(".") != -1) {
		format = format.section(".", -1); // Extract file extension
#ifdef DEBUG
	qDebug() << "Adjusted file extension to" << format;
#endif
	}

	imageFormat = format;
}

void ImageLabeler::loadIter()
{
	if (dirIter != nullptr)
		delete dirIter;
	dirIter = new WrappingQDirIterator(rootDirectory.absolutePath(), QStringList() << "*." + imageFormat, QDir::Files, QDirIterator::NoIteratorFlags);
}

void ImageLabeler::moveToSubdir(QString subdir){ //move process images to seperate directory and rename to correspond with its JSON
	// Validate subdir
	if (!subdir.isEmpty() && subdir.right(1) != "/") {
		subdir.append('/'); // Add trailing '/'
	}

    QDir d = QDir(dirIter->filePath());
    //QString currNum = QString::fromStdString(std::to_string(imageNumber));
	d.rename(dirIter->filePath(), rootDirectory.absolutePath() + subdir + dirIter->fileName());

#ifdef DEBUG
	qDebug() << dirIter->filePath() + " moved to " + rootDirectory.absolutePath() + subdir + dirIter->fileName();
#endif // DEBUG
}

// Creates a subdirectory, incrementing suffix to avoid filename collisions. Returns created filepath
// Example: createSubdirectory("processed_", "img_001.jpg")
QString ImageLabeler::createSubdir(const QString &subdir_root, const QString &filename) {  //creates processed directory as necessary
    int i = 0;
	QString subdir = subdir_root + QString::number(i) + "/";
	QFile *file = new QFile(rootDirectory.absolutePath() + subdir + filename);

	qDebug() << rootDirectory.absolutePath() + subdir + filename << "exists:" << file->exists();

	// Search until no duplicate file names/paths
	while (file->exists()) {
		++i;
		subdir = subdir_root + QString::number(i) + "/";
		delete file; // Delete old memory
		file = new QFile(subdir + filename);
	}

	// Make subdirectory
	this->rootDirectory.mkdir(subdir);
	qDebug() << "Created: " + subdir;

	// Clear memory
	delete file;

	// Return created subdirectory
	return subdir;
}

void ImageLabeler::saveData(ImageData currImage, QString subdir) //outputs data to file in JSON format
{
	// Validate subdir
	if (!subdir.isEmpty() && subdir.right(1) != "/") {
		subdir.append('/'); // Add trailing '/'
	}

	QString contents;
	QFile file ( rootDirectory.absolutePath() + subdir + dirIter->fileInfo().baseName() + ".json" );

	contents.append("{\n\t\"image\": ");
	contents.append("\"" + dirIter->fileName() + "\",");
	contents.append("\n\t\"shape\": \"");
	contents.append( currImage.shape );
	contents.append( "\",\n");
	contents.append("\t\"shapeColor\": \"");
	contents.append( currImage.shapeColor );
	contents.append( "\",\n");
	contents.append("\t\"letter\": \"");
	contents.append( currImage.letter );
	contents.append( "\",\n");
	contents.append("\t\"letterColor\": \"");
	contents.append( currImage.letterColor );
	contents.append( "\",\n");
	contents.append("\t\"orientation\": \"");
	contents.append( currImage.orientation );
	contents.append( "\"\n}");

	if ( file.open(QIODevice::WriteOnly) ) {
		QTextStream stream( &file );
		stream << contents;
		file.close();
    }
}

QString ImageLabeler::getCurrFilename() {
	return dirIter->fileName();
}

