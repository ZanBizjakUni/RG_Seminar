#pragma once
#include <unordered_map>
#include <glm\glm.hpp>
namespace PlayingGround {

	class InputManager
	{
	public:
		InputManager();
		~InputManager();
		void update();

		void pressKey(int keyID);
		void releaseKey(int keyID);
		void setMouseCords(double x, double y);
		bool isKeyDown(int keyID);
		bool isKeyPressed(int keyID);
		glm::vec2 getMouseCords() { return m_mouseCords; }
		glm::vec2 getCordsOffset() { return m_mouseCords - m_prevMouseCords; }
	private:

		bool wasKeyDown(int keyID);

		std::unordered_map<int, bool> m_keyMap;
		std::unordered_map<int, bool> m_prevKeyMap;

		glm::vec2 m_mouseCords;
		glm::vec2 m_prevMouseCords;

	};

} //namespace