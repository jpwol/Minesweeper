#include "TextureManager.h"

void TextureManager::hashTexture(const std::string &key,
                                 const std::string &path,
                                 SDL_Renderer *renderer) {
  if (textures.find(key) == textures.end()) {
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (surface == NULL) {
      printf("Error: Texture could not be loaded to surface.\n%s\n",
             SDL_GetError());
      return;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == NULL) {
      printf("Error: Unable to create texture from surface.\n%s\n",
             SDL_GetError());
    }
    textures[key] = texture;
  }
}

void TextureManager::loadTextures(SDL_Renderer *renderer) {
  hashTexture("tileFresh", "../res/tile/freshTileSmall.bmp", renderer);
  hashTexture("tileShown", "../res/tile/clickedTileSmall.bmp", renderer);
  hashTexture("tileFlagged", "../res/tile/flaggedTileSmall.bmp", renderer);
  hashTexture("tileFlaggedWrong", "../res/tile/flaggedTileWrongSmall.bmp",
              renderer);
  hashTexture("number1", "../res/tile/numberedTile1Small.bmp", renderer);
  hashTexture("number2", "../res/tile/numberedTile2Small.bmp", renderer);
  hashTexture("number3", "../res/tile/numberedTile3Small.bmp", renderer);
  hashTexture("number4", "../res/tile/numberedTile4Small.bmp", renderer);
  hashTexture("number5", "../res/tile/numberedTile5Small.bmp", renderer);
  hashTexture("number6", "../res/tile/numberedTile6Small.bmp", renderer);
  hashTexture("number7", "../res/tile/numberedTile7Small.bmp", renderer);
  hashTexture("number8", "../res/tile/numberedTile8Small.bmp", renderer);
  hashTexture("mine", "../res/tile/bombTileSmall.bmp", renderer);

  hashTexture("NumbersTileset", "../res/ui/BoardNumbers.bmp", renderer);
  hashTexture("UIHeader", "../res/ui/UIHeader.bmp", renderer);
  hashTexture("BombCountBorder", "../res/ui/NumbersBoarder.bmp", renderer);

  hashTexture("UIButtons", "../res/ui/buttons/UIButtons.png", renderer);
  hashTexture("Button1", "../res/ui/buttons/Button1.bmp", renderer);
  hashTexture("Button2", "../res/ui/buttons/Button2.bmp", renderer);
  hashTexture("Button3", "../res/ui/buttons/Button3.bmp", renderer);
  hashTexture("ButtonR", "../res/ui/buttons/ButtonR.bmp", renderer);
}

SDL_Texture *TextureManager::getTexture(const std::string &key) {
  return textures[key];
}

void TextureManager::handleTileRender(SDL_Renderer *renderer, Board &board,
                                      bool loseState) {
  for (const auto tile : board.accessTiles()) {
    SDL_Rect rect{tile.x * 32, tile.y * 32 + 52, 32, 32};
    if (!board.getTileFlag(tile.x, tile.y, CLICKED) &&
        !board.getTileFlag(tile.x, tile.y, FLAGGED))
      SDL_RenderCopy(renderer, getTexture("tileFresh"), NULL, &rect);
    else if (!board.getTileFlag(tile.x, tile.y, CLICKED) &&
             board.getTileFlag(tile.x, tile.y, FLAGGED))
      SDL_RenderCopy(renderer, getTexture("tileFlagged"), NULL, &rect);
    if (loseState && board.getTileFlag(tile.x, tile.y, FLAGGED) &&
        board.getTileType(tile.x, tile.y) != Mine)
      SDL_RenderCopy(renderer, getTexture("tileFlaggedWrong"), NULL, &rect);
    if (board.getTileFlag(tile.x, tile.y, CLICKED) == true)
      SDL_RenderCopy(renderer, getTexture(tile.texKey), NULL, &rect);
  }
}

void TextureManager::handleUIRender(SDL_Renderer *renderer, int bombIndex,
                                    Signal signal) {
  SDL_Rect srcrect;
  SDL_Rect dstrect{12, 12, 20, 28};
  SDL_Rect btndst{(tileSize * board.cols) - 116, 12, 20, 28};
  SDL_Rect UIHeader{0, 0, tileSize * board.cols, 52};
  SDL_Rect BombCountBorder{8, 8, 68, 36};
  SDL_Rect UIButtons{tileSize * board.cols - 120, 8, 112, 36};

  int hun = bombIndex / 100;
  int tens = (bombIndex / 10) % 10;
  int units = bombIndex % 10;

  SDL_RenderCopy(renderer, getTexture("UIHeader"), NULL, &UIHeader);
  SDL_RenderCopy(renderer, getTexture("BombCountBorder"), NULL,
                 &BombCountBorder);
  SDL_RenderCopy(renderer, getTexture("UIButtons"), NULL, &UIButtons);

  switch (signal) {
  case Button1:
    SDL_RenderCopy(renderer, getTexture("Button1"), NULL, &btndst);
    break;
  case Button2:
    btndst.x += 28;
    SDL_RenderCopy(renderer, getTexture("Button2"), NULL, &btndst);
    break;
  case Button3:
    btndst.x += 56;
    SDL_RenderCopy(renderer, getTexture("Button3"), NULL, &btndst);
    break;
  case ButtonR:
    btndst.x += 84;
    SDL_RenderCopy(renderer, getTexture("ButtonR"), NULL, &btndst);
    break;
  case Zero:
    SDL_RenderCopy(renderer, getTexture("UIButtons"), NULL, &UIButtons);
    break;
  default:
    SDL_RenderCopy(renderer, getTexture("UIButtons"), NULL, &UIButtons);
    break;
  }

  if (bombIndex >= 0) {
    for (int i = 0; i < 3; i++) {
      srcrect = {20, 28, 20, 28};
      switch (i) {
      case 0:
        srcrect.x = (hun < 5) ? srcrect.x *= hun : srcrect.x *= (hun - 5);
        srcrect.y = (hun < 5) ? srcrect.y *= 0 : srcrect.y *= 1;
        break;
      case 1:
        srcrect.x = (tens < 5) ? srcrect.x *= tens : srcrect.x *= (tens - 5);
        srcrect.y = (tens < 5) ? srcrect.y *= 0 : srcrect.y *= 1;
        break;
      case 2:
        srcrect.x = (units < 5) ? srcrect.x *= units : srcrect.x *= (units - 5);
        srcrect.y = (units < 5) ? srcrect.y *= 0 : srcrect.y *= 1;
        break;
      default:
        break;
      }
      SDL_RenderCopy(renderer, getTexture("NumbersTileset"), &srcrect,
                     &dstrect);
      dstrect.x += 20;
    }
  } else {
    for (int i = 0; i < 3; i++) {
      srcrect = {0, 0, 20, 28};
      SDL_RenderCopy(renderer, getTexture("NumbersTileset"), &srcrect,
                     &dstrect);
      dstrect.x += 20;
    }
  }
}

void TextureManager::cleanTextures() {
  for (auto &pair : textures) {
    SDL_DestroyTexture(pair.second);
  }
  textures.clear();
}
