#pragma once
#include "ComponentRender.h"

class Transform;
class BoxCollider;


class ColliderRender :
	public ComponentRender
{
public:
	ColliderRender();
	~ColliderRender() override;

	void initComponent() override;

	void render() const override;

private:
	Transform* myTransform;
	BoxCollider* myBoxCollider;
};
