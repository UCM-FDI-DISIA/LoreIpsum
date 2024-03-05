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
    int getActualActionPointsJ1() const { return actualActionPointsJ1; }
    int getActualActionPointsJ2() const { return actualActionPointsJ2; }
    TurnState getActualState() const { return actualState; }
    CellData::Owner getPlayerTurn() const;

    void setBoardManager(BoardManager* b) { board_ = b; }
    void substractActionPointsJ1(int pointsSubstracted) { actualActionPointsJ1 -= pointsSubstracted; }
    void substractActionPointsJ2(int pointsSubstracted) { actualActionPointsJ2 -= pointsSubstracted; }
    


private:
    BoardManager* board_ = nullptr;

    int defaultActionPoints;
    int actualActionPointsJ1;
    int actualActionPointsJ2;

    TurnState actualState;

    ecs::entity_t actualText;

	void setTurnText();
    void resetActualActionPoints();
    void setWinner();
};


