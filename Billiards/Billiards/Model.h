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
#include "Vector.h"
#include "glut.h"

class Model {
public:
    static const int debug_mode = 0;

    Model(void);
    Model(std::string, std::string);
    ~Model(void);

    void draw();
	void loadObject(char* model, char* texture);
    std::vector<Vector> getVerticies();

private:
    void calculateNormals();
    int load3DS(char*);
    int loadTextureBitmap(char*);

    int textureID, listID;
    std::vector<Vector> verticies;
    std::vector<Vector> normals;
    std::vector<std::array<unsigned short, 3>> polygons;
    std::vector<std::array<float, 2>> mapCoords;
};
