
#include "../checkML.h"
#include "GameState.h"

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

    void setWinnerOnData(int w) override;

private:
    ecs::entity_t card;
    ecs::entity_t board;
};

