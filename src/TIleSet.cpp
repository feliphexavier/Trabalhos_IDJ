#include <iostream>
#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file): tileSet(file), tileWidth(tileWidth), tileHeight(tileHeight), tileCount(0) {
    if (!tileSet.IsOpen()) {
        std::cerr << "TileSet: falha ao abrir " << file << std::endl;
        return;
    }
    int columns = tileSet.GetWidth() / tileWidth;
    int rows    = tileSet.GetHeight() / tileHeight;
    tileSet.SetFrameCount(columns, rows);
    tileCount = columns * rows;
}
void TileSet::RenderTile(unsigned index, float x, float y) {
    if (index >= (unsigned)tileCount) return;
    tileSet.SetFrame(index);
    tileSet.Render((int)x, (int)y, tileWidth, tileHeight);
}

int TileSet::GetTileWidth()  { return tileWidth; }
int TileSet::GetTileHeight() { return tileHeight; }