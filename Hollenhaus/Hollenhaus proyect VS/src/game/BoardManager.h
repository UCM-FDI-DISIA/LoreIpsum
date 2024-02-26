#pragma once
#include "ComponentUpdate.h"
#include <vector>

class Cell;
class Card;

class BoardManager : public ComponentUpdate
{
public:

    BoardManager();

    ~BoardManager();

    void initComponent() override;

    void update() override;

    bool AddCard(ecs::entity_t card, int posX, int posY);

    bool IsFull();

private:
    // si en la entrega es una constante, os mataré. bueno, yo os mataré
    const int WIDTH = 4;
    const int HEIGTH = 4;

    // Un vector de vectores de entidades "Cell".
    std::vector<std::vector<ecs::entity_t>> _board;

    int cardsOnBoard;


};

