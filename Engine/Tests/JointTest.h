#pragma once

#include "Test.h"

class JointTest : public Test
{
	void Initialize() override;

	void Update() override;
	virtual void Render() override;
	virtual void FixedUpdate() override;

private:
	class Body* m_anchor{ nullptr };
};