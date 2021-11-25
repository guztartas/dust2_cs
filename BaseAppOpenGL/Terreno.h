#ifndef __TERRENO_H__
#define __TERRENO_H__



#include <windows.h>	// Header File For Windows
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <winsock.h>
#include <crtdbg.h>
#include <fstream>

#include <glew.h>	
#include <gl.h>										// Header File For The OpenGL32 Library
#include <glu.h>										// Header File For The GLu32 Library
#include <glaux.h>
#include <glut.h>
#include <glext.h>


using namespace std;

#define MAP_SIZE		1000	// Este � o tamanho do arquivo .RAW
#define STEP_SIZE		30.0f	// Esta � a largura e altura de cada QUAD(quadrado do terreno)
#define	HEIGHT_RATIO	1.0f 

class CTerreno
{
public:
	CTerreno();
	~CTerreno();

	

	// Fun��o que retorna a altura (0 a 255) para o heightmap pegando X e Y
	int Height(int X, int Y);

	// Seta uma cor para cada index em particular, dependendo da altura do index
	void SetVertexColor(int x, int y);

	// Fun��o que carrega arquivo .RAW com o tamanho certo do arquivo
	void LoadRawFile(LPSTR strName);

	// Fun��o que p�e os dados do heightmap nas primitivas e desenha na tela
	void RenderHeightMap(bool isTexTile);

	void RenderHeightMapMultiTex();




private:
	BYTE pHeightMap[MAP_SIZE * MAP_SIZE];
	
	
};


#endif
