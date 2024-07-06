#include "my_lib/Ressources/Scene.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using namespace rapidxml;
using namespace std;

template<typename T>
void LoadObject(const std::string& filePath, GameObject<T>* world, ResourcesManager& resources)
{
    xml_document<> doc;

    ifstream theFile = resources.Load(filePath.c_str());
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');

    if (!theFile)
    {
        Log::PrintError(Low, "scene constructor ", "can't open the file");
    }
    

	doc.parse<0>(&buffer[0]); 

    GameObject<T>* childPtr = world; 

	for (rapidxml::xml_node<>* node = doc.first_node("WORLD")->first_node("REF"); node != nullptr; node = node->first_node())
    {
        for (rapidxml::xml_node<>* node2 = node; node2 != nullptr; node2 = node2->next_sibling())
        {

            GameObject<T>* temp = new GameObject<T>(Vec3(static_cast<float>(atof(node2->first_attribute("x")->value())),
                                                    static_cast<float>(atof(node2->first_attribute("y")->value())),
                                                    static_cast<float>(atof(node2->first_attribute("z")->value()))),
                                                Vec3(static_cast<float>(atof(node2->first_attribute("rotX")->value())),
                                                    static_cast<float>(atof(node2->first_attribute("rotY")->value())),
                                                    static_cast<float>(atof(node2->first_attribute("rotZ")->value()))),
                                                Vec3(static_cast<float>(atof(node2->first_attribute("scaleX")->value())),
                                                    static_cast<float>(atof(node2->first_attribute("scaleY")->value())),
                                                    static_cast<float>(atof(node2->first_attribute("scaleZ")->value()))),
                                                    node2->first_attribute("name")->value());
            
            Mesh* temp2 = new Mesh(node2->first_attribute("vertexShader")->value(),
                                                        node2->first_attribute("fragmentShader")->value(),
                                                        node2->first_attribute("name")->value(),
                                                        node2->first_attribute("object3D")->value(),
                                                        resources,
                                                        node2->first_attribute("textureFile")->value(),
                                                        static_cast<float>(atof(node2->first_attribute("mipmapScale")->value())));

            temp->mesh                  = *temp2;
            temp->activeInHierarchy     = true;
            temp->printable             = true;
            childPtr->children.emplace_back(temp);
        }
        childPtr = childPtr->children[0];
    }
}

template<typename T>
void LoadObjectWithTag(const std::string& filePath, GameObject<T>* world, ResourcesManager& resources, const std::string& _tag)
{
    xml_document<> doc;

    ifstream theFile = resources.Load(filePath.c_str());
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');

    if (!theFile)
    {
        Log::PrintError(Low, "scene constructor ", "can't open the file");
    }
    

	doc.parse<0>(&buffer[0]); 

    GameObject<T>* childPtr = world; 

	for (rapidxml::xml_node<>* node = doc.first_node("WORLD")->first_node("REF"); node != nullptr; node = node->first_node())
    {
        for (rapidxml::xml_node<>* node2 = node; node2 != nullptr; node2 = node2->next_sibling())
        {
            GameObject<T>* temp = new GameObject<T>(Vec3(static_cast<float>(atof(node2->first_attribute("x")->value())),
                                                    static_cast<float>(atof(node2->first_attribute("y")->value())),
                                                    static_cast<float>(atof(node2->first_attribute("z")->value()))),
                                                Vec3(static_cast<float>(atof(node2->first_attribute("rotX")->value())),
                                                    static_cast<float>(atof(node2->first_attribute("rotY")->value())),
                                                    static_cast<float>(atof(node2->first_attribute("rotZ")->value()))),
                                                Vec3(static_cast<float>(atof(node2->first_attribute("scaleX")->value())),
                                                    static_cast<float>(atof(node2->first_attribute("scaleY")->value())),
                                                    static_cast<float>(atof(node2->first_attribute("scaleZ")->value()))),
                                                    node2->first_attribute("name")->value(),
                                                    _tag);
            
            Mesh* temp2 = new Mesh(node2->first_attribute("vertexShader")->value(),
                                                        node2->first_attribute("fragmentShader")->value(),
                                                        node2->first_attribute("name")->value(),
                                                        node2->first_attribute("object3D")->value(),
                                                        resources,
                                                        node2->first_attribute("textureFile")->value(),
                                                        static_cast<float>(atof(node2->first_attribute("mipmapScale")->value())));

            temp->mesh                  = *temp2;
            temp->activeInHierarchy     = true;
            temp->printable             = true;
            childPtr->children.emplace_back(temp);
        }
        childPtr = childPtr->children[0];
    }
}

void LoadMap(const std::string& filePath, GameObject<OrientedBox>* world, ResourcesManager& resources, const std::string& _tag, float widthW, float heightW, GLFWwindow* window)
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

    xml_document<> doc;

    ifstream theFile = resources.Load(filePath.c_str());
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');

    if (!theFile)
    {
        Log::PrintError(Low, "scene constructor ", "can't open the file");
    }
    

	doc.parse<0>(&buffer[0]); 

    GameObject<OrientedBox>* childPtr = world;
    std::vector<GameObject<OrientedBox>*> mapList;


	for (rapidxml::xml_node<>* node = doc.first_node("WORLD")->first_node("REF"); node != nullptr; node = node->first_node())
    {
        for (rapidxml::xml_node<>* node2 = node; node2 != nullptr; node2 = node2->next_sibling())
        {

            GameObject<OrientedBox>* temp = new GameObject<OrientedBox>(Vec3(static_cast<float>(atof(node2->first_attribute("x")->value())),
                                                    static_cast<float>(atof(node2->first_attribute("y")->value())),
                                                    static_cast<float>(atof(node2->first_attribute("z")->value()))) * 5,
                                                Vec3(static_cast<float>(atof(node2->first_attribute("rotX")->value())),
                                                    static_cast<float>(atof(node2->first_attribute("rotY")->value())),
                                                    static_cast<float>(atof(node2->first_attribute("rotZ")->value()))),
                                                Vec3(static_cast<float>(atof(node2->first_attribute("scaleX")->value())),
                                                    static_cast<float>(atof(node2->first_attribute("scaleY")->value())),
                                                    static_cast<float>(atof(node2->first_attribute("scaleZ")->value()))),
                                                    node2->first_attribute("name")->value(),
                                                    _tag);
            
            ImGui_ImplOpenGL3_NewFrame();
		    ImGui_ImplGlfw_NewFrame();
		    ImGui::NewFrame();
            {
                ImGui::SetNextWindowPos(ImVec2(widthW / 2 - 150, heightW / 2 - 100), ImGuiCond_Once);
                ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_Once);

                ImGui::Begin("loading", &p_open, window_flags);

                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();

                ImGui::Text(" ");
                ImGui::SameLine(150 - ImGui::GetFontSize() * 4);
                ImGui::Text("FPS Game");

                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();

                ImGui::Text(" ");
                ImGui::SameLine(25);
                ImGui::Text("Now Loading:");

                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();

                ImGui::Text(" ");
                ImGui::SameLine(25);
                ImGui::Text(temp->name.c_str());
                ImGui::End();
            }

            ImGui::Render();
		    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glfwSwapBuffers(window);
            glfwPollEvents();
            glGetError();

            Mesh* temp2 = new Mesh(node2->first_attribute("vertexShader")->value(),
                                                        node2->first_attribute("fragmentShader")->value(),
                                                        node2->first_attribute("name")->value(),
                                                        node2->first_attribute("object3D")->value(),
                                                        resources,
                                                        node2->first_attribute("textureFile")->value(),
                                                        static_cast<float>(atof(node2->first_attribute("mipmapScale")->value())));

            temp->mesh                  = *temp2;
            temp->activeInHierarchy     = true;
            temp->printable             = true;
            childPtr->children.emplace_back(temp);
            mapList.push_back(temp);
        }
        childPtr = childPtr->children[0];
    }

    GameObject<OrientedBox>::LoadMap(mapList);
    GameObject<Sphere>::LoadMap(mapList);
}