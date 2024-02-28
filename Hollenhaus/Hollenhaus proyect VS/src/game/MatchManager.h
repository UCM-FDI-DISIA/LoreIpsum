#pragma once
#include "ComponentUpdate.h"
class MatchManager : public ComponentUpdate
{
public:
    enum MatchStates {
        TurnJ1,
        TurnJ2,
        Finish
    };

    MatchManager();

    ~MatchManager();

    void initComponent() override;

    void update() override;

    int GetActualActionPoints() const { return actualActionPoints; }
    void SubstactActualActionPoints(int pointsSubstracted) { actualActionPoints -= pointsSubstracted; }

    MatchStates GetActualState() const { return actualState; }
    void SetActualState(MatchStates newState) { actualState = newState; }

private:
    int defaultActionPoints;
    int actualActionPoints;

    MatchStates actualState;
};

