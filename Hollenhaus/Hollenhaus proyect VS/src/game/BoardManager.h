#pragma once
#include "ComponentUpdate.h"
#include <vector>
#include <list>
#include <iostream>
#include <functional>
#include "../Cell.h"

//class Cell;
class Card;
using SDLEventCallback = std::function<void()>;

constexpr int DEFAULT_SIZE = 4; 

class BoardManager : public ComponentUpdate
{
public:
    BoardManager();
    BoardManager(int);
    ~BoardManager() override;

    void initComponent() override;
    void update() override;

    bool addCard(ecs::entity_t card, int posX, int posY);
    bool isFull() const;
    void updateScore();

    /// Setters
    bool setCard(int x, int y, Card* c, CellData::Owner o); // true si pudo poner carta (no habia otra ya antes)

    /// Getters
    int getPlayer1Points() const { return pPlayer1; }
    int getPlayer2Points() const { return pPlayer2; }
    Cell* getCell(int x, int y) const;
    std::list<SDLEventCallback> getEffects(Cell* cell) const;

private:
    //cleon: si en la entrega es una constante, os mataré. bueno, yo os mataré
    int size = DEFAULT_SIZE;

    // Un vector de vectores de entidades "Cell".
    std::vector<std::vector<ecs::entity_t>> _board;

    int cardsOnBoard = 0;

    /// match manager
    void applyAllEffects() const;
    int pPlayer1 = 0;
    int pPlayer2 = 0;
};

