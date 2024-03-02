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

    int GetActualActionPoints() const { return actualActionPoints; } 
    void SubstactActualActionPoints(int pointsSubstracted) { actualActionPoints -= pointsSubstracted; }

    TurnState GetActualState() const { return actualState; }
    void SetActualState(TurnState newState) { actualState = newState; }

    CellData::Owner GetPlayerTurn() const;

private:
    int defaultActionPoints;
    int actualActionPoints;

    TurnState actualState;
};


