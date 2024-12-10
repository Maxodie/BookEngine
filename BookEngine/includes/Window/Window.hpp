#pragma once
#include "Window/Inputs.hpp"

namespace Book
{
    struct AppWindow
    {
        BOOK_INLINE AppWindow(EventDispatcher* dispatcher, int32_t width, int32_t height,
                              const char* title) : m_Dispatcher(dispatcher)
        {
            BOOK_CORE_INFO("GLFW window creation started ...");
            if(glfwInit() != GLFW_TRUE)
            {
                BOOK_CORE_FATAL("glfwInit() failed!");
                exit(EXIT_FAILURE);
            }

            glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_TRUE);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

            auto display { glfwGetVideoMode(glfwGetPrimaryMonitor()) };
            glfwWindowHint(GLFW_REFRESH_RATE, display->refreshRate);
            glfwWindowHint(GLFW_GREEN_BITS, display->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, display->blueBits);
            glfwWindowHint(GLFW_RED_BITS, display->redBits);
            glfwWindowHint(GLFW_SAMPLES, 4);

            glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

            m_Handle = glfwCreateWindow(width, height, title, NULL, NULL);
            if(!m_Handle)
            {
                BOOK_CORE_FATAL("Failed to initialize app-window!");
                exit(EXIT_FAILURE);
            }

            // set user data
            glfwSetWindowUserPointer(m_Handle, this);

            // binding callbacksA
            glfwSetWindowMaximizeCallback(m_Handle, OnMaximize);
            glfwSetFramebufferSizeCallback(m_Handle, OnResize);
            glfwSetWindowIconifyCallback(m_Handle, OnIconify);
            glfwSetMouseButtonCallback(m_Handle, OnMouse);
            glfwSetWindowCloseCallback(m_Handle, OnClose);
            glfwSetCursorPosCallback(m_Handle, OnMotion);
            glfwSetScrollCallback(m_Handle, OnWheel);
            glfwSetKeyCallback(m_Handle, OnKey);
            glfwSetErrorCallback(OnError);

            // create opengl context
            glfwMakeContextCurrent(m_Handle);

            // buffer swap interval
            glfwSwapInterval(1);

            BOOK_CORE_INFO("GLFW window successfully created");
        }

        BOOK_INLINE ~AppWindow()
        {
            glfwDestroyWindow(m_Handle);
            glfwTerminate();
        }

        BOOK_INLINE GLFWwindow* Handle()
        {
            return m_Handle;
        }

        BOOK_INLINE bool PollEvents()
        {
            glfwPollEvents();
            m_Dispatcher->PollEvents();
            glfwSwapBuffers(m_Handle);
            return (!glfwWindowShouldClose(m_Handle));
        }

        BOOK_INLINE bool IsKey(int32_t key)
        {
            if(key >= 0 && key <= GLFW_KEY_LAST)
            {
                return m_Inputs.Keys.test(key);
            }

            return false;
        }

        BOOK_INLINE bool IsMouse(int32_t button)
        {
            if(button >= 0 && button <= GLFW_MOUSE_BUTTON_LAST)
            {
                return m_Inputs.Mouse.test(button);
            }

            return false;
        }

        BOOK_INLINE static AppWindow* GetUserData(GLFWwindow* window)
        {
            return static_cast<AppWindow*>(glfwGetWindowUserPointer(window));
        }

        BOOK_INLINE static void OnKey(GLFWwindow* window, int32_t key,
                                      int32_t scancode, int32_t action, int32_t mods)
        {
            AppWindow* appWindow = GetUserData(window);

            if(key >= 0 && key <= GLFW_KEY_LAST)
            {
                switch(action)
                {
                    case GLFW_RELEASE:
                        appWindow->m_Dispatcher->PostEvent<KeyReleaseEvent>(key);
                        appWindow->m_Inputs.Keys.reset(key);
                    break;
                    case GLFW_PRESS:
                        appWindow->m_Dispatcher->PostEvent<KeyPressedEvent>(key);
                        appWindow->m_Inputs.Keys.set(key);
                    break;
                    case GLFW_REPEAT:
                    appWindow->m_Dispatcher->PostEvent<KeyRepeatEvent>(key);
                        appWindow->m_Inputs.Keys.set(key);
                    break;
                }
                return;
            }
            BOOK_CORE_ERROR("Invalid key code detected: [{}]", key);
        }

        BOOK_INLINE static void OnMouse(GLFWwindow* window, int32_t button,
                                        int32_t action, int32_t mods)
        {
            AppWindow* appWindow = GetUserData(window);

            if(button >= 0 && button <= GLFW_MOUSE_BUTTON_LAST)
            {
                switch (action)
                {
                    case GLFW_PRESS:
                        appWindow->m_Dispatcher->PostEvent<MouseDownEvent>(button);
                        appWindow->m_Inputs.Mouse.set(button);
                    case GLFW_RELEASE:
                        appWindow->m_Dispatcher->PostEvent<MouseReleaseEvent>(button);
                        appWindow->m_Inputs.Mouse.reset(button);
                    break;
                }
                return;
            }
            BOOK_CORE_ERROR("Invalid key code detected: [{}]", button);
        }

        BOOK_INLINE static void OnResize(GLFWwindow* window, int32_t width, int32_t height)
        {
            GetUserData(window)->m_Dispatcher->PostEvent<WindowResizeEvent>(width, height);
        }

        BOOK_INLINE static void OnMotion(GLFWwindow* window, double x, double y)
        {
            AppWindow* appWindow = GetUserData(window);
            appWindow->m_Dispatcher->PostEvent<MouseMotionEvent>(x, y);

            if(appWindow->m_Inputs.Mouse.test(GLFW_MOUSE_BUTTON_LEFT))
            {
                appWindow->m_Dispatcher->PostEvent<MouseDragEvent>(
                    (appWindow->m_Inputs.MouseX - x),
                    (appWindow->m_Inputs.MouseY - y)
                );
            }

            appWindow->m_Inputs.MouseX = x;
            appWindow->m_Inputs.MouseY = y;
        }

        BOOK_INLINE static void OnWheel(GLFWwindow* window, double x, double y)
        {
            GetUserData(window)->m_Dispatcher->PostEvent<MouseWheelEvent>(x, y);
        }

        BOOK_INLINE static void OnMaximize(GLFWwindow* window, int32_t action)
        {
            if(action)
            {
                GetUserData(window)->m_Dispatcher->PostEvent<WindowMaximizeEvent>();
            }
            else
            {
                GetUserData(window)->m_Dispatcher->PostEvent<WindowMaximizeEvent>();
            }
        }

        BOOK_INLINE static void OnIconify(GLFWwindow* window, int32_t action)
        {
            if(action)
            {
                GetUserData(window)->m_Dispatcher->PostEvent<WindowIconifyEvent>();
            }
            else
            {
                GetUserData(window)->m_Dispatcher->PostEvent<WindowIconifyEvent>();
            }
        }

        BOOK_INLINE static void OnError(int32_t code, const char* msg)
        {
            BOOK_CORE_ERROR("[GLFW]: [{}] {}", code, msg);
        }

        BOOK_INLINE static void OnClose(GLFWwindow* window)
        {
            GetUserData(window)->m_Dispatcher->PostEvent<WindowCloseEvent>();
        }

        private:
            EventDispatcher* m_Dispatcher;
            WindowInputs m_Inputs;
            GLFWwindow* m_Handle;
    };
}
