#pragma once
#include "Test.h"

class CollisionTest : public Test
{
public:

	void Initialize() override;

	void Update() override;
	virtual void Render() override;
	virtual void FixedUpdate() override;
};