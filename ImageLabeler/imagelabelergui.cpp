#include "imagelabelergui.h"
#include "flowlayout.h"
#include "ui_imagelabelergui.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>

ImageLabelerGUI::ImageLabelerGUI(ImageLabeler *core, QMainWindow *parent) :
    QMainWindow(parent),
	ui(new Ui::ImageLabelerGUI),
	model(core)
{
    ui->setupUi(this);

	// Customize UI programmatically
	ui->centralWidget->layout()->setAlignment(ui->imageBox, Qt::AlignHCenter);
	ui->image->setScaledContents(true);
}

ImageLabelerGUI::~ImageLabelerGUI()
{
    delete ui;
}

void ImageLabelerGUI::setFilepath(const QString &str)
{
	ui->imageFilepath->setText(str);
}

void ImageLabelerGUI::setImage(const QString &str)
{
	image = QPixmap(str);
	ui->imageBox->layout()->setAlignment(ui->image, Qt::AlignCenter);
	ui->image->setPixmap(image);

	// Check image dimensions
	if (image.height() != image.width()) {
		setComment("<font color=red>Warning! Non-square source image, aspect ratio not preserved!</font>");
	}
	else {
		setComment("");
	}
}

void ImageLabelerGUI::setComment(const QString &str)
{
	ui->imageComment->setText(str);
}

void ImageLabelerGUI::on_skipButton_clicked()
{
	model->loadNext();
}

void ImageLabelerGUI::on_saveAndNextButton_clicked()
{
	// TODO: Get data, pass to saveData
	// model->saveData(); //TODO
	model->loadNext();
}

void ImageLabelerGUI::on_cancelButton_clicked()
{
	close();
}
