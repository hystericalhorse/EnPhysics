#include "Input.h"

Input::Input()
{
	int numKeys;
	// get pointer to sdl keyboard states and number of keys
	m_keyboardState = SDL_GetKeyboardState(&numKeys);

	// resize of keyboard state using numKeys for size
	m_keyboard.resize(numKeys);

	// copy the sdl key states to keyboard state
	std::copy(m_keyboardState, m_keyboardState + numKeys, m_keyboard.begin());

	// set previous keyboard state to current keyboard state
	m_prevKeyboard = m_keyboard;
}

Input::~Input()
{
	//
}

void Input::Update()
{
	// save previous keyboard state
	m_prevKeyboard = m_keyboard;

	// get current keyboard state
	std::copy(m_keyboardState, m_keyboardState + m_keyboard.size(), m_keyboard.begin());

	// mouse
	m_prevMouseButton = m_mouseButton;
	int x, y;
	uint32_t buttons = SDL_GetMouseState(&x, &y);
	m_mousePosition = { x , y };
	m_mouseButton[0] = buttons & SDL_BUTTON_LMASK; // left button [0001] & [0RML]
	m_mouseButton[1] = buttons & SDL_BUTTON_RMASK; // right button [0100] & [0RML]
	m_mouseButton[2] = buttons & SDL_BUTTON_MMASK; // middle button [0010] & [0RML]
}

bool Input::GetKey(uint8_t key)
{
	return m_keyboard[key];
}

bool Input::GetKeyDown(uint8_t key)
{
	return m_keyboard[key] && !m_prevKeyboard[key];
}

bool Input::GetKeyUp(uint8_t key)
{
	return !m_keyboard[key] && m_prevKeyboard[key];
}

bool Input::GetMouseButton(uint8_t button)
{
	return m_mouseButton[button];
}

bool Input::GetMouseButtonDown(uint8_t button)
{
	return m_mouseButton[button] && !m_prevMouseButton[button];
}

bool Input::GetMouseButtonUp(uint8_t button)
{
	return !m_mouseButton[button] && m_prevMouseButton[button];
}

const uint8_t key_space = SDL_SCANCODE_SPACE;
const uint8_t key_up = SDL_SCANCODE_UP;
const uint8_t key_down = SDL_SCANCODE_DOWN;
const uint8_t key_left = SDL_SCANCODE_LEFT;
const uint8_t key_right = SDL_SCANCODE_RIGHT;
const uint8_t key_escape = SDL_SCANCODE_ESCAPE;

const uint8_t btn_left = 0;
const uint8_t btn_middle = 1;
const uint8_t btn_right = 2;