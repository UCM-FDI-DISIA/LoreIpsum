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

    void setBoardManager(BoardManager* b) { board_ = b; }

    int GetActualActionPoints() const { return actualActionPoints; } 
    void SubstactActualActionPoints(int pointsSubstracted) { actualActionPoints -= pointsSubstracted; }

    TurnState GetActualState() const { return actualState; }
    void SetActualState(TurnState newState);

    CellData::Owner GetPlayerTurn() const;

private:
    BoardManager* board_ = nullptr;

    int defaultActionPoints;
    int actualActionPoints;

    TurnState actualState;

    void ResetActualActionPoints();
    void setWinner();
};


