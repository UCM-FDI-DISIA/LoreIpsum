#pragma once

//Checkml
#include <game/checkML.h>

#include "ComponentUpdate.h"

#include "managers/Manager.h"
#include "basics/BoxCollider.h"

class NPC;

class ClickDecision :
    public ComponentUpdate
{
public:
    ClickDecision(int decision, ecs::entity_t parent, int scene);   // PAIGRO AQUI --> en vez de pasarle la escena, le pasas
                                                                    // el tipo de decision:
                                                                    // 0 -> no; 1 -> si; 2 -> comprar; 3 -> cambiar escena etc
                                                                    // crear metodos auxiliares si necesario para settear los valores de los
                                                                    // tipos de decisiones (ej: setScene())
    ~ClickDecision();

	void initComponent() override;
	void update() override;

    void OnLeftClickDown();
    void OnLeftClickUp();

    void TakeDecision();

    void setScene(int s); // PAIGRO AQUI

    void purchaseCard();
    void cancelPurchase();

private:
    void caseAccepted();

    ecs::entity_t parent_;
    NPC* myNpc_;
    int scene_;

    int decision_;
    bool click_;

    BoxCollider* collider_;
};

