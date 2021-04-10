#ifndef TILEMAP_H
#define TILEMAP_H

#include <QMainWindow>
#include <QImage>
#include <tilemapbuilder.h>
#include <vector>
#include <string>
#include <Magick++.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Tilemap; }
class QLabel;
class QScrollArea;
QT_END_NAMESPACE

class Tilemap : public QMainWindow
{
    Q_OBJECT

public:
    Tilemap(QWidget *parent = nullptr);
    ~Tilemap();
    bool loadFile(const QString &);

private slots:
    void generate();
    void loadCsvFile();
    void loadTilesetFile();
    void saveAs();

private:
    void setImage(const QImage &newImage);

    Ui::Tilemap *ui;
    QImage image;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    QString tilesetPath;
    QString csvPath;

    Magick::Image magickTilemap;

    double scaleFactor = 1;
};
#endif // TILEMAP_H
