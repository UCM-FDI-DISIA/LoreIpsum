#pragma once
#include "../ComponentUpdate.h"
#include "BoardManager.h"

class IA_manager;

class MatchManager : public ComponentUpdate
{
public:

    MatchManager(int defaultActionPointsJ1, int defaultActionPointsJ2, Turns::State turnStart, BoardManager* bm = nullptr);

    ~MatchManager();

    void initComponent() override;
    void update() override;

    // Getters & setters del estado de la partida
    void setActualState(Turns::State newState);
    Turns::State getActualState() const { return actualState; }
    Players::Owner getPlayerTurn() const;   // Devuelve el turno activo con el tipo usado en "BoardManager". 

    // Getters de los puntos de acci�n
    int getActualPlayerActualActionPoints();
    int getActualActionPointsJ1() const { return actualActionPointsJ1; }
    int getActualActionPointsJ2() const { return actualActionPointsJ2; }

    // M�todos para restar puntos de acci�n
    void substractActualPlayerActionPoints(int);
    void substractActionPointsJ1(int pointsSubstracted) { actualActionPointsJ1 -= pointsSubstracted; }
    void substractActionPointsJ2(int pointsSubstracted) { actualActionPointsJ2 -= pointsSubstracted; }
    
    // Setters para las referencias de los elementos visuales
    void setActualTurnVisual(ecs::entity_t visual) { actualTurnVisual = visual; }
    void setActionPointsVisualJ1(ecs::entity_t visual) { actionPointsVisualJ1 = visual; }
    void setActionPointsVisualJ2(ecs::entity_t visual) { actionPointsVisualJ2 = visual; }

    // Setter de la referencia al board
    void setBoardManager(BoardManager* b) { board_ = b; }

    // M�todo para actualizar el aspecto de las referencias visuales del MatchManager
    void updateVisuals();

    void setIA_Manager(IA_manager* ia);
    //solo la IA deberia llamar a este metodo
    void endTurnIA();
private:

    Turns::State actualState;

    // Queremos una referencia al board para detectar cu�ndo se llena y acabar la partida.
    // Tambi�n necesitamos el board para evaluar qu� jugador tiene m�s puntos y pasarlo a la data.
    BoardManager* board_ = nullptr;

    int defaultActionPointsJ1;
    int defaultActionPointsJ2;
    int actualActionPointsJ1;
    int actualActionPointsJ2;

    // Referencias a los elementos del HUD
    ecs::entity_t actualTurnVisual;
	ecs::entity_t actionPointsVisualJ1;
    ecs::entity_t actionPointsVisualJ2;

    IA_manager* ia_manager;

    void resetActualActionPoints();

    // M�todo para pasarle el ganador al GameState y guardarlo en data.
    void setWinnerOnData();


    void startTurnIA();
};


