#include "InputManager.h"
#include "DProps.h"

namespace DEngine {


	InputManager::InputManager() : m_mouseCords(DEngine::width / 2, DEngine::height / 2),
		m_prevMouseCords(DEngine::width / 2, DEngine::height / 2)
	{
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::update() {
		for (auto& it : m_keyMap) {
			m_prevKeyMap[it.first] = it.second;
		}
		m_prevMouseCords = m_mouseCords;
	}

	void InputManager::pressKey(int keyID) {
		m_keyMap[keyID] = true;
	}

	void InputManager::releaseKey(int keyID) {
		m_keyMap[keyID] = false;
	}

	void InputManager::setMouseCords(double x, double y) {
		m_mouseCords.x = x;
		m_mouseCords.y = y;
	}

	bool InputManager::isKeyDown(int keyID) {
		auto it = m_keyMap.find(keyID);
		if (it != m_keyMap.end()) {
			return it->second;
		}
		return false;
	}

	bool InputManager::isKeyPressed(int keyID) {
		if (m_keyMap[keyID] == true && wasKeyDown(keyID) == false) {
			return true;
		}
		return false;
	}

	bool InputManager::wasKeyDown(int keyID)
	{
		auto it = m_prevKeyMap.find(keyID);
		if (it != m_prevKeyMap.end()) {
			return it->second;
		}
		return false;
	}

} //namespace