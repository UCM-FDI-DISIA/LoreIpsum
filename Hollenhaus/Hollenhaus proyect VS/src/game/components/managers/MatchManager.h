#pragma once

//Checkml
#include <game/checkML.h>

#include "../ComponentUpdate.h"
#include "BoardManager.h"
#include "../HandComponent.h"

class IA_manager;
class NetGame;

class MatchManager : public ComponentUpdate
{
public:

    MatchManager(int defaultActionPointsJ1, int defaultActionPointsJ2, Turns::State turnStart, BoardManager* bm = nullptr, std::string j2 = " ");

    ~MatchManager();

    void initComponent() override;
    void update() override;

    // Getters & setters del estado de la partida
    void setActualState(Turns::State newState);
    Turns::State getActualState() const { return actualState; }
    Players::Owner getPlayerTurn() const;   // Devuelve el turno activo con el tipo usado en "BoardManager". 

    // Getters de los puntos de acción
    int getActualPlayerActualActionPoints();
    int getActualActionPointsJ1() const { return actualActionPointsJ1; }
    int getActualActionPointsJ2() const { return actualActionPointsJ2; }

    // Métodos para restar puntos de acción
    void substractActualPlayerActionPoints(int);
    void substractActionPointsJ1(int pointsSubstracted) { actualActionPointsJ1 -= pointsSubstracted; }
    void substractActionPointsJ2(int pointsSubstracted) { actualActionPointsJ2 -= pointsSubstracted; }
    
    // Setters para las referencias de los elementos visuales
    void setActualTurnVisual(ecs::entity_t visual) { actualTurnVisual = visual; }
    void setActionPointsVisualJ1(ecs::entity_t visual) { actionPointsVisualJ1 = visual; }
    void setActionPointsVisualJ2(ecs::entity_t visual) { actionPointsVisualJ2 = visual; }
    void setActionPointsJ1(const std::array<ecs::entity_t, 4>& visual) { actionPointsJ1 = visual; }
    void setActionPointsJ2(const std::array<ecs::entity_t, 4>& visual) { actionPointsJ2 = visual; }

    // Setter de la referencia al board
    void setBoardManager(BoardManager* b) { board_ = b; }

    // Método para actualizar el aspecto de las referencias visuales del MatchManager
    void updateVisuals();

    void setIA_Manager(IA_manager* ia);

    void setNetGame(NetGame* ng);
    //solo la IA deberia llamar a este metodo
    void endTurnIA();

    //envia el mensaje correspondiente
    void changeTurnMultiplayer();

    void InstantiatePanelFinPartida(int winner);

    // Revisa si no hay más jugadas disponibles y pasa de turno si afirmativo
    void CheckNextTurnAutomatic();

    void SetHandComponent(HandComponent* hand) { playerJ1Hand = hand; }

private:

    Turns::State actualState;

    // Queremos una referencia al board para detectar cuándo se llena y acabar la partida.
    // También necesitamos el board para evaluar qué jugador tiene más puntos y pasarlo a la data.
    BoardManager* board_ = nullptr;

    // Queremos una referencia a la mano del jugador para pasar turno automáticamente si no tiene jugadas disponibles
    HandComponent* playerJ1Hand;

    int defaultActionPointsJ1;
    int defaultActionPointsJ2;
    int actualActionPointsJ1;
    int actualActionPointsJ2;
    void turnPointsOff();
    void turnPointsOn();
    void turnEveryPointOn();



    bool isBoss;
    std::string j2_;

    // Referencias a los elementos del HUD
    ecs::entity_t actualTurnVisual;
	ecs::entity_t actionPointsVisualJ1; // en texto
    ecs::entity_t actionPointsVisualJ2; //en texto
    std::array<ecs::entity_t, 4> actionPointsJ1; // en imagenes
    std::array<ecs::entity_t, 4> actionPointsJ2; // en imagenes

    IA_manager* ia_manager;

    NetGame* netGame = nullptr;

    void resetActualActionPoints();

    // Método para pasarle el ganador al GameState y guardarlo en data.
    void setWinnerOnData();

    void startTurnIA();



};


