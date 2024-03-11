
#include "BoardFactory_v0.h"
#include "checkML.h"
#include "GameState.h"
#include "CardFactory_v0.h"


class NievesState :
    public GameState
{
public:
    NievesState();
    virtual ~NievesState();


    void refresh() override;
    void update() override;
    void render() const override;

    void onEnter() override;
    void onExit() override;

    void setWinner(int w) override{

        data->setWinner(w);
    }

private:
    ecs::entity_t card;
    ecs::entity_t board;
};

