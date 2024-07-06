#include "my_lib/Ressources/Model.h"

Model::Model()
{}

Model::Model(const std::string& path_)
{
    Loading::Print(Large, " Creation of the Model Started ! ");
    filepath = path_;
    std::vector<Vec3> tempVertices, tempNormals;
    std::vector<Vec2> tempUvs;

    Loading::Print(Small, "Open the file ... ");
    FILE * file = fopen(path_.c_str(), "r");
    if( file == NULL )
    {
        Log::PrintError(Medium,"fopen()","Impossible to open the file !\n");
    }

    Loading::Print(Small, "Read the file ... ");

    while (true)
    {
        char lineHeader[50000];
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break;

        if ( strcmp( lineHeader , "v" ) == 0)
        {
            Vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            tempVertices.push_back(vertex);
        }

        else if ( strcmp( lineHeader , "vt") == 0)
        {
            Vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y );
            tempUvs.push_back(uv);
        }

        else if ( strcmp( lineHeader , "vn") == 0)
        {
            Vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            tempNormals.push_back(normal);
        }

        else if ( strcmp( lineHeader , "f") == 0)
        {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3] );
            
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices    .push_back(uvIndex[0]);
            uvIndices    .push_back(uvIndex[1]);
            uvIndices    .push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);

            if (matches == 12)
            {
                vertexIndices.push_back(vertexIndex[2]);
                vertexIndices.push_back(vertexIndex[3]);
                vertexIndices.push_back(vertexIndex[0]);
                uvIndices    .push_back(uvIndex[2]);
                uvIndices    .push_back(uvIndex[3]);
                uvIndices    .push_back(uvIndex[0]);
                normalIndices.push_back(normalIndex[2]);
                normalIndices.push_back(normalIndex[3]);
                normalIndices.push_back(normalIndex[0]);
            }
            
        }
    }

    Loading::Print(Small, "Load Vertices ... ");
    for (unsigned int i = 0; i < vertexIndices.size(); i++)
    {
        unsigned int vertexIndex = vertexIndices[i];
        Vec3 vertex = tempVertices[vertexIndex-1];
        vertices.push_back(vertex);
    }

    Loading::Print(Small, "Load UV coordinates ... ");
    for (unsigned int i = 0; i < uvIndices.size(); i++)
    {
        unsigned int uvIndex = uvIndices[i];
        Vec2 uv = tempUvs[uvIndex-1];
        uvs.push_back(uv);
    }

    Loading::Print(Small, "Load normals ... ");
    for (unsigned int i = 0; i < normalIndices.size(); i++)
    {
        unsigned int normalIndex = normalIndices[i];
        Vec3 normal = tempNormals[normalIndex-1];
        normals.push_back(normal);
    }

    Loading::Print(Large, " Creation of the Model completed ! ");
}