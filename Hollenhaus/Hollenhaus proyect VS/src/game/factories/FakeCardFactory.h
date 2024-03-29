#pragma once
class FakeCardFactory
{
public:
	FakeCardFactory(){}
	virtual ~FakeCardFactory() {}

	virtual ecs::entity_t createFakeCard(int id, Vector2D pos, int cost, int value, std::string& sprite, bool unblockable, std::vector<JsonData::CardEffect>& effects) = 0;
};