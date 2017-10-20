#include "imagelabelergui.h"
#include "flowlayout.h"
#include "ui_imagelabelergui.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>

class ImageData;

// Constructor
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

// Deconstructor
ImageLabelerGUI::~ImageLabelerGUI()
{
    delete ui;
}

// Changes Root Directory to given String
void ImageLabelerGUI::setRootDirectory(const QString &str)
{
	ui->rootDirField->setText(str);
}

// Changes Image Format to given String
void ImageLabelerGUI::setImageFormat(const QString &str)
{
    ui->imageFormatEdit->setText(str);
}

// Changes File Path to given String
void ImageLabelerGUI::setFilepath(const QString &str)
{
	ui->imageFilepath->setText(str);
}

// 'Opens' Image at given String Path
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

// Set the Comment on current Image
void ImageLabelerGUI::setComment(const QString &str)
{
	ui->imageComment->setText(str);
}

// Action for 'Skip Button' click
void ImageLabelerGUI::on_skipButton_clicked()
{
	model->loadNext();
}

// Action for 'Save and Next' Click
// TODO: Change to 'Submit Image'
void ImageLabelerGUI::on_saveAndNextButton_clicked()
{

    //gather data for current image
	ImageData currImage = check_buttons();

    //validate button configuration
	if(validate_buttons(currImage) == false) {
        setComment("Not all fields pressed");
    }
	// Check for false positives
	else if (currImage.shape == "n/a") {
		QString dir = model->createSubdir("falsepositives_", model->getCurrFilename());
		model->moveToSubdir(dir);
		model->saveData(currImage, dir); //output currImage data to file
		model->loadNext();
	}
	else {
		QString dir = model->createSubdir("processed_", model->getCurrFilename());
		model->moveToSubdir(dir);
		model->saveData(currImage, dir); //output currImage data to file
        model->loadNext();
    }

}

// Action for 'Cancel Button' Click
// NOTE: Acts as a 'quit/exit' button, relabel or remove
void ImageLabelerGUI::on_cancelButton_clicked()
{
	close();
}

// Action for 'Set Directory' Click
void ImageLabelerGUI::on_directoryButton_clicked()
{
	QString dirString = ui->rootDirField->text();
    model->setRootDirectory(dirString);
    model->loadNext();
}

// Action for 'Set Format' Click
void ImageLabelerGUI::on_formatButton_clicked()
{
    QString format = ui->imageFormatEdit->text();
    model->setImageFormat(format);
    model->loadNext();
}

// Has an option for each field been selected?
// Returns true if all fields selected, false otherwise
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

// Resets the image data fields
void ImageLabelerGUI::resetButtons(){
    if(ui->shapeButtons->checkedButton() != NULL){
    ui->shapeButtons->setExclusive(false);
    ui->shapeButtons->checkedButton()->setChecked(false);
    ui->shapeButtons->setExclusive(true);
    }
    if(ui->colorButtons->checkedButton() != NULL){
    ui->colorButtons->setExclusive(false);
    ui->colorButtons->checkedButton()->setChecked(false);
    ui->colorButtons->setExclusive(true);
    }
    if(ui->letterButtons->checkedButton() != NULL){
    ui->letterButtons->setExclusive(false);
    ui->letterButtons->checkedButton()->setChecked(false);
    ui->letterButtons->setExclusive(true);
    }
    if(ui->letterColorButtons->checkedButton() != NULL){
    ui->letterColorButtons->setExclusive(false);
    ui->letterColorButtons->checkedButton()->setChecked(false);
    ui->letterColorButtons->setExclusive(true);
    }
    if(ui->dirButtons->checkedButton() != NULL){
    ui->dirButtons->setExclusive(false);
    ui->dirButtons->checkedButton()->setChecked(false);
    ui->dirButtons->setExclusive(true);
    }
    if(ui->notTarget->isChecked()){
        ui->notTarget->setChecked(false);
    }
}

// Fills 'False Flag' Fields
void ImageLabelerGUI::disableButtons(){ //special case for not a target button
    if(ui->shapeButtons->checkedButton() != NULL){
    ui->shapeButtons->setExclusive(false);
    ui->shapeButtons->checkedButton()->setChecked(false);
    ui->shapeButtons->setExclusive(true);
    }
    if(ui->colorButtons->checkedButton() != NULL){
    ui->colorButtons->setExclusive(false);
    ui->colorButtons->checkedButton()->setChecked(false);
    ui->colorButtons->setExclusive(true);
    }
    if(ui->letterButtons->checkedButton() != NULL){
    ui->letterButtons->setExclusive(false);
    ui->letterButtons->checkedButton()->setChecked(false);
    ui->letterButtons->setExclusive(true);
    }
    if(ui->letterColorButtons->checkedButton() != NULL){
    ui->letterColorButtons->setExclusive(false);
    ui->letterColorButtons->checkedButton()->setChecked(false);
    ui->letterColorButtons->setExclusive(true);
    }
    if(ui->dirButtons->checkedButton() != NULL){
    ui->dirButtons->setExclusive(false);
    ui->dirButtons->checkedButton()->setChecked(false);
    ui->dirButtons->setExclusive(true);
    }

}

// Action for 'Not Target Button' Click
// TODO: Change to 'False Flag' Button
void ImageLabelerGUI::on_notTarget_clicked()
{
    disableButtons();
    on_saveAndNextButton_clicked();
}

//check shapes toggled
ImageData ImageLabelerGUI::check_buttons()
{
    ImageData currImage;

    if(ui->notTarget->isChecked()){
        currImage.shape = "n/a";
        currImage.shapeColor = "n/a";
        currImage.letter = "n/a";
        currImage.letterColor = "n/a";
        currImage.orientation = "n/a";
    }
    else{
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
			currImage.letter = "A";
		}
		if(ui->letterButtons->checkedButton() == ui->b){
			currImage.letter = "B";
		}
		if(ui->letterButtons->checkedButton() == ui->c){
			currImage.letter = "C";
		}
		if(ui->letterButtons->checkedButton() == ui->d){
			currImage.letter = "D";
		}
		if(ui->letterButtons->checkedButton() == ui->e){
			currImage.letter = "E";
		}
		if(ui->letterButtons->checkedButton() == ui->f){
			currImage.letter = "F";
		}
		if(ui->letterButtons->checkedButton() == ui->g){
			currImage.letter = "G";
		}
		if(ui->letterButtons->checkedButton() == ui->h){
			currImage.letter = "H";
		}
		if(ui->letterButtons->checkedButton() == ui->i){
			currImage.letter = "I";
		}
		if(ui->letterButtons->checkedButton() == ui->j){
			currImage.letter = "J";
		}
		if(ui->letterButtons->checkedButton() == ui->k){
			currImage.letter = "K";
		}
		if(ui->letterButtons->checkedButton() == ui->l){
			currImage.letter = "L";
		}
		if(ui->letterButtons->checkedButton() == ui->m){
			currImage.letter = "M";
		}
		if(ui->letterButtons->checkedButton() == ui->n){
			currImage.letter = "N";
		}
		if(ui->letterButtons->checkedButton() == ui->o){
			currImage.letter = "O";
		}
		if(ui->letterButtons->checkedButton() == ui->p){
			currImage.letter = "P";
		}
		if(ui->letterButtons->checkedButton() == ui->q){
			currImage.letter = "Q";
		}
		if(ui->letterButtons->checkedButton() == ui->r){
			currImage.letter = "R";
		}
		if(ui->letterButtons->checkedButton() == ui->s){
			currImage.letter = "S";
		}
		if(ui->letterButtons->checkedButton() == ui->t){
			currImage.letter = "T";
		}
		if(ui->letterButtons->checkedButton() == ui->u){
			currImage.letter = "U";
		}
		if(ui->letterButtons->checkedButton() == ui->v){
			currImage.letter = "V";
		}
		if(ui->letterButtons->checkedButton() == ui->w){
			currImage.letter = "W";
		}
		if(ui->letterButtons->checkedButton() == ui->x){
			currImage.letter = "X";
		}
		if(ui->letterButtons->checkedButton() == ui->y){
			currImage.letter = "Y";
		}
		if(ui->letterButtons->checkedButton() == ui->z){
			currImage.letter = "Z";
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
            currImage.orientation = "NW";
		}
		if(ui->dirButtons->checkedButton() == ui->N){
            currImage.orientation = "N";
		}
		if(ui->dirButtons->checkedButton() == ui->NE){
            currImage.orientation = "NE";
		}
		if(ui->dirButtons->checkedButton() == ui->W){
            currImage.orientation = "W";
		}
		if(ui->dirButtons->checkedButton() == ui->E){
            currImage.orientation = "E";
		}
		if(ui->dirButtons->checkedButton() == ui->SW){
            currImage.orientation = "SW";
		}
		if(ui->dirButtons->checkedButton() == ui->S){
            currImage.orientation = "S";
		}
		if(ui->dirButtons->checkedButton() == ui->SE){
            currImage.orientation = "SE";
		}
    }

    return currImage;
}




