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

    MatchManager(int defaultActionPointsJ1, int defaultActionPointsJ2, TurnState turnStart, BoardManager* bm = nullptr);

    ~MatchManager();

    void initComponent() override;
    void update() override;

    // Getters & setters del estado de la partida
    void setActualState(TurnState newState);
    TurnState getActualState() const { return actualState; }
    Players::Owner getPlayerTurn() const;   // Devuelve el turno activo con el tipo usado en "BoardManager". 

    // Getters de los puntos de acción
    int getActivePlayerActualActionPoints();
    int getActualActionPointsJ1() const { return actualActionPointsJ1; }
    int getActualActionPointsJ2() const { return actualActionPointsJ2; }

    // Métodos para restar puntos de acción
    void substractActualPlayerActionPoints(int);
    void substractActionPointsJ1(int pointsSubstracted) { actualActionPointsJ1 -= pointsSubstracted; }
    void substractActionPointsJ2(int pointsSubstracted) { actualActionPointsJ2 -= pointsSubstracted; }
    

    // Setter de la referencia al board
    void setBoardManager(BoardManager* b) { board_ = b; }

    void updateVisuals();

private:

    TurnState actualState;

    BoardManager* board_ = nullptr;

    int defaultActionPointsJ1;
    int defaultActionPointsJ2;
    int actualActionPointsJ1;
    int actualActionPointsJ2;

    // visuals
    ecs::entity_t actualTurnVisual;
	ecs::entity_t actionPointsVisualJ1;
    ecs::entity_t actionPointsVisualJ2;

	void setTurnText();
    void resetActualActionPoints();
    void setWinner();
};


