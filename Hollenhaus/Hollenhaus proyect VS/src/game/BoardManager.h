#pragma once
#include "ComponentUpdate.h"
#include <vector>
#include <list>
#include <iostream>
#include <functional>

//class Cell;
class Card;
using SDLEventCallback = std::function<void()>;

#include "../Cell.h"

class BoardManager : public ComponentUpdate
{
public:

    BoardManager();

    ~BoardManager();

    void initComponent() override;

    void update() override;

    bool AddCard(ecs::entity_t card, int posX, int posY);

    bool IsFull();

    Cell* getCell(int x, int y) const;

    std::list<SDLEventCallback> getEffects(Cell* cell) const;


    bool setCard(int x, int y, Card* c, CellData::Owner o); // true si pudo poner carta (no habia otra ya antes)


    int getPlayer1Points() const { return pPlayer1; }
    int getPlayer2Points() const { return pPlayer2; }

    void updateScore();

private:
    //cleon: si en la entrega es una constante, os mataré. bueno, yo os mataré
    const int WIDTH = 4;
    const int HEIGTH = 4;

    // Un vector de vectores de entidades "Cell".
    std::vector<std::vector<ecs::entity_t>> _board;

    int cardsOnBoard;

    void applyAllEffects() const;


    int pPlayer1 = 0;
    int pPlayer2 = 0;

};

