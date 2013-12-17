/**
 * 3D imported model, loaded from disk
 *
 * @author Dan Lapp
 * @version 1.0
 * @since 2013-12-10
**/
#pragma once
#include <string>
#include <stdio.h>
#include <io.h>
#include <Windows.h>
#include <array>
#include <vector>
#include "GL/glut.h"
#include "Array3.h"

class Model {
public:
    static const int debug_mode = 0;

    Model();
    Model(std::string, std::string);
    ~Model();

    void draw();

	void loadObject(char* model, char* texture);

private:
    
    void calculateNormals();
    int load3DS(char*);
    int loadTextureBitmap(char*);

    int textureID, listID;
    std::vector<Array3*> verticies;
    std::vector<Array3*> normals;
    std::vector<std::array<unsigned short, 3>> polygons;
    std::vector<std::array<float, 2>> mapCoords;
};