#pragma once
#include "Game.h"
#include <SDL2/SDL_image.h>

class TextureManager {
  static inline const int tileSize = 32;
  static inline std::unordered_map<std::string, SDL_Texture *> textures;

public:
  static void hashTexture(const std::string &key, const std::string &path,
                          SDL_Renderer *renderer);
  static void loadTextures(SDL_Renderer *renderer);
  static SDL_Texture *getTexture(const std::string &key);
  static void handleTileRender(SDL_Renderer *renderer, Board &board,
                               bool loseState);
  static void handleUIRender(SDL_Renderer *renderer, int bombIndex,
                             Signal signal);
  static void cleanTextures();
};
