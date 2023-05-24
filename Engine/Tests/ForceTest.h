#pragma once

#include "Test.h"

class ForceTest : public Test
{
	void Initialize() override;

	void Update() override;
	virtual void Render() override;
	virtual void FixedUpdate() override;
};