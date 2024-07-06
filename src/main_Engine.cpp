#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "my_lib/Ressources/stb_image.h"
#include "my_lib/LowRenderer/Mesh.h"
#include "my_lib/LowRenderer/Camera.h"
#include "my_lib/Ressources/Scene.h"
#include "my_lib/Core/DataStructure/GameObject.hpp"
#include "my_lib/Weapon.hpp"
#include "my_lib/Enemies.hpp"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

void window_size_callback(GLFWwindow* window, int width, int height);

void ProcessInput(GLFWwindow *window);

void MouseCallback(GLFWwindow *window, Camera* cam);

void EnnemyWaveSpawn(ResourcesManager& resources, std::vector<Enemy*>& enemyList, const std::vector<Vec3>& enemySpawnPoints, int& enemyToSpawn, float& timeToSpawn);

void Menu(GLFWwindow* window);

void Game(GLFWwindow* window);

Vec4 ColorEffect(Vec4 color)
{
    int x = 2;

	if (color.x >= 255 && color.z <= 1 && color.y < 255)
		color.y += x;

	else if (color.y >= 255 && color.x > 1)
		color.x -= x;

	else if (color.y >= 255 && color.x <= 1 && color.z < 255)
		color.z += x;

	else if (color.z >= 255 && color.y > 1)
        color.y -= x;

	else if (color.z >= 255 && color.y <= 1 && color.x < 255)
		color.x += x;

	else if (color.x >= 255)
		color.z -= x;

    return color;
}

Vec4 ColorConverter(Vec4 color)
{
    if (color.x <= 1 && color.y <= 1 && color.z <= 1)
    {
        color.x *= 255;
        color.y *= 255;
        color.z *= 255;
    }

    else
    {
        color.x /= 255;
        color.y /= 255;
        color.z /= 255;
    }
    
    return color;
}

void ImgUiSpacing(int nb)
{
    for (int i = 0; i < nb; i++)
        ImGui::Spacing();
}

int widthW, heightW;

bool menu = true;
bool quit = false;

float currentFrame = glfwGetTime();
float lastFrame = currentFrame;
float deltaTime;

int main(int argc, char** argv)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE); 

    widthW = 1280;
    heightW = 720;

    GLFWwindow* window = glfwCreateWindow(widthW, heightW, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        Log::PrintError(High, "GLFW_WINDOW()", "Failed to create GLFW window");
    } 

    glfwMaximizeWindow(window);
    glfwGetWindowSize(window, &widthW, &heightW);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Log::PrintError(High, "GLAD", "Failed to initialize GLAD");
    }
    
    glViewport(0, 0, widthW, heightW);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    while (!quit)
    {
        if (menu)
            Menu(window);
        else 
            Game(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();



    glfwTerminate();
    return 0;
}

void Menu(GLFWwindow* window)
{
    bool no_titlebar = true;
    bool no_scrollbar = true;
    bool no_menu = true;
    bool no_move = true;
    bool no_resize = true;
    bool no_collapse = true;
    bool no_nav = true;
    bool no_background = false;
    bool no_bring_to_front = true;

    ImGuiWindowFlags window_flags = 0;
    if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
    if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	
	bool p_open = true;
    
    while(1)
    {
        ProcessInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
        {
            ImGui::SetNextWindowPos(ImVec2(widthW / 2 - 150, heightW / 2 - 100), ImGuiCond_Once);
            ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_Once);
        
            ImGui::Begin("Menu", &p_open, window_flags);

            ImgUiSpacing(3);

            ImGui::Text(" ");
            ImGui::SameLine(150 - ImGui::GetFontSize() * 2);
            ImGui::Text("FPS Game");

            ImgUiSpacing(3);

            ImGui::Text(" ");
            ImGui::SameLine(25);
            if (ImGui::Button("Start Game", ImVec2(250.f, 50.f)))
            {
                menu = false;
                ImGui::End();
                ImGui::Render();
		        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
                return;
            }

            ImgUiSpacing(3);

            ImGui::Text(" ");
            ImGui::SameLine(25);
            if (ImGui::Button("Quit", ImVec2(250.f, 50.f)))
            {
                quit = true;
                ImGui::End();
                ImGui::Render();
		        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
                return;
            }
            ImGui::End();
        }

        ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glfwSwapBuffers(window);
        glfwPollEvents();
        glGetError();
    }

    quit = true;
}

void Game(GLFWwindow* window)
{
    srand(time(NULL));
    std::vector<Enemy*> EnemyList;

    ResourcesManager resources;
    
    GameObject<Sphere> Gun(Vec3(-2,-2,1), Vec3(0,0,0), Vec3(1,1,1), "Handgun");
    Gun.mesh = Mesh("./ressources/Shaders/shader.vs", "./ressources/Shaders/shader.fs", "Handgun", "./ressources/Models/M24.obj", resources, "ressources/Textures/M24.jpg");
    Gun.activeInHierarchy = true;
    Gun.printable = true;

    GameObject<OrientedBox> world       = GameObject<OrientedBox>(Vec3(0,0,0), Vec3(0,0,0), Vec3(1,1,1), "World", "World");
    LoadMap("./ressources/Scenes/Map.XML", &world, resources, world.tag, widthW, heightW, window);
    Camera cam                          = Camera(Vec3(0,1020,0),500, 1000,0.005, 100, "Player", "Player");
    cam.activeInHierarchy               = true;
    cam.gravity                         = 1;

    cam.children.push_back(&Gun);

    EnemyList.push_back( new Enemy(resources, Vec3(0,1000,0), Vec3(1.5,1.5,1.5), 40, 500, 10, 1));
    EnemyList[0]->gravity                = 1;
    
    double  xPos,   yPos;

    glfwGetCursorPos(window, &xPos, &yPos);
    glfwSetCursorPos(window,widthW/2,heightW/2);
    cam.scWidth = widthW;
    cam.scHeight = heightW;
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Mat4 viewMat;
    Mat4 projectionMat;
    projectionMat = Perspective(60,cam.scWidth/cam.scHeight,0.1f,100000.0f);

    Weapon shoot(10, 300, 30.f, .1f, 1);
	
	bool no_titlebar = true;
    bool no_scrollbar = true;
    bool no_menu = true;
    bool no_move = true;
    bool no_resize = true;
    bool no_collapse = true;
    bool no_nav = true;
    bool no_background = false;
    bool no_bring_to_front = true;

    ImGuiWindowFlags window_flags = 0;
    if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
    if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	
	bool p_open = true;

    Bullet::enemyList = &EnemyList;

    float timeLW = 2.5f;

    /* Start Enemy Part */
    
    std::vector<Vec3> enemySpawnPoints;
    enemySpawnPoints.push_back(Vec3(0, 1000, 0));
    enemySpawnPoints.push_back(Vec3(5000, 1000, 5000));
    enemySpawnPoints.push_back(Vec3(-5000, 1000, -5000));

    float enemySpawnTime = 2.5f;
    int enemyToSpawn = 5;

    /* End Enemy Part */

    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        ProcessInput(window);
        MouseCallback(window,&cam);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (cam.HP <= 0)
        {
            ImGui::SetNextWindowPos(ImVec2(widthW / 2 - 250 , heightW / 2 - 125), ImGuiCond_Once);
            ImGui::SetNextWindowSize(ImVec2(500, 250), ImGuiCond_Once);
        
            ImGui::Begin("Lose", &p_open, window_flags);
            ImGui::SetWindowFontScale(2.f);

            for (int i = 0; i < 27; i++)
                ImGui::Spacing();

            ImGui::Text(" ");
            ImGui::SameLine(250 - ImGui::GetFontSize() * 3);
            ImGui::Text("You Lose !");
            ImGui::End();

            timeLW -= deltaTime;
            if (timeLW <= 0.f)
            {
                ImGui::Render();
		        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
                break;
            }
        }
        else if (EnemyList.size() == 0 && enemyToSpawn == 0)
        {
            ImGui::SetNextWindowPos(ImVec2(widthW / 2 - 250 , heightW / 2 - 125), ImGuiCond_Once);
            ImGui::SetNextWindowSize(ImVec2(500, 250), ImGuiCond_Once);
        
            ImGui::Begin("Win", &p_open, window_flags);
            ImGui::SetWindowFontScale(2.f);

            for (int i = 0; i < 27; i++)
                ImGui::Spacing();

            ImGui::Text(" ");
            ImGui::SameLine(250 - ImGui::GetFontSize() * 3);
            ImGui::Text("You Won !");
            ImGui::End();

            timeLW -= deltaTime;
            if (timeLW <= 0.f)
            {
                ImGui::Render();
		        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
                break;
            }
        }
        else 
        {
            GameObject<Sphere>::setTime(currentFrame, deltaTime);
            GameObject<OrientedBox>::setTime(currentFrame, deltaTime);
            
            /* Start Player ui */
            {
                ImGui::SetNextWindowPos(ImVec2(widthW / 50, heightW / 30), ImGuiCond_Once);
                ImGui::SetNextWindowSize(ImVec2(175, 100), ImGuiCond_Once);
            
                ImGui::Begin("PlayerStats", &p_open, window_flags);
                ImGui::Text("Player life : ");
                std::string hpString = std::to_string(cam.HP);
                std::string maxHpString = std::to_string(cam.MaxHP);
                ImGui::SameLine();
                ImGui::Text(hpString.c_str());
                ImGui::SameLine();
                ImGui::Text(" / ");
                ImGui::SameLine();
                ImGui::Text(maxHpString.c_str());
                
                ImGui::Text("Ammos : ");
                ImGui::SameLine();
                ImGui::Text(std::to_string(shoot.ammo).c_str());
                ImGui::SameLine();
                ImGui::Text(" / ");
                ImGui::SameLine();
                ImGui::Text(std::to_string(shoot.allAmmo).c_str());

                ImGui::Text("FPS : ");
                ImGui::SameLine();
                ImGui::Text(std::to_string(roundf(1/deltaTime)).c_str());
                ImGui::End();
            }
            /* End Player ui */

            cam.Update(window, deltaTime, EnemyList);

            /* Start ShootPart */
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !shoot.isShooting && shoot.ammo > 0)
            {
                shoot.Shoot(cam.transform.position, cam.transform.forward, resources);
                shoot.ammo--;
            }
            else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE && shoot.isShooting)
            {
                shoot.isShooting = false;
            }
            else if (shoot.ammo == 0)
            {
                ImGui::SetNextWindowPos(ImVec2(widthW / 2, heightW / 2), ImGuiCond_Once);
                ImGui::SetNextWindowSize(ImVec2(75, 25), ImGuiCond_Once);
            
                ImGui::Begin("Reloading", &p_open, window_flags);
                ImGui::Text("RELOADING");
                ImGui::End();

                if (shoot.reloadTime > 0)
                    shoot.reloadTime -= deltaTime;
                else if (shoot.allAmmo <= _AMMOMAGAZINE && shoot.allAmmo > 0)
                {
                    shoot.ammo = shoot.allAmmo;
                    shoot.allAmmo = 0;
                    shoot.reloadTime = _RELOADTIME;
                }
                else if (shoot.allAmmo > _AMMOMAGAZINE)
                {
                    shoot.ammo = _AMMOMAGAZINE;
                    shoot.allAmmo -= _AMMOMAGAZINE;
                    shoot.reloadTime = _RELOADTIME;
                }
            }

            if ( GameObject<Sphere>::animObject.size() > 0 )
            {
                for (unsigned int i = 0; i < GameObject<Sphere>::animObject.size(); i++)
                {                
                    if (GameObject<Sphere>::animObject[i]->cooldown - GameObject<Sphere>::time <= -1)
                    {
                        GameObject<Sphere>::animObject.erase(GameObject<Sphere>::animObject.begin() + i);
                        i--;
                    }
                    else
                        GameObject<Sphere>::animObject[i]->ChildrensProcess(viewMat,projectionMat);
                }
            }

            shoot.BulletsMove(viewMat, projectionMat, resources);
            /* End ShootPart */
        }

        viewMat = cam.CreateViewMatrix();
        world.ChildrensProcess(viewMat,projectionMat);
        cam.ChildrensProcess(viewMat,projectionMat);

        //EnnemyWaveSpawn(ResourcesManager& resources, std::vector<Enemy*>& enemyList, const std::vector<Vec3>& enemySpawnPoints, int& enemyToSpawn, float& timeToSpawn);
        EnnemyWaveSpawn(resources, EnemyList, enemySpawnPoints, enemyToSpawn, enemySpawnTime);
        
        for (unsigned int i = 0; i < EnemyList.size(); i++)
        {
            EnemyList[i]->MoveTowardTarget(cam.transform.position, deltaTime);
            EnemyList[i]->ChildrensProcess(viewMat, projectionMat);
            if (EnemyList[i]->HP <= 0)
            {
                EnemyList.erase(EnemyList.begin() + i);
                i--;
            }
        }

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glfwSwapBuffers(window);
        glfwPollEvents();
        glGetError();
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    menu = true;
}

void EnnemyWaveSpawn(ResourcesManager& resources, std::vector<Enemy*>& enemyList, const std::vector<Vec3>& enemySpawnPoints, int& enemyToSpawn, float& timeToSpawn)
{
    if (enemySpawnPoints.size() == 0)
    {
        std::cout << "Spawn points null, ennemies can't spawn !";
        return;
    }

    if (timeToSpawn > 0.f)
        timeToSpawn -= deltaTime;
    else if (enemyToSpawn > 0)
    {
        int spawnPoint = rand() % (enemySpawnPoints.size() - 1);
        enemyList.push_back( new Enemy(resources, enemySpawnPoints[spawnPoint], Vec3(1.5,1.5,1.5), 40, 500, 10, 1));
        enemyList[enemyList.size() - 1]->gravity = 1;
        enemyToSpawn--;
        timeToSpawn = 2.5f;
    }
}

void MouseCallback(GLFWwindow *window, Camera* cam)
{
    double xRelpos = cam->xMousePos;
    double yRelpos = cam->yMousePos;
    glfwGetCursorPos(window, &cam->xMousePos, &cam->yMousePos);
    double xoffset = cam->xMousePos - xRelpos;
    double yoffset = cam->yMousePos - yRelpos;
    cam->Rotate(xoffset,yoffset); 
}

void ProcessInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
