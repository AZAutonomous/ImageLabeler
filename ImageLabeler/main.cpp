#include "imagelabelergui.h"
#include "imagelabelercore.h"
//#include <QApplication>

//#include <QGraphicsPixmapItem>
//#include <QGraphicsScene>
//#include <QGraphicsView>

int main(int argc, char *argv[])
{
	ImageLabeler app(argc, argv);

	// Test case
	app.setImageFormat("PNG");

	app.setRootDirectory("Z:/");
	app.loadNext(); // Load first image

	return app.run();
}

