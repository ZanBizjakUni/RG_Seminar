#pragma once
#include <unordered_map>

#include <glm\glm.hpp>
namespace DEngine {

	///class InputManager
	/*
	* class that manages the input of the user
	*/
	class InputManager
	{
	public:
		InputManager();
		~InputManager();
		///void update();
		/*
		* updates the current states of key presses
		*/
		void update();

		///pressKey(int keyID)
		/*
		* sets the state m_keyMap with key keyID to true
		*/
		void pressKey(int keyID);

		///releaseKey(int keyID)
		/*
		* sets the state m_keyMap with key keyID to false
		*/
		void releaseKey(int keyID);
		void setMouseCords(double x, double y);
		bool isKeyDown(int keyID);
		bool isKeyPressed(int keyID);
		glm::vec2 getMouseCords() { return m_mouseCords; }
		glm::vec2 getCordsOffset() { return glm::vec2(m_mouseCords.x - m_prevMouseCords.x, m_prevMouseCords.y - m_mouseCords.y); }
		void setNewWH(int height, int width);
	private:
		bool wasKeyDown(int keyID);

		std::unordered_map<int, bool> m_keyMap;
		std::unordered_map<int, bool> m_prevKeyMap;

		glm::vec2 m_mouseCords;
		glm::vec2 m_prevMouseCords;
	};

} //namespace