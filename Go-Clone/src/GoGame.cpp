#include "GoGame.h"

#include "GameState.h"


GoGame::GoGame() {
}


GoGame::~GoGame() {
}

void GoGame::Start() {

}

const GameState& GoGame::GetGameState() const {
	return gameState;
}
