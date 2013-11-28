#include <Core/Environment.h>
#include <States/MainState.h>
#include <States/GameState.h>
#include <Core/PlatformIncludes.h>
#include <iostream>

using namespace MLD;

void ErrorCallback(int Error, const char* Desc)
{
    printf("Error: %d; Desc: ", Error);
    printf(Desc);
    printf("\n");
}

int main()
{
    GLFWwindow* Window;
    glfwSetErrorCallback(ErrorCallback);

    if(!glfwInit())		//init and test glfw
        printf("Glfw is not happy\n");

    Window = glfwCreateWindow(1280, 720, "MiniLD45 : Low-level Jam", NULL, NULL);
    if (!Window)
    {
        glfwTerminate();
    }
    glfwMakeContextCurrent(Window);

    GLenum error = glewInit();
    if(error != GL_NO_ERROR)		//init and test glew
		printf("Glew is not happy\n");
    //timing
    float DeltaTime = 0.0f;
    float OldTime = glfwGetTime();
    int Fps = 0;
    float FpsTimer = 0.0f;
    //

    //Resolution
    int WinWidth, WinHeight;
    //

    //set up state manager
    Environ->Init(Window, new GameState());

    while(!glfwWindowShouldClose(Window))
    {
        DeltaTime = glfwGetTime() - OldTime;
        OldTime = glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwGetWindowSize(Window, &WinWidth, &WinHeight);
        glViewport(0,0, WinWidth, WinHeight);

        Environ->Update(DeltaTime);

        glfwSwapBuffers(Window);
        glfwPollEvents();

        Fps++;
        FpsTimer += DeltaTime;
        if(FpsTimer >= 1.0f)
        {
            printf("FPS: %d\n", Fps);
            Fps = 0;
            FpsTimer = 0.0f;
        }
    }
    glfwDestroyWindow(Window);

    glfwTerminate();

    return 0;
}
