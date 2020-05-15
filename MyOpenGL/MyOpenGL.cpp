// MyOpenGL.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "GLWindow.h"
#include "Viewer.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "RenderState.h"
#include "Texture2D.h"

#include <iostream>
#include <ctime>
#include <cstdlib>

const int SCR_WIDTH = 1280;
const int SCR_HEIGHT = 720;


int main()
{
    GLWindow window(SCR_WIDTH, SCR_HEIGHT);
    if (!window.IsActive())
        return -1;

    Viewer viewer(&window);

    //创建渲染状态
    ShaderProgram shader_program(ShaderProgram::DefaultVertexShader, ShaderProgram::DefaultFragmentShader);
    ShaderProgram shader_program_instanced(ShaderProgram::InstancedVertexShader, ShaderProgram::DefaultFragmentShader);
    Image image("../resources/texture/container2.png");
    Image image2("../resources/texture/container2_specular.png");
    Texture2D texture(&image);
    Texture2D texture2(&image2);

    RenderState state;
    state.SetShaderProgram(&shader_program);
    state.SetDiffuseTexture(&texture);
    state.SetSpecularTexture(&texture2);

    RenderState state2;
    state2.SetShaderProgram(&shader_program_instanced);
    state2.SetDiffuseTexture(&texture);
    state2.SetSpecularTexture(&texture2);


    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

    std::vector<Vertex> vertex_vec;
    for (int i = 0;i < 36 * 8;i += 8)
    {
        Vertex ver;
        ver.Postion = Vector3f(vertices[i], vertices[i + 1], vertices[i + 2]);
        ver.Normal = Vector3f(vertices[i + 3], vertices[i + 4], vertices[i + 5]);
        ver.Texcoord = Vector2f(vertices[i + 6], vertices[i + 7]);
        vertex_vec.emplace_back(ver);
    }

    unsigned int indices[] = {
        0,1,2,3,4,5,
        6,7,8,9,10,11,
        12,13,14,15,16,17,
        18,19,20,21,22,23,
        24,25,26,27,28,29,
        30,31,32,33,34,35
    };

    std::vector<unsigned int> indice_vec;
    for (int i = 0;i < 36;++i)
    {
        indice_vec.emplace_back(indices[i]);
    }

#if 0
    std::vector<Mesh*> meshes;
    srand((int)time(0));
    for (int i = 0;i < 10000;++i)
    {
        float random1 = (float)(rand() % 100);
        float random2 = (float)(rand() % 100);
        float random3 = (float)(rand() % 100);
        Matrix4x4f model = Matrix4x4f::Translate(random1, random2, random3);
        Mesh* mesh = new Mesh(vertex_vec, indice_vec);
        mesh->SetState(&state);
        mesh->SetModelMatrix(model);
        meshes.emplace_back(mesh);
    }
#else
    std::vector<Mesh*> meshes;
    std::vector<Vector3f> veces;
    srand((int)time(0));
    for (int i = 0;i < 10000;++i)
    {
        float random1 = (float)(rand() % 100);
        float random2 = (float)(rand() % 100);
        float random3 = (float)(rand() % 100);
        veces.emplace_back(Vector3f(random1, random2, random3));
    }
    Mesh* mesh = new Mesh(vertex_vec, indice_vec, veces);
    mesh->SetState(&state2);
    meshes.emplace_back(mesh);
#endif

    viewer.RenderScene(meshes);

    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
