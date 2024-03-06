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

    MatchManager(int defaultActionPoints, TurnState turnStart, BoardManager* bm = nullptr);

    ~MatchManager();

    void initComponent() override;
    void update() override;

    void setActualState(TurnState newState);
    void setBoard(BoardManager* value) { board_ = value; } 
    int getActualActionPoints();
    int getActualActionPointsJ1() const { return actualActionPointsJ1; }
    int getActualActionPointsJ2() const { return actualActionPointsJ2; }
    TurnState getActualState() const { return actualState; }
    Players::Owner getPlayerTurn() const;

    void setBoardManager(BoardManager* b) { board_ = b; }
    void substractActionPoints(int);
    void substractActionPointsJ1(int pointsSubstracted) { actualActionPointsJ1 -= pointsSubstracted; }
    void substractActionPointsJ2(int pointsSubstracted) { actualActionPointsJ2 -= pointsSubstracted; }
    
    void updateVisuals();

private:
    BoardManager* board_ = nullptr;

    int defaultActionPoints;
    int actualActionPointsJ1;
    int actualActionPointsJ2;

    TurnState actualState;

    // visuals
    ecs::entity_t actualTurnVisual;
	ecs::entity_t actionPointsVisualJ1;
    ecs::entity_t actionPointsVisualJ2;

	void setTurnText();
    void resetActualActionPoints();
    void setWinner();
};


