#include "CModel_ASSIMP.h"



CModel_ASSIMP::CModel_ASSIMP(RENDER_MODE render, std::string modelPathAndName)
{
	this->modelpath = "";
	this->scene = NULL;
	this->scene_list = 0;
	this->modelpath = modelPathAndName;
	this->iRenderMode = render;

	this->Load();

	if (this->iRenderMode == RENDER_MODE::IMMEDIATE)
	{

	}
	else if (this->iRenderMode == RENDER_MODE::DISPLAYLIST)
	{
		displayListId = 0;
		CreateDisplayList();
	}
	else if (this->iRenderMode == RENDER_MODE::VERTEX_ARRAY)
	{
		for (int i = 0; i < scene->mNumMeshes; ++i)
		{
			meshEntries.push_back(new CModel_ASSIMP::MeshEntry(scene->mMeshes[i]));
		}
	}
	else {}

	//	this->createAILogger();
	//	this->logInfo("App fired!");	
}


CModel_ASSIMP::~CModel_ASSIMP()
{
	this->textureIdMap.clear(); //no need to delete pointers in it manually here. (Pointers point to textureIds deleted in next step)

	if (this->textureIds)
	{
		delete[] this->textureIds;
		this->textureIds = NULL;
	}

	if (this->iRenderMode == RENDER_MODE::DISPLAYLIST)
	{
		glDeleteLists(this->displayListId, 1);
	}

	if (this->iRenderMode == RENDER_MODE::VERTEX_ARRAY)
	{
		for (int i = 0; i < meshEntries.size(); ++i)
		{
			delete meshEntries.at(i);
		}
		meshEntries.clear();
	}

	//this->destroyAILogger();
}

void CModel_ASSIMP::Load()
{
	this->Import3DFromFile(this->modelpath);
	this->LoadGLTextures(this->scene);
}

void CModel_ASSIMP::createAILogger()
{
	// Change this line to normal if you not want to analyse the import process
	//Assimp::Logger::LogSeverity severity = Assimp::Logger::NORMAL;
	Assimp::Logger::LogSeverity severity = Assimp::Logger::VERBOSE;

	// Create a logger instance for Console Output
	Assimp::DefaultLogger::create("", severity, aiDefaultLogStream_STDOUT);

	// Create a logger instance for File Output (found in project folder or near .exe)
	Assimp::DefaultLogger::create("assimp_log.txt", severity, aiDefaultLogStream_FILE);

	// Now I am ready for logging my stuff
	Assimp::DefaultLogger::get()->info("this is my info-call");
}

void CModel_ASSIMP::destroyAILogger()
{
	// Kill it after the work is done
	Assimp::DefaultLogger::kill();
}

void CModel_ASSIMP::logInfo(std::string logString)
{
	// Will add message to File with "info" Tag
	Assimp::DefaultLogger::get()->info(logString.c_str());
}

void CModel_ASSIMP::logDebug(const char* logString)
{
	// Will add message to File with "debug" Tag
	Assimp::DefaultLogger::get()->debug(logString);
}


bool CModel_ASSIMP::Import3DFromFile(const std::string& pFile)
{
	// Check if file exists
	std::ifstream fin(pFile.c_str());
	if (!fin.fail())
	{
		fin.close();
	}
	else
	{
		MessageBox(NULL, ("Couldn't open file: " + pFile).c_str(), "ERROR", MB_OK | MB_ICONEXCLAMATION);
		//logInfo(importer.GetErrorString());
		return false;
	}

	scene = importer.ReadFile(pFile, aiProcessPreset_TargetRealtime_Quality);

	// If the import failed, report it
	if (!scene)
	{
		//logInfo(importer.GetErrorString());
		MessageBox(NULL, importer.GetErrorString(), "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	// Now we can access the file's contents.
	//logInfo("Import of scene " + pFile + " succeeded.");

	// We're done. Everything will be cleaned up by the importer destructor
	return true;
}

std::string CModel_ASSIMP::getBasePath(const std::string& path)
{
	size_t pos = path.find_last_of("\\/");
	return (std::string::npos == pos) ? "" : path.substr(0, pos + 1);
}

int CModel_ASSIMP::LoadGLTextures(const aiScene* scene)
{
	ILboolean success;

	/* Before calling ilInit() version should be checked. */
	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
	{
		/// wrong DevIL version ///
		std::string err_msg = "Wrong DevIL version. Old devil.dll in system32/SysWow64?";
		char* cErr_msg = (char*)err_msg.c_str();
		MessageBox(NULL, cErr_msg, "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return -1;
	}

	ilInit(); /* Initialization of DevIL */

	if (scene->HasTextures())
		MessageBox(NULL, "Support for meshes with embedded textures is not implemented", "ERROR", MB_OK | MB_ICONEXCLAMATION);

	/* getTexture Filenames and Numb of Textures */
	for (unsigned int m = 0; m < scene->mNumMaterials; m++)
	{
		int texIndex = 0;
		aiReturn texFound = AI_SUCCESS;

		aiString path;	// filename

		while (texFound == AI_SUCCESS)
		{
			texFound = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
			textureIdMap[path.data] = NULL; //fill map with textures, pointers still NULL yet
			texIndex++;
		}
	}

	int numTextures = textureIdMap.size();

	/* array with DevIL image IDs */
	ILuint* imageIds = NULL;
	imageIds = new ILuint[numTextures];

	/* generate DevIL Image IDs */
	ilGenImages(numTextures, imageIds); /* Generation of numTextures image names */

										/* create and fill array with GL texture ids */
	textureIds = new GLuint[numTextures];
	glGenTextures(numTextures, textureIds); /* Texture name generation */

											/* get iterator */
	std::map<std::string, GLuint*>::iterator itr = textureIdMap.begin();

	std::string basepath = getBasePath(modelpath);
	for (int i = 0; i < numTextures; i++)
	{

		//save IL image ID
		std::string filename = (*itr).first;  // get filename
		(*itr).second = &textureIds[i];	  // save texture id for filename in map
		itr++;								  // next texture


		ilBindImage(imageIds[i]); /* Binding of DevIL image name */
		std::string fileloc = basepath + filename;	/* Loading of image */
		success = ilLoadImage(fileloc.c_str());

		if (success) /* If no error occurred: */
		{
			// Convert every colour component into unsigned byte.If your image contains 
			// alpha channel you can replace IL_RGB with IL_RGBA
			ILenum imageType = ilDetermineType(fileloc.c_str());

			if (imageType == IL_TGA)
			{
				success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
				iluFlipImage();
			}
			else
				success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);

			if (!success)
			{
				/* Error occurred */
				MessageBox(NULL, "Couldn't convert image", "ERROR", MB_OK | MB_ICONEXCLAMATION);
				return -1;
			}
			// Binding of texture name
			glBindTexture(GL_TEXTURE_2D, textureIds[i]);


			// redefine standard texture values
			// We will use linear interpolation for magnification filter
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// We will use linear interpolation for minifying filter
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			// Texture specification
			glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
				ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
				ilGetData());
			// we also want to be able to deal with odd texture dimensions
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
			glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
			glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
		}
		else
		{
			/* Error occurred */
			MessageBox(NULL, ("Couldn't load Image: " + fileloc).c_str(), "ERROR", MB_OK | MB_ICONEXCLAMATION);
		}
	}
	// Because we have already copied image data into texture data  we can release memory used by image.
	ilDeleteImages(numTextures, imageIds);

	// Cleanup
	delete[] imageIds;
	imageIds = NULL;

	return TRUE;
}

// Can't send color down as a pointer to aiColor4D because AI colors are ABGR.
void CModel_ASSIMP::Color4f(const aiColor4D* color)
{
	glColor4f(color->r, color->g, color->b, color->a);
}

void CModel_ASSIMP::set_float4(float f[4], float a, float b, float c, float d)
{
	f[0] = a;
	f[1] = b;
	f[2] = c;
	f[3] = d;
}

void CModel_ASSIMP::color4_to_float4(const aiColor4D* c, float f[4])
{
	f[0] = c->r;
	f[1] = c->g;
	f[2] = c->b;
	f[3] = c->a;
}

void CModel_ASSIMP::apply_material(const aiMaterial* mtl)
{
	//float c[4];

	////GLenum fill_mode;
	//int ret1, ret2;
	//aiColor4D diffuse;
	//aiColor4D specular;
	//aiColor4D ambient;
	//aiColor4D emission;
	//ai_real shininess, strength;
	////int two_sided;
	////int wireframe;
	//unsigned int max;	// changed: to unsigned

	int texIndex = 0;
	aiString texPath;	//contains filename of texture

	if (AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, texIndex, &texPath))
	{
		//bind texture
		unsigned int texId = *textureIdMap[texPath.data];
		glBindTexture(GL_TEXTURE_2D, texId);
	}

	//set_float4(c, 1.0f, 1.0f, 1.0f, 1.0f);
	//if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
	//	color4_to_float4(&ambient, c);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);

	//set_float4(c, 1.0f, 1.0f, 1.0f, 1.0f);
	//if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
	//	color4_to_float4(&diffuse, c);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c);

	//set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	//if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
	//	color4_to_float4(&specular, c);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);	

	//set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	//if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
	//	color4_to_float4(&emission, c);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, c);

	//max = 1;
	//ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
	//max = 1;
	//ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
	//if ((ret1 == AI_SUCCESS) && (ret2 == AI_SUCCESS))
	//	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
	//else {
	//	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
	//	set_float4(c, 0.0f, 0.0f, 0.0f, 0.0f);
	//	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
	//}
}


void CModel_ASSIMP::recursive_render(const struct aiScene* sc, const struct aiNode* nd, float scale)
{
	unsigned int i;
	unsigned int n = 0, t;
	aiMatrix4x4 m = nd->mTransformation;

	//aiMatrix4x4 m2;
	//aiMatrix4x4::Scaling(aiVector3D(scale, scale, scale), m2);
	//m = m * m2;

	// update transform
	m.Transpose();
	glPushMatrix();
	glMultMatrixf((float*)&m);

	// draw all meshes assigned to this node
	for (; n < nd->mNumMeshes; ++n)
	{
		const struct aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];

		apply_material(sc->mMaterials[mesh->mMaterialIndex]);

		for (t = 0; t < mesh->mNumFaces; ++t)
		{
			const struct aiFace* face = &mesh->mFaces[t];
			GLenum face_mode;

			switch (face->mNumIndices)
			{
				case 1: face_mode = GL_POINTS; break;
				case 2: face_mode = GL_LINES; break;
				case 3: face_mode = GL_TRIANGLES; break;
				default: face_mode = GL_POLYGON; break;
			}

			glBegin(face_mode);
			for (i = 0; i < face->mNumIndices; i++)		// go through all vertices in face
			{
				int vertexIndex = face->mIndices[i];	// get group index for current index
				if (mesh->mColors[0] != NULL)
					Color4f(&mesh->mColors[0][vertexIndex]);
				if (mesh->mNormals != NULL)
					glNormal3fv(&mesh->mNormals[vertexIndex].x);
				if (mesh->HasTextureCoords(0))		//HasTextureCoords(texture_coordinates_set)
					glTexCoord2f(mesh->mTextureCoords[0][vertexIndex].x, 1 - mesh->mTextureCoords[0][vertexIndex].y); //mTextureCoords[channel][vertex]

				glVertex3fv(&mesh->mVertices[vertexIndex].x);
			}
			glEnd();
		}
	}

	// draw all children
	for (n = 0; n < nd->mNumChildren; ++n)
	{
		recursive_render(sc, nd->mChildren[n], scale);
	}

	glPopMatrix();
}



void CModel_ASSIMP::CreateDisplayList()
{
	displayListId = glGenLists(1);
	glNewList(displayListId, GL_COMPILE);

	this->recursive_render(this->scene, this->scene->mRootNode, 1.0);

	glEndList();
}


void CModel_ASSIMP::Draw()
{
	if (this->iRenderMode == RENDER_MODE::IMMEDIATE)
	{
		this->recursive_render(this->scene, this->scene->mRootNode, 1.0);
	}
	else if (this->iRenderMode == RENDER_MODE::DISPLAYLIST)
	{
		glCallList(displayListId);
	}
	else if (this->iRenderMode == RENDER_MODE::VERTEX_ARRAY)
	{
		//aiMatrix4x4 mRoot = this->scene->mRootNode->mTransformation;
		//mRoot.Transpose();
		//glPushMatrix();
		//glMultMatrixf((float*)&mRoot);

		for (int i = 0; i < meshEntries.size(); ++i)
		{
			const struct aiMesh* mesh = scene->mMeshes[i];

			apply_material(scene->mMaterials[mesh->mMaterialIndex]);

			//aiMatrix4x4 m = this->scene->mRootNode->mChildren[i]->mTransformation;
			//m.Transpose();

			//glPushMatrix();
			//glMultMatrixf((float*)&m);
			meshEntries.at(i)->render();
			//glPopMatrix();
		}

		//glPopMatrix();
	}
	else {}
}




CModel_ASSIMP::MeshEntry::MeshEntry(aiMesh* mesh)
{
	elementCount = mesh->mNumFaces * 3;

	if (mesh->HasPositions())
	{
		vertices = new float[mesh->mNumVertices * 3];
		for (int i = 0; i < mesh->mNumVertices; ++i)
		{
			vertices[i * 3] = mesh->mVertices[i].x;
			vertices[i * 3 + 1] = mesh->mVertices[i].y;
			vertices[i * 3 + 2] = mesh->mVertices[i].z;
		}
	}


	if (mesh->HasTextureCoords(0))
	{
		texCoords = new float[mesh->mNumVertices * 2];
		for (int i = 0; i < mesh->mNumVertices; ++i)
		{
			texCoords[i * 2] = mesh->mTextureCoords[0][i].x;
			texCoords[i * 2 + 1] = (1 - mesh->mTextureCoords[0][i].y);
		}
	}


	if (mesh->HasNormals())
	{
		normals = new float[mesh->mNumVertices * 3];
		for (int i = 0; i < mesh->mNumVertices; ++i)
		{
			normals[i * 3] = mesh->mNormals[i].x;
			normals[i * 3 + 1] = mesh->mNormals[i].y;
			normals[i * 3 + 2] = mesh->mNormals[i].z;
		}
	}


	if (mesh->HasFaces())
	{
		indices = new unsigned int[mesh->mNumFaces * 3];
		for (int i = 0; i < mesh->mNumFaces; ++i)
		{
			indices[i * 3] = mesh->mFaces[i].mIndices[0];
			indices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
			indices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
		}
	}
}


CModel_ASSIMP::MeshEntry::~MeshEntry()
{
	delete[] vertices;
	delete[] texCoords;
	delete[] normals;
	delete[] indices;
}

void CModel_ASSIMP::MeshEntry::render()
{
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glNormalPointer(GL_FLOAT, 0, normals);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, indices);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}