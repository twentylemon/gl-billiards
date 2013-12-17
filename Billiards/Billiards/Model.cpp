/**
 * 3D imported model, loaded from disk
 *
 * @author Dan Lapp
 * @version 1.0
 * @since 2013-12-10
**/
#include "Model.h"

static int num_texture = -1;

/**
 * Default constructor.
**/
Model::Model(void){
}


/**
 * Constructor. Calls Model::loadObject().
 *
 * @param modelPath where the 3DS model is located
 * @param texturePath where the texture file is located
**/
Model::Model(std::string modelPath, std::string texturePath){
    loadObject((char*)modelPath.c_str(), (char*)texturePath.c_str());
}


/**
 * Destructor.
**/
Model::~Model(void){
}


/**
 * Draws this model.
**/
void Model::draw(){
    glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_TRIANGLES);
        for (unsigned int i = 0; i < polygons.size(); i++){
            for (int j = 0; j < 3; j++){
                glTexCoord2fv(mapCoords[polygons[i][j]].data());
                glNormal3dv(normals[polygons[i][j]]->data());
                glVertex3dv(verticies[polygons[i][j]]->data());
            }
        }
	glEnd();
}


/**
 * Prepares this object to be drawn.
 *
 * @param modelPath where the 3DS model is located
 * @param texturePath where the texture file is located
**/
void Model::loadObject(char* modelPath, char* texture){
	load3DS(modelPath);
	textureID = loadTextureBitmap(texture);
	calculateNormals();
    int max = -1;
    for (int i = 0; i < polygons.size(); i++)
        for (int j = 0; j < 3; j++)
            if (max < polygons[i][j])
                max = polygons[i][j];
    printf("max = %d\nnormals = %d\nvertex = %d\n\n", max, normals.size(), verticies.size());
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
int Model::load3DS(char* p_filename){
	int i;
	FILE *l_file;
	
	unsigned short l_chunk_id;      //Chunk identifier
	unsigned int l_chunk_lenght;    //Chunk lenght

	unsigned char l_char;   //Char variable
	unsigned short l_qty;   //Number of elements in each chunk

	unsigned short l_face_flags;    //Flag that stores some face information

	if ((l_file = fopen(p_filename, "rb")) == NULL){
        return 0; //Open the file
    }

	while (ftell (l_file) < _filelength (_fileno (l_file))) //Loop to scan the whole file 
	{
		//getche(); //Insert this command for debug (to wait for keypress for each chuck reading)

		fread(&l_chunk_id, 2, 1, l_file); //Read the chunk header
		
		if(debug_mode)
			printf("ChunkID: %x\n",l_chunk_id); 
		fread(&l_chunk_lenght, 4, 1, l_file); //Read the lenght of the chunk

		if(debug_mode)
			printf("ChunkLenght: %x\n",l_chunk_lenght);

		switch (l_chunk_id){
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
			i = 0;
			do {
				fread(&l_char, 1, 1, l_file);
                //model->name[i]=l_char;
				i++;
            } while(l_char != '\0' && i<20);
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
			fread(&l_qty, sizeof (unsigned short), 1, l_file);
            for (i = 0; i < l_qty; i++){
                float x, y, z;
				fread(&x, sizeof(float), 1, l_file);
                fread(&y, sizeof(float), 1, l_file);
				fread(&z, sizeof(float), 1, l_file);
                verticies.push_back(new Array3(x, y, z));
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
			fread(&l_qty, sizeof (unsigned short), 1, l_file);

            for (i = 0; i < l_qty; i++){
                std::array<unsigned short, 3> poly;
				fread(&poly[0], sizeof (unsigned short), 1, l_file);
				fread(&poly[1], sizeof (unsigned short), 1, l_file);
				fread(&poly[2], sizeof (unsigned short), 1, l_file);
                polygons.push_back(poly);
					
				fread(&l_face_flags, sizeof (unsigned short), 1, l_file);
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
			fread(&l_qty, sizeof (unsigned short), 1, l_file);

			for (i = 0; i < l_qty; i++){
                std::array<float, 2> map;
				fread(&map[0], sizeof (float), 1, l_file);
				fread(&map[1], sizeof (float), 1, l_file);
                mapCoords.push_back(map);
			}
            break;

		//----------- Skip unknown chunks ------------
		//We need to skip all the chunks that currently we don't use
		//We use the chunk lenght information to set the file pointer
		//to the same level next chunk
		//-------------------------------------------
		default:
				fseek(l_file, l_chunk_lenght-6, SEEK_CUR);
        }
	}
	fclose(l_file);
	return 1;
}


/**********************************************************
 *
 * FUNCTION LoadBitmap(char *)
 *
 * This function loads a bitmap file and return the OpenGL reference ID to use that texture
 *
 *********************************************************/
int Model::loadTextureBitmap(char *filename){
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
    for (i=0; i < infoheader.biWidth*infoheader.biHeight; i++){            
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

    return num_texture; // Returns the current texture OpenGL ID
}


/*
 * Modified code from Damiano Vitulli makes up this function
 *
 */
void Model::calculateNormals(){
    std::vector<int> numPolygons(verticies.size());
    for (unsigned int i = 0; i < verticies.size(); i++){
        normals.push_back(new Array3());
    }

    for (unsigned int i = 0; i < polygons.size(); i++){
        //make the two vectors on the polygon
        Array3* vec1 = Array3::subtract(verticies[polygons[i][1]], verticies[polygons[i][0]]);
        Array3* vec2 = Array3::subtract(verticies[polygons[i][2]], verticies[polygons[i][0]]);
        //their cross product is a normal vector to the polygon
        Array3* normal = Array3::crossProduct(vec1, vec2);
        
        //add up all the polygon surface normals
        for (int j = 0; j < 3; j++){
            normals[polygons[i][j]]->add(normal);
            numPolygons[polygons[i][j]]++;
        }
    }

    //now to get the vertex normals, just average the polygon normals
    for (unsigned int i = 0; i < verticies.size(); i++){
        if (numPolygons[i] > 1){
            for (int j = 0; j < 3; j++){
                normals[i]->divide(numPolygons[i]);
            }
        }
    }
}
