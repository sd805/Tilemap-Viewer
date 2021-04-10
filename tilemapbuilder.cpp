#include "tilemapbuilder.h"

#include <fstream>
#include <algorithm>

#include <iostream>

std::vector<std::vector<int>> TilemapBuilder::ReadCSV(const std::string& filename)
{
    std::ifstream file(filename);
    int columnCount = 0;
    int rowCount = 0;
    std::string line;
    char delimiter = ',';

    // Get the max number of columns and rows.
    while (std::getline(file, line, '\n'))
    {
        columnCount = std::max(columnCount, (int) (std::count(line.begin(), line.end(), delimiter) + 1));
        rowCount++;
    }

    // Initialize all values in the 2D vector to -1
    std::vector<std::vector<int>> vec(rowCount, std::vector<int>(columnCount, -1));

    // return to beginning of file to populate 2D vector
    file.clear();
    file.seekg(0);
    columnCount = 0;
    rowCount = 0;
    std::string token;
    std::string::iterator stringIterator;
    int subStart;
    int subEnd;

    while (std::getline(file, line, '\n'))
    {
        subStart = 0;
        subEnd = 0;
        stringIterator = line.begin();
        while (stringIterator != line.end())
        {
            if (*stringIterator == ',')
            {
                // If the cell has a value, put it in the 2D vector. Otherwise leave as -1.
                if (subEnd > 0)
                {
                    token = line.substr(subStart, subEnd);
                    vec[rowCount][columnCount] = std::stoi(token);
                }
                subStart += subEnd + 1;
                subEnd = 0;
                stringIterator++;

                columnCount++;
            }
            else
            {
                stringIterator++;
                subEnd++;
            }

            if (stringIterator == line.end())
            {
                if (subEnd > 0)
                {
                    token = line.substr(subStart, subEnd);
                    vec[rowCount][columnCount] = std::stoi(token);
                }
            }
        }
        columnCount = 0;
        rowCount++;
    }
    return vec;
}

Magick::Image TilemapBuilder::createTiledImage(std::vector<std::vector<int>> csvVec, std::string tilemapFile, int tileWidth)
{
    Magick::Image tilemap(tilemapFile);

    int numTileColumns = tilemap.size().width() / tileWidth;

    if (numTileColumns < 1)
        throw std::range_error("Tile width is too large.");

    std::vector<Magick::Image> rowImages;


    for (int i = 0; i < csvVec.size(); ++i)
    {
        std::vector<Magick::Image> tiledImages;
        for (int j = 0; j < csvVec[i].size(); ++j)
        {
            int tileIndex = csvVec[i][j];

            if (tileIndex == -1)
            {
                Magick::Image transparentSquare(Magick::Geometry(tileWidth, tileWidth), Magick::Color(0, 0, 0, 0));
                tiledImages.push_back(transparentSquare);
            }
            else
            {
                int xOffset = tileIndex % numTileColumns;
                int yOffset = tileIndex / numTileColumns;

                int xCropPos = tileWidth * xOffset;
                int yCropPos = tileWidth * yOffset;

                Magick::Image tile = tilemap;

                if (xCropPos > tile.size().width() || yCropPos > tile.size().height())
                    throw std::range_error("CSV file contains out-of-range tile.");

                tile.crop(Magick::Geometry(tileWidth, tileWidth, xCropPos, yCropPos));
                tiledImages.push_back(tile);
            }
        }
        Magick::Image appendedRow;
        Magick::appendImages(&appendedRow, tiledImages.begin(), tiledImages.end());
        rowImages.push_back(appendedRow);
    }

    Magick::Image appendedFinal;
    Magick::appendImages(&appendedFinal, rowImages.begin(), rowImages.end(), true);
    return appendedFinal;
}
