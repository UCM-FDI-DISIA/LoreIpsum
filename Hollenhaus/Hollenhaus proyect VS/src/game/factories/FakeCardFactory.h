#pragma once
class FakeCardFactory
{
public:
	FakeCardFactory();
	virtual ~FakeCardFactory();

	virtual ecs::entity_t createFakeCard(int id){}
};

