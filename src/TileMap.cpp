#include "TileMap.h"
#include "GameObject.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet) : Component(associated), mapWidth(0), mapHeight(0), mapDepth(0) {
    Load(file);
    SetTileSet(tileSet);
}
void TileMap::Load(std::string file) {
    std::ifstream in(file);
    if (!in.is_open()) {
        std::cerr << "TileMap: falha ao abrir " << file << std::endl;
        return;
    }
    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string content = buffer.str();
    std::replace(content.begin(), content.end(), ',', ' ');
    std::stringstream ss(content);
    ss >> mapWidth >> mapHeight >> mapDepth;
    tileMatrix.clear();
    tileMatrix.reserve(mapWidth * mapHeight * mapDepth);
    int tile;
    while (ss >> tile) {
        tileMatrix.push_back(tile);
    }
    if ((int)tileMatrix.size() != mapWidth * mapHeight * mapDepth) {
        std::cerr << "TileMap: esperava " << mapWidth * mapHeight * mapDepth
                  << " tiles, li " << tileMatrix.size() << std::endl;
    }
}
void TileMap::SetTileSet(TileSet* tileSet) {
    this->tileSet.reset(tileSet); 
}
int& TileMap::At(int x, int y, int z) {
    return tileMatrix[x + y * mapWidth + z * mapWidth * mapHeight];
}
void TileMap::Update(float dt) {}
void TileMap::RenderLayer(int layer) {
    if (!tileSet) return;
    int tw = tileSet->GetTileWidth();
    int th = tileSet->GetTileHeight();
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            tileSet->RenderTile(At(x, y, layer),
                                associated.box.x + x * tw,
                                associated.box.y + y * th);
        }
    }
}
void TileMap::Render() {
    for (int z = 0; z < mapDepth; z++) {
        RenderLayer(z);
    }
}
int TileMap::GetWidth()  { return mapWidth; }
int TileMap::GetHeight() { return mapHeight; }
int TileMap::GetDepth()  { return mapDepth; }