#include "my_lib/LowRenderer/Mesh.h"

Mesh::Mesh()
{}

Mesh::Mesh(const std::string& vertexShader, const std::string& fragmentShader, const std::string& name, const std::string& object3D, ResourcesManager& resources, const std::string& textureFile, const float& mipmapScale)
{
    std::cout << std::endl;
    Loading::Print(Huge, " Creation of the " +  name + " Started ! " );

    int width, height, nrChannels;

    if (textureFile != "")
    { 
        int checkIndex = resources.CheckTexture(textureFile);
        if ( checkIndex != -1 )
        {
            texture = resources.textures[checkIndex];
        }
        
        else
        {
            texture = Texture(textureFile, &width, &height, &nrChannels);
            resources.textures.push_back(texture);
        }
    }

    int checkIndex2 = resources.CheckModel(object3D);

    if ( checkIndex2 != -1 )
    {
        model = resources.models[checkIndex2];
        for (unsigned int i = 0; i < model.uvs.size(); i++)
        {
            model.uvs[i] = model.uvs[i] * mipmapScale;
        }
    }
    
    else
    {
        model = Model(object3D);
        resources.models.push_back(model);
        for (unsigned int i = 0; i < model.uvs.size(); i++)
        {
            model.uvs[i] = model.uvs[i] * mipmapScale;
        }
        checkIndex2 = resources.models.size() - 1;
    }
    
    Shader(vertexShader, fragmentShader, &resources);
    shader.ID = resources.shaders[resources.shaders.size()-1];

    color = {255,255,255,255};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    if (textureFile != "")
    {
        glGenBuffers(1, &texBuffer);
    }

    glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //glBufferData(GL_ARRAY_BUFFER, resources.models[checkIndex2].vertices.size() * sizeof(Vec3), &resources.models[checkIndex2].vertices[0], GL_STATIC_DRAW);
        glBufferData(GL_ARRAY_BUFFER, model.vertices.size() * sizeof(Vec3), &model.vertices[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3 , GL_FLOAT, GL_FALSE, 0, (void*) 0);
        glEnableVertexAttribArray(0);

        if (textureFile != "")
        {
            glBindBuffer(GL_ARRAY_BUFFER, texBuffer);
            //glBufferData(GL_ARRAY_BUFFER, resources.models[checkIndex2].uvs.size() * sizeof(Vec2), &resources.models[checkIndex2].uvs[0], GL_STATIC_DRAW);
            glBufferData(GL_ARRAY_BUFFER, model.uvs.size() * sizeof(Vec2), &model.uvs[0], GL_STATIC_DRAW);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glEnableVertexAttribArray(1);
        }

    glBindVertexArray(0);

    Loading::Print(Huge, " Creation of the " + name + " to complete ! ");
    std::cout << std::endl;
}

void Mesh::Draw(const Mat4& MVPMatrix)
{
    shader.Use();
    GLint transformLoc = glGetUniformLocation(shader.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &MVPMatrix.matrix[0]);

    //color = ColorEffect(color);
    color = ColorConverter(color);
    shader.SetVec4("ourColor", color);
    color = ColorConverter(color);

    glBindTexture(GL_TEXTURE_2D, texture.index);

    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, model.vertexIndices.size());

    glBindVertexArray(0);
}

Mesh::~Mesh()
{}