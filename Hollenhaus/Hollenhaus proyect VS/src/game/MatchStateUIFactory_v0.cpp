#include "pch.h"
#include "MatchStateUIFactory_v0.h"

#include "TextComponent.h"
#include "MatchManager.h"
#include "EndTurnButton.h"

ecs::entity_t MatchStateUIFactory_v0::createVisual_NextTurnButton(int posX, int posY)
{
    ecs::entity_t endTurnButton = Instantiate(Vector2D(posX, posY));  // 200, 265
    endTurnButton->getComponent<Transform>()->getGlobalScale().set(1.2, 1.2);
    endTurnButton->addComponent<SpriteRenderer>("EndTurnButton");
    endTurnButton->addComponent<BoxCollider>();
    endTurnButton->addComponent<EndTurnButton>(MatchManager::TurnState::TurnJ1);
    endTurnButton->setLayer(4);
    return endTurnButton;
}

ecs::entity_t MatchStateUIFactory_v0::createVisual_ActionPointsCounter(int posX, int posY)
{
    ecs::entity_t actionPointsVisual = Instantiate(Vector2D(posX, posY)); // 100, 500 | 100, 100
    actionPointsVisual->addComponent<TextComponent>("Puntos de accion:\n---",
        "8bit_24pt", SDL_Color({ 255, 255, 0, 255 }), 200,  
        TextComponent::BoxPivotPoint::CenterCenter,
        TextComponent::TextAlignment::Center);

    actionPointsVisual->setLayer(9);
    return actionPointsVisual;
}

ecs::entity_t MatchStateUIFactory_v0::createVisual_ScoreCounter(int posX, int posY, SDL_Color color)
{
    ecs::entity_t scoreVisual = Instantiate(Vector2D(posX, posY)); // 300, 350 | 300, 225
    scoreVisual->addComponent<TextComponent>("0", 
        "8bit_48pt", color, 120,    // 102, 255, 255 | 255, 102, 255
        TextComponent::BoxPivotPoint::CenterCenter, 
        TextComponent::TextAlignment::Center);
    scoreVisual->setLayer(9);

    return scoreVisual;
}

ecs::entity_t MatchStateUIFactory_v0::createVisual_PlayerTurnIndicator(int posX, int posY)
{
    ecs::entity_t actualTurnVisual = Instantiate(Vector2D(posX, posY)); // 700, 325
    actualTurnVisual->setLayer(2);

    actualTurnVisual->addComponent<TextComponent>("Turno de:\n---",
        "8bit_32pt", SDL_Color({ 255, 255, 255, 255 }), 200,
        TextComponent::BoxPivotPoint::CenterBot,
        TextComponent::TextAlignment::Center);

    return actualTurnVisual;
}

ecs::entity_t MatchStateUIFactory_v0::createVisual_BackgroundBlackBox(int posX, int posY, float xPixelsSize, float yPixelsSize)
{

    ecs::entity_t blackBox = Instantiate(Vector2D(posX, posY)); // 600, 200
    blackBox->addComponent<SpriteRenderer>("black_box");

    // Obtenemos la altura y anchura de "black_box" para definir el tamaño del sprite en pixeles
    int textureW = blackBox->getComponent<SpriteRenderer>()->getTexture()->width();
    int textureH = blackBox->getComponent<SpriteRenderer>()->getTexture()->height();
    blackBox->getComponent<Transform>()->getGlobalScale().set(xPixelsSize / textureW, yPixelsSize / textureH);

    blackBox->setLayer(1);

    return blackBox;
}

ecs::entity_t MatchStateUIFactory_v0::createVisual_BackgroundBoard()
{
    ecs::entity_t background = Instantiate();
    background->addComponent<Transform>();
    background->getComponent<Transform>()->getGlobalScale().set(0.555, 0.555);
    background->addComponent<SpriteRenderer>("board");
    return background;
}
