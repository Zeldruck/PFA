#include "my_lib/Ressources/shader.h"

Shader::Shader()
{}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath, ResourcesManager* resources)
{
    Loading::Print(Large, " Shader creation started ! ");
    std::string vertexCode;
    std::string fragmentCode;

    Loading::Print(Small, "Loading function ...     ");
    std::ifstream vs = resources->Load(vertexPath);
    std::ifstream fs = resources->Load(fragmentPath);

    Loading::Print(Small, "Error checking ...       ");
    if(!vs)
        Log::PrintError(Low, "opening of the file vs", "Error the file is missing !");
    if(!fs)
        Log::PrintError(Low, "opening of the file fs", "Error the file is missing !");
    
    std::string line;
    std::string srcCodeVs;
    std::string srcCodeFs;

    Loading::Print(Small, "Reading the file ...     ");
    
    while(getline(vs, line))
    {
       srcCodeVs += line + '\n';
    }

    while(getline(fs, line))
    {
        srcCodeFs += line + '\n';
    }

    Loading::Print(Small, "Converting to c_str ...  ");
    const char* vShaderCode = srcCodeVs.c_str();
    const char* fShaderCode = srcCodeFs.c_str();

    unsigned int vertex, fragment;

    Loading::Print(Small, "Compiling VS ...         ");
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    Loading::Print(Small, "Compiling FS ...         ");
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    Loading::Print(Small, "Create the program ...   ");
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    Loading::Print(Small, "Deletion ...             ");
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    Loading::Print(Large, " Compilation of shaders complete ! ");
    
    resources->shaders.push_back(ID);
}

void Shader::Use() 
{ 
    glUseProgram(ID); 
}

void Shader::SetBool(const std::string& name, const bool& value) const
{         
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}

void Shader::SetInt(const std::string& name, const int& value) const
{ 
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::SetFloat(const std::string& name, const float& value) const
{ 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::SetVec4(const std::string &name, const Vec4& value) const
{ 
    glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y , value.z , value.w); 
}