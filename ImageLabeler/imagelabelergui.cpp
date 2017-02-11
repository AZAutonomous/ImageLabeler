#include "imagelabelergui.h"
#include "flowlayout.h"
#include "ui_imagelabelergui.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>

<<<<<<< HEAD
class ImageData;

=======
>>>>>>> 5784a4fdf9e154f445b71734d42f5ca56fae81da
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
<<<<<<< HEAD
    image = QPixmap(str);
=======
	image = QPixmap(str);
>>>>>>> 5784a4fdf9e154f445b71734d42f5ca56fae81da
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
<<<<<<< HEAD
    //gather data for current image
    ImageData currImage = check_buttons();

    //validate button configuration
    if(validate_buttons(currImage) == false){
        setComment("Not all fields pressed");
    }
    else{  
        model->moveToProcessedDir();
        model->saveData(currImage); //output currImage data to file
        model->loadNext();

    }
    //TODO: move that image from unprocessed to processed directory. Should those directories be made programatically?

=======
	// TODO: Get data, pass to saveData
	// model->saveData(); //TODO
	model->loadNext();
>>>>>>> 5784a4fdf9e154f445b71734d42f5ca56fae81da
}

void ImageLabelerGUI::on_cancelButton_clicked()
{
	close();
}
<<<<<<< HEAD

void ImageLabelerGUI::on_directoryButton_clicked()
{
    QString dirString = ui->lineEdit->text();
    model->setRootDirectory(dirString);
    model->loadNext();

}
bool ImageLabelerGUI::validate_buttons(ImageData currImage){
    if(currImage.shape.length() == 0 ||
       currImage.shapeColor.length() == 0 ||
       currImage.letter.length() == 0 ||
       currImage.letterColor.length() == 0 ||
       currImage.orientation.length() == 0 ){
        return false;
    }
    else{
        return true;
    }
}
//check shapes toggled
ImageData ImageLabelerGUI::check_buttons()
{
    ImageData currImage;

    //check shape button
    if(ui->shapeButtons->checkedButton() == ui->circle){
        currImage.shape = "circle";
    }
    if(ui->shapeButtons->checkedButton() == ui->semicircle){
        currImage.shape = "semicircle";
    }
    if(ui->shapeButtons->checkedButton() == ui->quartercircle){
        currImage.shape = "quartercircle";
    }
    if(ui->shapeButtons->checkedButton() == ui->triangle){
        currImage.shape = "triangle";
    }
    if(ui->shapeButtons->checkedButton() == ui->square){
        currImage.shape = "square";
    }
    if(ui->shapeButtons->checkedButton() == ui->rectangle){
        currImage.shape = "rectangle";
    }
    if(ui->shapeButtons->checkedButton() == ui->trapezoid){
        currImage.shape = "trapezoid";
    }
    if(ui->shapeButtons->checkedButton() == ui->pentagon){
        currImage.shape = "pentagon";
    }
    if(ui->shapeButtons->checkedButton() == ui->hexagon){
        currImage.shape = "hexagon";
    }
    if(ui->shapeButtons->checkedButton() == ui->heptagon){
        currImage.shape = "heptagon";
    }
    if(ui->shapeButtons->checkedButton() == ui->octagon){
        currImage.shape = "octagon";
    }
    if(ui->shapeButtons->checkedButton() == ui->star){
        currImage.shape = "star";
    }
    if(ui->shapeButtons->checkedButton() == ui->cross){
        currImage.shape = "cross";
    }

    //check shape color
    if(ui->colorButtons->checkedButton() == ui->white){
        currImage.shapeColor = "white";
    }
    if(ui->colorButtons->checkedButton() == ui->black){
        currImage.shapeColor = "black";
    }
    if(ui->colorButtons->checkedButton() == ui->gray){
        currImage.shapeColor = "gray";
    }
    if(ui->colorButtons->checkedButton() == ui->red){
        currImage.shapeColor = "red";
    }
    if(ui->colorButtons->checkedButton() == ui->blue){
        currImage.shapeColor = "blue";
    }
    if(ui->colorButtons->checkedButton() == ui->green){
        currImage.shapeColor = "green";
    }
    if(ui->colorButtons->checkedButton() == ui->yellow){
        currImage.shapeColor = "yellow";
    }
    if(ui->colorButtons->checkedButton() == ui->purple){
        currImage.shapeColor = "purple";
    }
    if(ui->colorButtons->checkedButton() == ui->brown){
        currImage.shapeColor = "brown";
    }
    if(ui->colorButtons->checkedButton() == ui->orange){
        currImage.shapeColor = "orange";
    }

    //Check Letter/Number
    if(ui->letterButtons->checkedButton() == ui->a){
        currImage.letter = "a";
    }
    if(ui->letterButtons->checkedButton() == ui->b){
        currImage.letter = "b";
    }
    if(ui->letterButtons->checkedButton() == ui->c){
        currImage.letter = "c";
    }
    if(ui->letterButtons->checkedButton() == ui->d){
        currImage.letter = "d";
    }
    if(ui->letterButtons->checkedButton() == ui->e){
        currImage.letter = "e";
    }
    if(ui->letterButtons->checkedButton() == ui->f){
        currImage.letter = "f";
    }
    if(ui->letterButtons->checkedButton() == ui->g){
        currImage.letter = "g";
    }
    if(ui->letterButtons->checkedButton() == ui->h){
        currImage.letter = "h";
    }
    if(ui->letterButtons->checkedButton() == ui->i){
        currImage.letter = "i";
    }
    if(ui->letterButtons->checkedButton() == ui->j){
        currImage.letter = "j";
    }
    if(ui->letterButtons->checkedButton() == ui->k){
        currImage.letter = "k";
    }
    if(ui->letterButtons->checkedButton() == ui->l){
        currImage.letter = "l";
    }
    if(ui->letterButtons->checkedButton() == ui->m){
        currImage.letter = "m";
    }
    if(ui->letterButtons->checkedButton() == ui->n){
        currImage.letter = "n";
    }
    if(ui->letterButtons->checkedButton() == ui->o){
        currImage.letter = "o";
    }
    if(ui->letterButtons->checkedButton() == ui->p){
        currImage.letter = "p";
    }
    if(ui->letterButtons->checkedButton() == ui->q){
        currImage.letter = "q";
    }
    if(ui->letterButtons->checkedButton() == ui->r){
        currImage.letter = "r";
    }
    if(ui->letterButtons->checkedButton() == ui->s){
        currImage.letter = "s";
    }
    if(ui->letterButtons->checkedButton() == ui->t){
        currImage.letter = "t";
    }
    if(ui->letterButtons->checkedButton() == ui->u){
        currImage.letter = "u";
    }
    if(ui->letterButtons->checkedButton() == ui->v){
        currImage.letter = "v";
    }
    if(ui->letterButtons->checkedButton() == ui->w){
        currImage.letter = "w";
    }
    if(ui->letterButtons->checkedButton() == ui->x){
        currImage.letter = "x";
    }
    if(ui->letterButtons->checkedButton() == ui->y){
        currImage.letter = "y";
    }
    if(ui->letterButtons->checkedButton() == ui->z){
        currImage.letter = "z";
    }
    if(ui->letterButtons->checkedButton() == ui->zero){
        currImage.letter = "zero";
    }
    if(ui->letterButtons->checkedButton() == ui->one){
        currImage.letter = "one";
    }
    if(ui->letterButtons->checkedButton() == ui->two){
        currImage.letter = "two";
    }
    if(ui->letterButtons->checkedButton() == ui->three){
        currImage.letter = "three";
    }
    if(ui->letterButtons->checkedButton() == ui->four){
        currImage.letter = "four";
    }
    if(ui->letterButtons->checkedButton() == ui->five){
        currImage.letter = "five";
    }
    if(ui->letterButtons->checkedButton() == ui->six){
        currImage.letter = "six";
    }
    if(ui->letterButtons->checkedButton() == ui->seven){
        currImage.letter = "seven";
    }
    if(ui->letterButtons->checkedButton() == ui->eight){
        currImage.letter = "eight";
    }
    if(ui->letterButtons->checkedButton() == ui->nine){
        currImage.letter = "nine";
    }

    //check letter color
    if(ui->letterColorButtons->checkedButton() == ui->letterWhite){
        currImage.letterColor = "white";
    }
    if(ui->letterColorButtons->checkedButton() == ui->letterBlack){
        currImage.letterColor = "black";
    }
    if(ui->letterColorButtons->checkedButton() == ui->letterGray){
        currImage.letterColor = "gray";
    }
    if(ui->letterColorButtons->checkedButton() == ui->letterRed){
        currImage.letterColor = "red";
    }
    if(ui->letterColorButtons->checkedButton() == ui->letterBlue){
        currImage.letterColor = "blue";
    }
    if(ui->letterColorButtons->checkedButton() == ui->letterGreen){
        currImage.letterColor = "green";
    }
    if(ui->letterColorButtons->checkedButton() == ui->letterYellow){
        currImage.letterColor = "yellow";
    }
    if(ui->letterColorButtons->checkedButton() == ui->letterPurple){
        currImage.letterColor = "purple";
    }
    if(ui->letterColorButtons->checkedButton() == ui->letterBrown){
        currImage.letterColor = "brown";
    }
    if(ui->letterColorButtons->checkedButton() == ui->letterOrange){
        currImage.letterColor = "orange";
    }

    //check orientation
    if(ui->dirButtons->checkedButton() == ui->NW){
        currImage.orientation = "nw";
    }
    if(ui->dirButtons->checkedButton() == ui->N){
        currImage.orientation = "n";
    }
    if(ui->dirButtons->checkedButton() == ui->NE){
        currImage.orientation = "ne";
    }
    if(ui->dirButtons->checkedButton() == ui->W){
        currImage.orientation = "w";
    }
    if(ui->dirButtons->checkedButton() == ui->E){
        currImage.orientation = "e";
    }
    if(ui->dirButtons->checkedButton() == ui->SW){
        currImage.orientation = "sw";
    }
    if(ui->dirButtons->checkedButton() == ui->S){
        currImage.orientation = "s";
    }
    if(ui->dirButtons->checkedButton() == ui->SE){
        currImage.orientation = "se";
    }

    return currImage;
}

=======
>>>>>>> 5784a4fdf9e154f445b71734d42f5ca56fae81da
