#include <QColorSpace>
#include <QFileDialog>
#include <QStandardPaths>
#include <QImageWriter>
#include <QImageReader>
#include <QMessageBox>
#include <QScrollArea>

#include "tilemap.h"
#include "ui_tilemap.h"
#include "tilemapbuilder.h"
#include <Magick++.h>

#include <iostream>

Tilemap::Tilemap(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tilemap)
{
    ui->setupUi(this);

    connect(ui->tilesetButton, &QPushButton::pressed, this, &Tilemap::loadTilesetFile);
    connect(ui->csvButton, &QPushButton::pressed, this, &Tilemap::loadCsvFile);
    connect(ui->generateButton, &QPushButton::pressed, this, &Tilemap::generate);
    connect(ui->actionSaveAs, &QAction::triggered, this, &Tilemap::saveAs);
}

Tilemap::~Tilemap()
{
    delete ui;
}


void Tilemap::setImage(const QImage &newImage)
{
    image = newImage;
    ui->imageLabel->setPixmap(QPixmap::fromImage(image));
    scaleFactor = 1.0;
}


void Tilemap::loadCsvFile()
{
    QFileDialog dialog(this, tr("Open File"));
    dialog.setDirectory(QDir::currentPath());
    dialog.setNameFilter("CSV files (*.csv)");
    dialog.setDefaultSuffix("csv");
    if(dialog.exec() == QDialog::Accepted)
    {
        QString filepath = dialog.selectedFiles().first().toLatin1();
        QString filename = filepath.section("/", -1, -1);
        ui->csvLabel->setText(filename);
        csvPath = filepath;
    }
}

void Tilemap::loadTilesetFile()
{
    QFileDialog dialog(this, tr("Open File"));
    dialog.setDirectory(QDir::currentPath());
    dialog.setNameFilter("Image Files (*.png *.jpg)");
    dialog.setDefaultSuffix("jpg");
    if(dialog.exec() == QDialog::Accepted)
    {
        QString filepath = dialog.selectedFiles().first().toLatin1();
        QString filename = filepath.section("/", -1, -1);
        ui->tilesetLabel->setText(filename);
        tilesetPath = filepath;
    }
}

void Tilemap::generate()
{
    if (csvPath.isNull())
        return;
    if (tilesetPath.isNull())
        return;

    std::vector<std::vector<int>> csvFile = TilemapBuilder::ReadCSV(csvPath.toStdString());

    int tileWidth = ui->widthInput->value();

    try
    {
        magickTilemap = TilemapBuilder::createTiledImage(csvFile, tilesetPath.toStdString(), tileWidth);
        magickTilemap.write("output.png");
    }
    catch (const std::exception &exec)
    {
        std::cerr << exec.what() << std::endl;
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(), tr(exec.what()));
        return;
    }

    QString url = R"(output.png)";
    image = QImage(url);
    ui->imageLabel->setPixmap(QPixmap::fromImage(image));

    const QString message = tr("%1x%2, Depth: %3")
        .arg(image.width()).arg(image.height()).arg(image.depth());
    ui->statusbar->showMessage(message);
}

void Tilemap::saveAs()
{
    QFileDialog dialog(this, tr("Save File As"));
    dialog.setDirectory(QDir::currentPath());
    dialog.setNameFilter("Image files (*.png)");
    dialog.setDefaultSuffix("png");

    if(dialog.exec() == QDialog::Accepted)
    {
        std::string filepath = dialog.selectedFiles().first().toStdString();
        magickTilemap.write(filepath);
    }
}
