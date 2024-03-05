#pragma once
#include "ComponentUpdate.h"
#include "BoardManager.h"


class MatchManager : public ComponentUpdate
{
public:
    enum TurnState {
        TurnJ1,
        TurnJ2,
        Finish
    };

    MatchManager(int defaultActionPoints, TurnState turnStart);

    ~MatchManager();

    void initComponent() override;
    void update() override;

    void getActualState(TurnState newState);
    int getActualActionPoints() const { return actualActionPoints; }
    TurnState getActualState() const { return actualState; }
    CellData::Owner getPlayerTurn() const;

    void setBoardManager(BoardManager* b) { board_ = b; }
    void substractActualActionPoints(int pointsSubstracted) { actualActionPoints -= pointsSubstracted; }



private:
    BoardManager* board_ = nullptr;

    int defaultActionPoints;
    int actualActionPoints;

    TurnState actualState;

    void resetActualActionPoints();
    void setWinner();
};


