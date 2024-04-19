#pragma once
class DecisionComponent : public ComponentUpdate
{
public:
	//----Constructora:
	DecisionComponent();
	//----Destructora:
	~DecisionComponent();


	void setDecision(int i);

	void manageDecisions();

private:

	int index;

};

