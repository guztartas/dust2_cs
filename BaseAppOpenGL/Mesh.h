#pragma once

#include <windows.h>
#include <stdio.h>
#include "glew.h"
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
// assimp include files. These three are usually needed.
#include "assimp/Importer.hpp"	//OO version Header!
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "assimp/DefaultLogger.hpp"
#include "assimp/LogStream.hpp"
#include "assimp\mesh.h"


//to map image filenames to textureIds
#include <string.h>
#include <map>
#include <vector>

class Mesh
{
public :
	struct MeshEntry {
		static enum BUFFERS {
			VERTEX_BUFFER, TEXCOORD_BUFFER, NORMAL_BUFFER, INDEX_BUFFER
		};
		GLuint vao;
		GLuint vbo[4];

		unsigned int elementCount;

		MeshEntry(aiMesh *mesh);
		~MeshEntry();

		void load(aiMesh *mesh);
		void render();
	};

	std::vector<MeshEntry*> meshEntries;

public:
	Mesh(const char *filename);
	~Mesh(void);

	void render();
	std::string getBasePath(const std::string& path);
	int LoadGLTextures(const aiScene* scene);
	void Color4f(const aiColor4D *color);
	void set_float4(float f[4], float a, float b, float c, float d);
	void color4_to_float4(const aiColor4D *c, float f[4]);
	void apply_material(const aiMaterial *mtl);

	std::string modelpath;

	// the global Assimp scene object
	const aiScene* scene;
	GLuint scene_list;
	aiVector3D scene_min, scene_max, scene_center;

	// images / texture
	std::map<std::string, GLuint*> textureIdMap;	// map image filenames to textureIds
	GLuint*		textureIds;							// pointer to texture Array

	Assimp::Importer importer;	// Create an instance of the Importer class
};

