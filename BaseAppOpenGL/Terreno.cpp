#pragma warning(disable:4996)

#include "Terreno.h"



CTerreno::CTerreno()
{
	
}


CTerreno::~CTerreno()
{

}

// Fun��o que retorna a altura dentro do heightmap
int CTerreno::Height(int X, int Y)
{

	// Isto � usado como index para nosso array heightmap
	// Para ter certeza que n�o ir� exceder o tamanho do array, usa-se %.
	// Desse modo X e Y ser�o calculados com (MAX_SIZE - 1)

	int x = X % MAP_SIZE;	// Checar erros para o valor de X
	int y = Y % MAP_SIZE;	// Checar erros para o valor de Y

	if (!pHeightMap) return 0;		// Se houver erros...CAI FORA!!!

	// Abaixo n�s precisamos tratar o array simples como um array 2D
	// Pode-se usar a equa��o: index = (x + (y * arrayWidth)
	// Isso assume que estamos usando um array[x][y]
	// Agora que temos o index corrente, podemos retornar a algura daquele index

	return pHeightMap[x + (y * MAP_SIZE)];	// Indexa em nosso array de altura e retorna a altura

}


// Seta uma cor para cada index em particular, dependendo da altura do index
void CTerreno::SetVertexColor(int x, int y)
{

	if (!pHeightMap) return;		// Ter certeza que que nossos dados de altura s�o v�lidos

	// Aqui n�s setamos a cor para o vertice baseado no indedice de altura
	// Para fazer escuro come�amos com -0.15f. Tamb�m pegamos o ratio da cor
	// para 0 e 1.0 pela divis�o da altura por 256.0f
	float fColor = -0.15f + (Height(x, y) / 256.0f);

	// Associamos a sombra verde para o v�rtice corrente
	glColor3f(fColor, fColor, fColor);

}




// Carrega o arquivo .RAW dentro de um array de bytes.
// Cada valor � um valor de altura
void CTerreno::LoadRawFile(LPSTR strName)
{

	FILE *pFile = NULL;

	// Abrindo o arquivo no modo Read/Binary
	pFile = fopen(strName, "rb");

	// Checar se o arquivo foi encontrado e p�de ser aberto
	if (pFile == NULL)
	{
		// Mostra mensagem de erro e termina o programa
		MessageBox(NULL, "Arquivo n�o encontrado!", "Erro carregando textura", MB_OK);
		return;
	}

	// Aqui n�s carregamos nosso .RAW dentro de nosso array de dados pHeightMap
	fread(pHeightMap, 1, MAP_SIZE * MAP_SIZE, pFile);

	// Depois que os dados foram lidos, � bom checar se tudo foi lido corretamente
	int result = ferror(pFile);

	// Checando se recebemos algum erro
	if (result)
	{
		MessageBox(NULL, "Dados da textura n�o recebidos!", "Erro na integridade dos dados", MB_OK);
	}

	// Fechamos o arquivo de textura
	fclose(pFile);

}


// Renderiza o heightmap com QUADS (poligonos)
void CTerreno::RenderHeightMap(bool isTexTile)
{

	int X = 0, Y = 0;		// Vari�veis para percorrer o array
	int x, y, z;			// Variaveis para readability
	float fColor = 0.0f;	// Vari�vel para guardar a cor de nosso pol�gono

	if (!pHeightMap) return;	// Ter certeza que que nossos dados de altura s�o v�lidos

		glBegin(GL_TRIANGLES);

			int index=0;
			for (X = 0; X < MAP_SIZE; X += STEP_SIZE) 
			{

				for (Y = 0; Y < MAP_SIZE; Y += STEP_SIZE) 
				{

					float s = 0.0f;
					float t = 0.0f;

					x = X;
					y = Height(X, Y);
					z = Y;
					if (isTexTile)
						glTexCoord2f(0.0f, 0.0f);
					else
					{						
						s = (float)(x*(1.0f/MAP_SIZE));
						t = (float)(z*(1.0f/MAP_SIZE));
						glTexCoord2f(s, t);
					}
					glVertex3i(x, y, z);


					x = X;
					y = Height(X, Y + STEP_SIZE);
					z = Y + STEP_SIZE;					
					if (isTexTile)
						glTexCoord2f(1.0f, 0.0f);
					else
					{						
						s = (float)(x*(1.0f/MAP_SIZE));
						t = (float)(z*(1.0f/MAP_SIZE));
						glTexCoord2f(s, t);
					}					
					glVertex3i(x, y, z);



					x = X+ STEP_SIZE;
					y = Height(X + STEP_SIZE, Y + STEP_SIZE);
					z = Y + STEP_SIZE;
					if (isTexTile)
						glTexCoord2f(1.0f, 1.0f);
					else
					{						
						s = (float)(x*(1.0f/MAP_SIZE));
						t = (float)(z*(1.0f/MAP_SIZE));
						glTexCoord2f(s, t);
					}					
					glVertex3i(x, y, z);



					x = X;
					y = Height(X, Y);
					z = Y;
					if (isTexTile)
						glTexCoord2f(0.0f, 0.0f);
					else
					{						
						s = (float)(x*(1.0f/MAP_SIZE));
						t = (float)(z*(1.0f/MAP_SIZE));
						glTexCoord2f(s, t);
					}					
					glVertex3i(x, y, z);



					x = X + STEP_SIZE;
					y = Height(X + STEP_SIZE, Y + STEP_SIZE);
					z = Y + STEP_SIZE;
					if (isTexTile)
						glTexCoord2f(1.0f, 1.0f);
					else
					{						
						s = (float)(x*(1.0f/MAP_SIZE));
						t = (float)(z*(1.0f/MAP_SIZE));
						glTexCoord2f(s, t);
					}			
					glVertex3i(x, y, z);

					
					
					x = X + STEP_SIZE;
					y = Height(X + STEP_SIZE, Y);
					z = Y;
					if (isTexTile)
						glTexCoord2f(0.0f, 1.0f);
					else
					{						
						s = (float)(x*(1.0f/MAP_SIZE));
						t = (float)(z*(1.0f/MAP_SIZE));
						glTexCoord2f(s, t);
					}								
					glVertex3i(x, y, z);

				}
			}

		glEnd();

		// Reseta a cor
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

}

void CTerreno::RenderHeightMapMultiTex()
{

	float X = 0.0f, Y = 0.0f;		
	float x = 0.0f, y = 0.0f, z = 0.0f;			
	float fColor = 0.0f;	

	if (!pHeightMap) return;

		glBegin(GL_TRIANGLES);

			int index=0;
			for (X = 0; X < MAP_SIZE; X += STEP_SIZE) 
			{

				for (Y = 0; Y < MAP_SIZE; Y += STEP_SIZE) 
				{

					float s = 0.0f;
					float t = 0.0f;


					x = X;
					y = Height(X, Y);
					z = Y;
					s = (float)(x*(1.0f/MAP_SIZE));
					t = (float)(z*(1.0f/MAP_SIZE));

					//glTexCoord2f(s, t);
					glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f);
					glMultiTexCoord2f(GL_TEXTURE1, s, t);
					glMultiTexCoord2f(GL_TEXTURE2, 0.0f, 0.0f);
					glVertex3i(x, y, z);


					x = X;
					y = Height(X, Y + STEP_SIZE);
					z = Y + STEP_SIZE;
					s = (float)(x*(1.0f/MAP_SIZE));
					t = (float)(z*(1.0f/MAP_SIZE));

					//glTexCoord2f(s, t);
					glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f);
					glMultiTexCoord2f(GL_TEXTURE1, s, t);
					glMultiTexCoord2f(GL_TEXTURE2, 1.0f, 0.0f);
					glVertex3i(x, y, z);



					x = X + STEP_SIZE;
					y = Height(X + STEP_SIZE, Y + STEP_SIZE);
					z = Y + STEP_SIZE;
					s = (float)(x*(1.0f/MAP_SIZE));
					t = (float)(z*(1.0f/MAP_SIZE));

					//glTexCoord2f(s, t);
					glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f);
					glMultiTexCoord2f(GL_TEXTURE1, s, t);
					glMultiTexCoord2f(GL_TEXTURE2, 1.0f, 1.0f);
					glVertex3i(x, y, z);



					x = X;
					y = Height(X, Y);
					z = Y;
					s = (float)(x*(1.0f/MAP_SIZE));
					t = (float)(z*(1.0f/MAP_SIZE));

					//glTexCoord2f(s, t);
					glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f);
					glMultiTexCoord2f(GL_TEXTURE1, s, t);
					glMultiTexCoord2f(GL_TEXTURE2, 0.0f, 0.0f);
					glVertex3i(x, y, z);



					x = X + STEP_SIZE;
					y = Height(X + STEP_SIZE, Y + STEP_SIZE);
					z = Y + STEP_SIZE;
					s = (float)(x*(1.0f/MAP_SIZE));
					t = (float)(z*(1.0f/MAP_SIZE));

					//glTexCoord2f(s, t);
					glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f);
					glMultiTexCoord2f(GL_TEXTURE1, s, t);
					glMultiTexCoord2f(GL_TEXTURE2, 1.0f, 1.0f);
					glVertex3i(x, y, z);

					
					
					x = X + STEP_SIZE;
					y = Height(X + STEP_SIZE, Y);
					z = Y;
					s = (float)(x*(1.0f/MAP_SIZE));
					t = (float)(z*(1.0f/MAP_SIZE));

					//glTexCoord2f(s, t);
					glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f);
					glMultiTexCoord2f(GL_TEXTURE1, s, t);
					glMultiTexCoord2f(GL_TEXTURE2, 0.0f, 1.0f);
					glVertex3i(x, y, z);

				}
			}

		glEnd();

		// Reseta a cor
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

}
