#include "Game.h"
#include "TextureManager.h"

void Game::initGame(int rows, int cols) {
  board = Board(rows, cols);
  int wWidth = board.cols * 32;
  int wHeight = board.rows * 32 + 52;
  if (!(SDL_Init(SDL_INIT_VIDEO))) {
    window = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, wWidth, wHeight, 0);
    if (window == NULL) {
      std::cerr << "Error: SDL Failed to create window. " << SDL_GetError()
                << '\n';
      return;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
      std::cerr << "Error: SDL Failed to create renderer. " << SDL_GetError()
                << '\n';
      return;
    }
  } else {
    std::cerr << "ERROR: SDL FAILED TO INITIALIZE. " << SDL_GetError() << '\n';
    return;
  }

  board.hashTiles();
  TextureManager::loadTextures(renderer);
  board.initBoard(showTiles, loseState, bombIndex, desiredDensity);
}

void Game::handleEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      running = false;
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        running = false;
        break;
      case SDLK_e:
        showTiles = !showTiles;
        break;
      case SDLK_SPACE:
        board.initBoard(showTiles, loseState, bombIndex, desiredDensity);
        break;
      case SDLK_1:
        handleResize(8, 8, 16);
        break;
      case SDLK_2:
        handleResize(16, 16, 16);
        break;
      case SDLK_3:
        handleResize(16, 30, 20.625);
        break;
      default:
        break;
      }
      break;
    default:
      break;
    }
  }
}

void Game::handleInput() {
  if (mouseState == 4 || mouseState == 1)
    bDown = true;
  if (mouseState == 0)
    bDown = false;
}

void Game::update() {
  mouseState = SDL_GetMouseState(&mouseX, &mouseY);
  int mX = 0, mY = 0;

  if (mouseY >= 12 && mouseY <= 32 && !bDown) {
    if (mouseX >= board.cols * 32 - 120 && mouseX <= board.cols * 32 - 92) {
      signal = Button1;
      if (mouseState == 1)
        handleResize(8, 8, 16);
    } else if (mouseX >= board.cols * 32 - 92 &&
               mouseX <= board.cols * 32 - 64) {
      signal = Button2;
      if (mouseState == 1)
        handleResize(16, 16, 16);
    } else if (mouseX >= board.cols * 32 - 64 &&
               mouseX <= board.cols * 32 - 36) {
      signal = Button3;
      if (mouseState == 1)
        handleResize(16, 30, 20.625);
    } else if (mouseX >= board.cols * 32 - 36 &&
               mouseX <= board.cols * 32 - 8) {
      signal = ButtonR;
      if (mouseState == 1)
        board.initBoard(showTiles, loseState, bombIndex, desiredDensity);
    } else
      signal = Zero;
  } else
    signal = Zero;

  if (mouseX >= 0 && mouseX < board.cols * 32 && mouseY >= 52 &&
      mouseY < board.rows * 32 + 52) {
    mX = mouseX / 32, mY = (mouseY - 52) / 32;
    if (mouseState == 1 && !bDown && !board.getTileFlag(mX, mY, CLICKED) &&
        !board.getTileFlag(mX, mY, FLAGGED) && !loseState) {
      board.setTileFlag(mX, mY, CLICKED);
      if (board.getTileType(mX, mY) == Mine)
        board.triggerLoseState(loseState);
      board.cycleTiles(mX, mY);
    }
    if (mouseState == 4 && !bDown && !board.getTileFlag(mX, mY, CLICKED) &&
        !loseState) {
      if (!board.getTileFlag(mX, mY, FLAGGED))
        bombIndex--;
      else if (board.getTileFlag(mX, mY, FLAGGED))
        bombIndex++;
      board.setTileFlag(mX, mY, FLAGGED);
    }
  }
  handleInput();
}

void Game::render() {
  SDL_RenderClear(renderer);
  TextureManager::handleUIRender(renderer, bombIndex, signal);
  TextureManager::handleTileRender(renderer, board, loseState);
  SDL_RenderPresent(renderer);
}

void Game::cleanup() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  TextureManager::cleanTextures();
  SDL_Quit();
}

void Game::run() {
  while (running) {
    handleEvents();
    update();
    render();
  }
}
