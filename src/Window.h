#pragma once

#include "stdio.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Constant.h"
class Window
{
public:
	Window() = delete;
	Window(GLint windowWidth, GLint windowHeight);

	~Window();

	int Initialize();

	GLint getBufferWidth() const { return m_bufferWidth; }
	GLint getBufferHeight() const { return m_bufferHeight; }

	bool getShouldClose() const { return glfwWindowShouldClose(m_mainWindow); }

	bool* getsKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();

	void swapBuffers() { glfwSwapBuffers(m_mainWindow); }

	GLFWwindow* m_mainWindow;

private:

	GLint m_width, m_height;
	GLint m_bufferWidth, m_bufferHeight;

	bool keys[TOTAL_KEY];

	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;

	void createCallbacks();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};