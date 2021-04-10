#ifndef TILEMAPBUILDER_H
#define TILEMAPBUILDER_H

#include <vector>
#include <string>
#include <Magick++.h>

class TilemapBuilder
{
public:
    static std::vector<std::vector<int>> ReadCSV(const std::string& filename);
    static Magick::Image createTiledImage(std::vector<std::vector<int>> csvVec, std::string tilemapFile, int tileWidth);
};

#endif // TILEMAPBUILDER_H
