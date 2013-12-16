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

//REMOVE THIS AND FIX
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
/////////

#include "ModelLoader.h"

/**********************************************************
 *
 * TYPES DECLARATION
 *
 *********************************************************/

#define MAX_VERTICES 8000 // Max number of vertices (for each object)
#define MAX_POLYGONS 8000 // Max number of polygons (for each object)


/**********************************************************
 *
 * VARIABLES DECLARATION
 *
 *********************************************************/

// Counter to keep track of the last loaded texture
static int num_texture = -1;

static bool debug_mode = false;

vertex_type normals[MAX_VERTICES];


/**********************************************************
 *
 * FUNCTION LoadBitmap(char *)
 *
 * This function loads a bitmap file and return the OpenGL reference ID to use that texture
 *
 *********************************************************/

int LoadTextureBitmap(char *filename) 
{
	//int num_texture = -1;
    int i, j=0; //Index variables
    FILE *l_file; //File pointer
    unsigned char *l_texture; //The pointer to the memory zone in which we will load the texture
    
    // windows.h gives us these types to work with the Bitmap files
    BITMAPFILEHEADER fileheader; 
    BITMAPINFOHEADER infoheader;
    RGBTRIPLE rgb;

    num_texture++; // The counter of the current texture is increased

    if( (l_file = fopen(filename, "rb"))==NULL) return (-1); // Open the file for reading
    
    fread(&fileheader, sizeof(fileheader), 1, l_file); // Read the fileheader
    
    fseek(l_file, sizeof(fileheader), SEEK_SET); // Jump the fileheader
    fread(&infoheader, sizeof(infoheader), 1, l_file); // and read the infoheader

    // Now we need to allocate the memory for our image (width * height * color deep)
    l_texture = (byte *) malloc(infoheader.biWidth * infoheader.biHeight * 4);
    // And fill it with zeros
    memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);
 
    // At this point we can read every pixel of the image
    for (i=0; i < infoheader.biWidth*infoheader.biHeight; i++)
    {            
            // We load an RGB value from the file
            fread(&rgb, sizeof(rgb), 1, l_file); 

            // And store it
            l_texture[j+0] = rgb.rgbtRed; // Red component
            l_texture[j+1] = rgb.rgbtGreen; // Green component
            l_texture[j+2] = rgb.rgbtBlue; // Blue component
            l_texture[j+3] = 255; // Alpha value
            j += 4; // Go to the next position
    }

    fclose(l_file); // Closes the file stream
     
    glBindTexture(GL_TEXTURE_2D, num_texture); // Bind the ID texture specified by the 2nd parameter
 
    // The next commands sets the texture parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // If the u,v coordinates overflow the range 0,1 the image is repeated
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // The magnification function ("linear" produces better results)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); //The minifying function

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // We don't combine the color with the original surface color, use only the texture map.

    // Finally we define the 2d texture
    glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    // And create 2d mipmaps for the minifying function
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    free(l_texture); // Free the memory we used to load the texture

    return (num_texture); // Returns the current texture OpenGL ID
}


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

char Load3DS (obj_type_ptr p_object, char *p_filename)
{
	int i; //Index variable
	
	FILE *l_file; //File pointer
	
	unsigned short l_chunk_id; //Chunk identifier
	unsigned int l_chunk_lenght; //Chunk lenght

	unsigned char l_char; //Char variable
	unsigned short l_qty; //Number of elements in each chunk

	unsigned short l_face_flags; //Flag that stores some face information

	if ((l_file=fopen (p_filename, "rb"))== NULL) return 0; //Open the file

	while (ftell (l_file) < _filelength (_fileno (l_file))) //Loop to scan the whole file 
	{
		//getche(); //Insert this command for debug (to wait for keypress for each chuck reading)

		fread (&l_chunk_id, 2, 1, l_file); //Read the chunk header
		
		if(debug_mode)
			printf("ChunkID: %x\n",l_chunk_id); 
		fread (&l_chunk_lenght, 4, 1, l_file); //Read the lenght of the chunk

		if(debug_mode)
			printf("ChunkLenght: %x\n",l_chunk_lenght);

		switch (l_chunk_id)
        {
			//----------------- MAIN3DS -----------------
			// Description: Main chunk, contains all the other chunks
			// Chunk ID: 4d4d 
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
			case 0x4d4d: 
			break;    

			//----------------- EDIT3DS -----------------
			// Description: 3D Editor chunk, objects layout info 
			// Chunk ID: 3d3d (hex)
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
			case 0x3d3d:
			break;
			
			//--------------- EDIT_OBJECT ---------------
			// Description: Object block, info for each object
			// Chunk ID: 4000 (hex)
			// Chunk Lenght: len(object name) + sub chunks
			//-------------------------------------------
			case 0x4000: 
				i=0;
				do
				{
					fread (&l_char, 1, 1, l_file);
                    p_object->name[i]=l_char;
					i++;
                }while(l_char != '\0' && i<20);
			break;

			//--------------- OBJ_TRIMESH ---------------
			// Description: Triangular mesh, contains chunks for 3d mesh info
			// Chunk ID: 4100 (hex)
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
			case 0x4100:
			break;
			
			//--------------- TRI_VERTEXL ---------------
			// Description: Vertices list
			// Chunk ID: 4110 (hex)
			// Chunk Lenght: 1 x unsigned short (number of vertices) 
			//             + 3 x float (vertex coordinates) x (number of vertices)
			//             + sub chunks
			//-------------------------------------------
			case 0x4110: 
				fread (&l_qty, sizeof (unsigned short), 1, l_file);
                p_object->vertices_qty = l_qty;

				if(debug_mode)
					printf("Number of vertices: %d\n",l_qty);

                for (i=0; i<l_qty; i++)
                {
					fread (&p_object->vertex[i].x, sizeof(float), 1, l_file);
 					
					if(debug_mode)
						printf("Vertices list x: %f\n",p_object->vertex[i].x);
                    fread (&p_object->vertex[i].y, sizeof(float), 1, l_file);
 					
					if(debug_mode)
						printf("Vertices list y: %f\n",p_object->vertex[i].y);
					fread (&p_object->vertex[i].z, sizeof(float), 1, l_file);
 					
					if(debug_mode)
						printf("Vertices list z: %f\n",p_object->vertex[i].z);
				}
				break;

			//--------------- TRI_FACEL1 ----------------
			// Description: Polygons (faces) list
			// Chunk ID: 4120 (hex)
			// Chunk Lenght: 1 x unsigned short (number of polygons) 
			//             + 3 x unsigned short (polygon points) x (number of polygons)
			//             + sub chunks
			//-------------------------------------------
			case 0x4120:
				fread (&l_qty, sizeof (unsigned short), 1, l_file);
                p_object->polygons_qty = l_qty;

                if(debug_mode)
					printf("Number of polygons: %d\n",l_qty); 

                for (i=0; i<l_qty; i++)
                {
					fread (&p_object->polygon[i].a, sizeof (unsigned short), 1, l_file);
					
					if(debug_mode)
						printf("Polygon point a: %d\n",p_object->polygon[i].a);
					
					fread (&p_object->polygon[i].b, sizeof (unsigned short), 1, l_file);
					
					if(debug_mode)
						printf("Polygon point b: %d\n",p_object->polygon[i].b);
					
					fread (&p_object->polygon[i].c, sizeof (unsigned short), 1, l_file);
					
					if(debug_mode)
						printf("Polygon point c: %d\n",p_object->polygon[i].c);
					
					fread (&l_face_flags, sizeof (unsigned short), 1, l_file);
					
					if(debug_mode)	
						printf("Face flags: %x\n",l_face_flags);
				}
                break;

			//------------- TRI_MAPPINGCOORS ------------
			// Description: Vertices list
			// Chunk ID: 4140 (hex)
			// Chunk Lenght: 1 x unsigned short (number of mapping points) 
			//             + 2 x float (mapping coordinates) x (number of mapping points)
			//             + sub chunks
			//-------------------------------------------
			case 0x4140:
				fread (&l_qty, sizeof (unsigned short), 1, l_file);
				for (i=0; i<l_qty; i++)
				{
					fread (&p_object->mapcoord[i].u, sizeof (float), 1, l_file);

					if(debug_mode)
						printf("Mapping list u: %f\n",p_object->mapcoord[i].u);
                    
					fread (&p_object->mapcoord[i].v, sizeof (float), 1, l_file);
					
					if(debug_mode)
						printf("Mapping list v: %f\n",p_object->mapcoord[i].v);
				}
                break;

			//----------- Skip unknow chunks ------------
			//We need to skip all the chunks that currently we don't use
			//We use the chunk lenght information to set the file pointer
			//to the same level next chunk
			//-------------------------------------------
			default:
				 fseek(l_file, l_chunk_lenght-6, SEEK_CUR);
        } 
	}
	fclose (l_file); // Closes the file stream
	return (1); // Returns ok
}

/*
 *	Enables debug messages and model info for loading 3ds models
 */
void enable3dsDebugMode()
{
	debug_mode = true;
}

/*
 *	Disables debug messages and model info for loading 3ds models
 */
void disable3dsDebugMode()
{
	debug_mode = false;
}

/*
 * Modified code from Damiano Vitulli makes up this function
 *
 */
void calculateNormals(obj_type_ptr p_object)
{
	int i;
	//Array3* l_vect1, l_vect2, l_vect3, l_vect_b1, l_vect_b2, l_normal;
	int l_connections_qty[MAX_VERTICES];

	for (i=0; i < p_object->vertices_qty; i++)
	{
		p_object->normal[i] = new Array3();
		l_connections_qty[i]=0;
	}

	for (i=0; i<p_object->polygons_qty; i++)
	{
		Array3* l_vect1 = new Array3(p_object->vertex[p_object->polygon[i].a].x,
									p_object->vertex[p_object->polygon[i].a].y,
									p_object->vertex[p_object->polygon[i].a].z);
		Array3* l_vect2 = new Array3(p_object->vertex[p_object->polygon[i].b].x,
									p_object->vertex[p_object->polygon[i].b].y,
									p_object->vertex[p_object->polygon[i].b].z);
		Array3* l_vect3 = new Array3(p_object->vertex[p_object->polygon[i].c].x,
									p_object->vertex[p_object->polygon[i].c].y,
									p_object->vertex[p_object->polygon[i].c].z);

		/*VectCreate(&l_vect1, &l_vect2, &l_vect_b1);
		VectCreate(&l_vect1, &l_vect3, &l_vect_b2);*/
		l_vect2->subtract(l_vect1);
		l_vect3->subtract(l_vect1);

		//VectDotProduct (&l_vect_b1, &l_vect_b2, &l_normal);
		Array3* l_normal = l_vect2->crossProduct(l_vect3);

		//VectNormalize (&l_normal);
		l_normal->normalize();

		l_connections_qty[p_object->polygon[i].a]+=1;
		l_connections_qty[p_object->polygon[i].b]+=1;
		l_connections_qty[p_object->polygon[i].c]+=1;

		p_object->normal[p_object->polygon[i].a]->add(l_normal);
		p_object->normal[p_object->polygon[i].b]->add(l_normal);
		p_object->normal[p_object->polygon[i].c]->add(l_normal);
	} 

	for (i=0; i<p_object->vertices_qty; i++)
	{
		if (l_connections_qty[i]>0)
		{
			p_object->normal[i]->divide(l_connections_qty[i]);
		}
	}
}