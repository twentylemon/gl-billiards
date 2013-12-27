/**
 *	Model and texture loader for openGL.
 *	Modified code from Damiano Vitulli was used to construct
 *	this class
 *
 *	@author Dan Lapp
 *	@since 2013-12-10
 */


/*
 * ---------------- www.spacesimulator.net --------------
 *   ---- Space simulators and 3d engine tutorials ----
 *
 * Author: Damiano Vitulli
 *
 * This program is released under the BSD licence
 * By using this program you agree to licence terms on spacesimulator.net copyright page
 *
 *
 * Tutorial 4: 3d engine - 3ds models loader
 * 
 * Include Files: texture.cpp, 3dsloader.cpp
 *  
 */

#pragma once
#include <stdio.h>
#include <io.h>
#include <Windows.h>
#include <new>

#include "glut.h"
#include "Vector.h"

/**********************************************************
 *
 * TYPES DECLARATION
 *
 *********************************************************/

#define MAX_VERTICES 8000 // Max number of vertices (for each object)
#define MAX_POLYGONS 8000 // Max number of polygons (for each object)

// Our vertex type
typedef struct{
    float x,y,z;
}vertex_type;

// The polygon (triangle), 3 numbers that aim 3 vertices
typedef struct{
    unsigned short a,b,c;
}polygon_type;

// The mapcoord type, 2 texture coordinates for each vertex
typedef struct{
    float u,v;
}mapcoord_type;

// The object type
typedef struct {
	char name[20];
    
	int vertices_qty;
    int polygons_qty;

    vertex_type vertex[MAX_VERTICES]; 
    polygon_type polygon[MAX_POLYGONS];
    mapcoord_type mapcoord[MAX_VERTICES];
	Vector* normal[MAX_VERTICES]; // Array of the vertices' normals

    int id_texture;
} obj_type, *obj_type_ptr;


/**********************************************************
 *
 * FUNCTION Load3DS (obj_type_ptr, char *)
 *
 * This function loads a mesh from a 3ds file.
 * Please note that we are loading only the vertices, polygons and mapping lists.
 * If you need to load meshes with advanced features as for example: 
 * multi objects, materials, lights and so on, you must insert other chunk parsers.
 *
 *********************************************************/

extern char Load3DS (obj_type_ptr ogg, char *filename);

/**********************************************************
 *
 * FUNCTION LoadBitmap(char *)
 *
 * This function loads a bitmap file and return the OpenGL reference ID to use that texture
 *
 *********************************************************/

extern int LoadTextureBitmap(char *filename);

void calculateNormals(obj_type_ptr p_object);
