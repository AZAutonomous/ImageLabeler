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
<<<<<<< HEAD
    app.setImageFormat("jpg");
=======
	app.setImageFormat("png");
>>>>>>> 5784a4fdf9e154f445b71734d42f5ca56fae81da
	app.setRootDirectory("Z:/");
	app.loadNext(); // Load first image

	return app.run();
}
