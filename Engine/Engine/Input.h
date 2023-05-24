#pragma once
#include <SDL.h>
#include <glm.hpp>
#include <vector>
#include <array>

class Input
{
public:

	Input();
	~Input();

	void Update();

	// keyboard
	bool GetKey(uint8_t key);
	bool GetKeyDown(uint8_t key);
	bool GetKeyUp(uint8_t key);

	// mouse
	const glm::vec2& GetMousePosition() const { return m_mousePosition; }
	bool GetMouseButton(uint8_t key);
	bool GetMouseButtonDown(uint8_t key);
	bool GetMouseButtonUp(uint8_t key);

private:
	// keyboard
	const uint8_t* m_keyboardState;
	std::vector<uint8_t> m_keyboard;
	std::vector<uint8_t> m_prevKeyboard;

	// mouse
	glm::vec2 m_mousePosition;
	std::array<uint8_t, 3> m_mouseButton;
	std::array<uint8_t, 3> m_prevMouseButton;
};

extern const uint8_t key_space;
extern const uint8_t key_up;
extern const uint8_t key_down;
extern const uint8_t key_left;
extern const uint8_t key_right;
extern const uint8_t key_escape;

extern const uint8_t btn_left;
extern const uint8_t btn_right;
extern const uint8_t btn_middle;
