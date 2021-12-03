#include "Scene1.h"


CScene1::CScene1()
{
	pCamera = NULL;
	pTexto = NULL;
	pTextures = NULL;
	smokeTextures = NULL;

	bIsWireframe = false;
	bIsCameraFPS = true;

	iFPS = 0;
	iFrames = 0;
	ulLastFPS = 0;
	szTitle[256] = 0;

	nextText = 0;

	// Cria gerenciador de impressão de texto na tela
	pTexto = new CTexto();

	// Cria camera
	pCamera = new CCamera(289.0f, 22.0f, -67.44f, 0.9f);

	// Cria o Timer
	pTimer = new CTimer();
	pTimer->Init();

	fTimerPosY = 0.0f;
	fRenderPosY = 0.0f;

	glPushAttrib(GL_TEXTURE_BIT);
	// Carrega todas as texturas
	pTextures = new CTexture();	
	pTextures->CreateTextureMipMap(0, "../Scene1/back.bmp");
	pTextures->CreateTextureMipMap(1, "../Scene1/front.bmp");
	pTextures->CreateTextureMipMap(2, "../Scene1/down.bmp");
	pTextures->CreateTextureMipMap(3, "../Scene1/up.bmp");
	pTextures->CreateTextureMipMap(4, "../Scene1/left.bmp");
	pTextures->CreateTextureMipMap(5, "../Scene1/right.bmp");
	pTextures->CreateTextureMipMap(6, "../Scene1/terreno.bmp");
	pTextures->CreateTextureMipMap(7, "../Scene1/Dust2/textures/window.jpg");
	glPopAttrib();

	glPushAttrib(GL_TEXTURE_BIT);
	smokeTextures = new CTexture();
	smokeTextures->CreateTextureTGA(0, "../Scene1/Smoke/explosion01-frame001.tga");
	smokeTextures->CreateTextureTGA(1, "../Scene1/Smoke/explosion01-frame002.tga");
	smokeTextures->CreateTextureTGA(2, "../Scene1/Smoke/explosion01-frame003.tga");
	smokeTextures->CreateTextureTGA(3, "../Scene1/Smoke/explosion01-frame004.tga");
	smokeTextures->CreateTextureTGA(4, "../Scene1/Smoke/explosion01-frame005.tga");
	smokeTextures->CreateTextureTGA(5, "../Scene1/Smoke/explosion01-frame006.tga");
	smokeTextures->CreateTextureTGA(6, "../Scene1/Smoke/explosion01-frame007.tga");
	smokeTextures->CreateTextureTGA(7, "../Scene1/Smoke/explosion01-frame008.tga");
	smokeTextures->CreateTextureTGA(8, "../Scene1/Smoke/explosion01-frame009.tga");
	smokeTextures->CreateTextureTGA(9, "../Scene1/Smoke/explosion01-frame010.tga");
	smokeTextures->CreateTextureTGA(10, "../Scene1/Smoke/explosion01-frame011.tga");
	smokeTextures->CreateTextureTGA(11, "../Scene1/Smoke/explosion01-frame012.tga");
	smokeTextures->CreateTextureTGA(12, "../Scene1/Smoke/explosion01-frame013.tga");
	smokeTextures->CreateTextureTGA(13, "../Scene1/Smoke/explosion01-frame014.tga");
	smokeTextures->CreateTextureTGA(14, "../Scene1/Smoke/explosion01-frame015.tga");
	smokeTextures->CreateTextureTGA(15, "../Scene1/Smoke/explosion01-frame016.tga");
	smokeTextures->CreateTextureTGA(16, "../Scene1/Smoke/explosion01-frame017.tga");
	smokeTextures->CreateTextureTGA(17, "../Scene1/Smoke/explosion01-frame018.tga");
	smokeTextures->CreateTextureTGA(18, "../Scene1/Smoke/explosion01-frame019.tga");
	smokeTextures->CreateTextureTGA(19, "../Scene1/Smoke/explosion01-frame020.tga");
	smokeTextures->CreateTextureTGA(20, "../Scene1/Smoke/explosion01-frame021.tga");
	smokeTextures->CreateTextureTGA(21, "../Scene1/Smoke/explosion01-frame022.tga");
	smokeTextures->CreateTextureTGA(22, "../Scene1/Smoke/explosion01-frame023.tga");
	smokeTextures->CreateTextureTGA(23, "../Scene1/Smoke/explosion01-frame024.tga");
	smokeTextures->CreateTextureTGA(24, "../Scene1/Smoke/explosion01-frame025.tga");
	smokeTextures->CreateTextureTGA(25, "../Scene1/Smoke/explosion01-frame026.tga");
	smokeTextures->CreateTextureTGA(26, "../Scene1/Smoke/explosion01-frame027.tga");
	smokeTextures->CreateTextureTGA(27, "../Scene1/Smoke/explosion01-frame028.tga");
	smokeTextures->CreateTextureTGA(28, "../Scene1/Smoke/explosion01-frame029.tga");
	smokeTextures->CreateTextureTGA(29, "../Scene1/Smoke/explosion01-frame030.tga");
	smokeTextures->CreateTextureTGA(30, "../Scene1/Smoke/explosion01-frame031.tga");
	smokeTextures->CreateTextureTGA(31, "../Scene1/Smoke/explosion01-frame032.tga");
	smokeTextures->CreateTextureTGA(32, "../Scene1/Smoke/explosion01-frame033.tga");
	smokeTextures->CreateTextureTGA(33, "../Scene1/Smoke/explosion01-frame034.tga");
	smokeTextures->CreateTextureTGA(34, "../Scene1/Smoke/explosion01-frame035.tga");
	smokeTextures->CreateTextureTGA(35, "../Scene1/Smoke/explosion01-frame036.tga");
	smokeTextures->CreateTextureTGA(36, "../Scene1/Smoke/explosion01-frame037.tga");
	smokeTextures->CreateTextureTGA(37, "../Scene1/Smoke/explosion01-frame038.tga");
	smokeTextures->CreateTextureTGA(38, "../Scene1/Smoke/explosion01-frame039.tga");
	smokeTextures->CreateTextureTGA(39, "../Scene1/Smoke/explosion01-frame040.tga");
	smokeTextures->CreateTextureTGA(40, "../Scene1/Smoke/explosion01-frame041.tga");
	smokeTextures->CreateTextureTGA(41, "../Scene1/Smoke/explosion01-frame042.tga");
	smokeTextures->CreateTextureTGA(42, "../Scene1/Smoke/explosion01-frame043.tga");
	smokeTextures->CreateTextureTGA(43, "../Scene1/Smoke/explosion01-frame044.tga");
	smokeTextures->CreateTextureTGA(44, "../Scene1/Smoke/explosion01-frame045.tga");
	smokeTextures->CreateTextureTGA(45, "../Scene1/Smoke/explosion01-frame046.tga");
	smokeTextures->CreateTextureTGA(46, "../Scene1/Smoke/explosion01-frame047.tga");
	smokeTextures->CreateTextureTGA(47, "../Scene1/Smoke/explosion01-frame048.tga");
	smokeTextures->CreateTextureTGA(48, "../Scene1/Smoke/explosion01-frame049.tga");
	smokeTextures->CreateTextureTGA(49, "../Scene1/Smoke/explosion01-frame050.tga");
	smokeTextures->CreateTextureTGA(50, "../Scene1/Smoke/explosion01-frame051.tga");
	smokeTextures->CreateTextureTGA(51, "../Scene1/Smoke/explosion01-frame052.tga");
	smokeTextures->CreateTextureTGA(52, "../Scene1/Smoke/explosion01-frame053.tga");
	smokeTextures->CreateTextureTGA(53, "../Scene1/Smoke/explosion01-frame054.tga");
	smokeTextures->CreateTextureTGA(54, "../Scene1/Smoke/explosion01-frame055.tga");
	smokeTextures->CreateTextureTGA(55, "../Scene1/Smoke/explosion01-frame056.tga");
	smokeTextures->CreateTextureTGA(56, "../Scene1/Smoke/explosion01-frame057.tga");
	smokeTextures->CreateTextureTGA(57, "../Scene1/Smoke/explosion01-frame058.tga");
	smokeTextures->CreateTextureTGA(58, "../Scene1/Smoke/explosion01-frame059.tga");
	smokeTextures->CreateTextureTGA(59, "../Scene1/Smoke/explosion01-frame060.tga");
	smokeTextures->CreateTextureTGA(60, "../Scene1/Smoke/explosion01-frame061.tga");
	smokeTextures->CreateTextureTGA(61, "../Scene1/Smoke/explosion01-frame062.tga");
	smokeTextures->CreateTextureTGA(62, "../Scene1/Smoke/explosion01-frame063.tga");
	smokeTextures->CreateTextureTGA(63, "../Scene1/Smoke/explosion01-frame064.tga");
	smokeTextures->CreateTextureTGA(64, "../Scene1/Smoke/explosion01-frame065.tga");
	smokeTextures->CreateTextureTGA(65, "../Scene1/Smoke/explosion01-frame066.tga");
	smokeTextures->CreateTextureTGA(66, "../Scene1/Smoke/explosion01-frame067.tga");
	smokeTextures->CreateTextureTGA(67, "../Scene1/Smoke/explosion01-frame068.tga");
	smokeTextures->CreateTextureTGA(68, "../Scene1/Smoke/explosion01-frame069.tga");
	smokeTextures->CreateTextureTGA(69, "../Scene1/Smoke/explosion01-frame070.tga");
	smokeTextures->CreateTextureTGA(70, "../Scene1/Smoke/explosion01-frame071.tga");
	smokeTextures->CreateTextureTGA(71, "../Scene1/Smoke/explosion01-frame072.tga");
	smokeTextures->CreateTextureTGA(72, "../Scene1/Smoke/explosion01-frame073.tga");
	smokeTextures->CreateTextureTGA(73, "../Scene1/Smoke/explosion01-frame074.tga");
	smokeTextures->CreateTextureTGA(74, "../Scene1/Smoke/explosion01-frame075.tga");
	smokeTextures->CreateTextureTGA(75, "../Scene1/Smoke/explosion01-frame076.tga");
	smokeTextures->CreateTextureTGA(76, "../Scene1/Smoke/explosion01-frame077.tga");
	smokeTextures->CreateTextureTGA(77, "../Scene1/Smoke/explosion01-frame078.tga");
	smokeTextures->CreateTextureTGA(78, "../Scene1/Smoke/explosion01-frame079.tga");
	smokeTextures->CreateTextureTGA(79, "../Scene1/Smoke/explosion01-frame080.tga");
	smokeTextures->CreateTextureTGA(80, "../Scene1/Smoke/explosion01-frame081.tga");
	smokeTextures->CreateTextureTGA(81, "../Scene1/Smoke/explosion01-frame082.tga");
	smokeTextures->CreateTextureTGA(82, "../Scene1/Smoke/explosion01-frame083.tga");
	smokeTextures->CreateTextureTGA(83, "../Scene1/Smoke/explosion01-frame084.tga");
	smokeTextures->CreateTextureTGA(84, "../Scene1/Smoke/explosion01-frame085.tga");
	smokeTextures->CreateTextureTGA(85, "../Scene1/Smoke/explosion01-frame086.tga");
	smokeTextures->CreateTextureTGA(86, "../Scene1/Smoke/explosion01-frame087.tga");
	smokeTextures->CreateTextureTGA(87, "../Scene1/Smoke/explosion01-frame088.tga");
	smokeTextures->CreateTextureTGA(88, "../Scene1/Smoke/explosion01-frame089.tga");
	smokeTextures->CreateTextureTGA(89, "../Scene1/Smoke/explosion01-frame090.tga");
	smokeTextures->CreateTextureTGA(90, "../Scene1/Smoke/explosion01-frame091.tga");
	smokeTextures->CreateTextureTGA(91, "../Scene1/Smoke/explosion01-frame092.tga");
	smokeTextures->CreateTextureTGA(92, "../Scene1/Smoke/explosion01-frame093.tga");
	smokeTextures->CreateTextureTGA(93, "../Scene1/Smoke/explosion01-frame094.tga");
	smokeTextures->CreateTextureTGA(94, "../Scene1/Smoke/explosion01-frame095.tga");
	smokeTextures->CreateTextureTGA(95, "../Scene1/Smoke/explosion01-frame096.tga");
	smokeTextures->CreateTextureTGA(96, "../Scene1/Smoke/explosion01-frame097.tga");
	smokeTextures->CreateTextureTGA(97, "../Scene1/Smoke/explosion01-frame098.tga");
	smokeTextures->CreateTextureTGA(98, "../Scene1/Smoke/explosion01-frame099.tga");
	smokeTextures->CreateTextureTGA(99, "../Scene1/Smoke/explosion01-frame100.tga");
	glPopAttrib();

	fPosX = 0.0f;
	fPosY = 0.0f;
	fPosZ = 0.0f;
	fMovementFactor = 0.01f;	

	fAngle = 0.0f;		
	
	pModelASSIMP_1 = NULL;
	pModelASSIMP_1 = new CModel_ASSIMP(CModel_ASSIMP::IMMEDIATE, "../Scene1/Dust2/d2.obj");

	pModelASSIMP_2 = NULL;
	pModelASSIMP_2 = new CModel_ASSIMP(CModel_ASSIMP::IMMEDIATE, "../Scene1/Dust2/byBox.obj");

	fLowLight[0] = 0.5;
	fLowLight[1] = 0.5;
	fLowLight[2] = 0.5;
	fLowLight[3] = 1.0;
}


CScene1::~CScene1(void)
{
	if (pTexto)
	{
		delete pTexto;
		pTexto = NULL;
	}

	if (pTextures)
	{
		delete pTextures;
		pTextures = NULL;
	}

	if (smokeTextures)
	{
		delete smokeTextures;
		smokeTextures = NULL;
	}

	if (pCamera)
	{
		delete pCamera;
		pCamera = NULL;
	}

	if (pTimer)
	{
		delete pTimer;
		pTimer = NULL;
	}

	if (pModelASSIMP_1)
	{
		delete pModelASSIMP_1;
		pModelASSIMP_1 = NULL;
	}

	if (pModelASSIMP_2)
	{
		delete pModelASSIMP_2;
		pModelASSIMP_2 = NULL;
	}
}




int CScene1::DrawGLScene(void)	// Função que desenha a cena
{
	// Get FPS
	if (GetTickCount() - ulLastFPS >= 1000)	// When A Second Has Passed...
	{
		ulLastFPS = GetTickCount();				// Update Our Time Variable
		iFPS = iFrames;							// Save The FPS
		iFrames = 0;							// Reset The FPS Counter
	}
	iFrames++;									// FPS counter

	pTimer->Update();							// Atualiza o timer

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limpa a tela e o Depth Buffer
	glLoadIdentity();									// Inicializa a Modelview Matrix Atual


	// Seta as posições da câmera
	pCamera->setView();

	// Desenha grid 
	//Draw3DSGrid(20.0f, 20.0f);

	// Desenha os eixos do plano cartesiano
	//DrawAxis();

	// Modo FILL ou WIREFRAME (pressione barra de espaço)	
	if (bIsWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (INÍCIO)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// Primeiro definir a cor da atual para BRANCO 100%
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);

	CreateSkyBox(0.0f, 100.0f, 0.0f, 1500.0f, 1500.0f, 1500.0f, pTextures);

	glEnable(GL_FOG);
	glFogfv(GL_FOG_COLOR, fLowLight);
	glFogf(GL_FOG_START, -500.0f);
	glFogf(GL_FOG_END, 500.0f);
	glFogi(GL_FOG_MODE, GL_LINEAR);

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -150.0f);
	glScalef(20.0f, 20.0f, 20.0f);
		pModelASSIMP_1->Draw();
	glPopMatrix();	

	glPushMatrix();
	glTranslatef(399.29f, -11.8f, -168.5f);
	glScalef(5.0f, 5.0f, 5.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		pModelASSIMP_2->Draw();
	glPopMatrix();

	// SMOKE
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);

	pTextures->ApplyTexture(7);
	glPushMatrix();
	glTranslatef(272.9f, 49.8f, -203.0f);
	glBegin(GL_QUADS);
	glScalef(5.0f, 5.0f, 5.0f);


	glTexCoord2d(0.0f, 0.0f); glVertex3f(1.5f, -1.3f, 3.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(1.5f, -1.3f, -3.20f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(1.5f, 5.1f, -3.20f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(1.5f, 5.1f, 3.0f);

	glEnd();
	glPopMatrix();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	if (pTimer->GetTime() >= 20)
	{
		nextText++;
		pTimer->Init();
	
		if (nextText >= 100) {
			nextText = 0;
		}
	}

	smokeTextures->ApplyTexture(nextText);

	glPushMatrix();

	float matrixBillboard[16] =
	{
		pCamera->Right[0],      pCamera->Right[1],	  pCamera->Right[2],	0.0f,
		pCamera->Up[0],         pCamera->Up[1],		  pCamera->Up[2],		0.0f,
		pCamera->Forward[0],    pCamera->Forward[1],  pCamera->Forward[2],	0.0f,
		262.29f,					20.15f,				  -178.68f,				1.0f
	};

	glMultMatrixf(matrixBillboard);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-60.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(60.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(60.0f, 120.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-60.0f, 120.0f, 0.0f);

	glEnd();
	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_FOG);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (FIM)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	fTimerPosY = pTimer->GetTime() / 1000.0f;
	fRenderPosY += 0.01f;

	// Impressão de texto na tela...
	// Muda para modo de projeção ortogonal 2D
	// OBS: Desabilite Texturas e Iluminação antes de entrar nesse modo de projeção
	OrthoMode(0, 0, WIDTH, HEIGHT);


	glPushMatrix();
	glTranslatef(0.0f, HEIGHT - 200, 0.0f);	// Move 1 unidade para dentro da tela (eixo Z)

	// Cor da fonte
	glColor3f(1.0f, 1.0f, 0.0f);


	glRasterPos2f(10.0f, 0.0f);	// Posicionando o texto na tela
	if (!bIsWireframe) {
		pTexto->glPrint("[TAB]  Modo LINE"); // Imprime texto na tela
	}
	else {
		pTexto->glPrint("[TAB]  Modo FILL");
	}


	//// Camera LookAt
	glRasterPos2f(10.0f, 40.0f);
	pTexto->glPrint("Player LookAt  : %f, %f, %f", pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);

	//// Posição do Player
	glRasterPos2f(10.0f, 60.0f);
	pTexto->glPrint("Player Position: %f, %f, %f", pCamera->Position[0], pCamera->Position[1], pCamera->Position[2]);

	//// Imprime o FPS da aplicação e o Timer
	glRasterPos2f(10.0f, 80.0f);
	pTexto->glPrint("Frames-per-Second: %d ---- Timer: %.1f segundos", iFPS, (pTimer->GetTime()/1000));

	
	glPopMatrix();

	// Muda para modo de projeção perspectiva 3D
	PerspectiveMode();

	return true;
}




void CScene1::MouseMove(void) // Tratamento de movimento do mouse
{
	// Realiza os cálculos de rotação da visão do Player (através das coordenadas
	// X do mouse.
	POINT mousePos;
	int middleX = WIDTH >> 1;
	int middleY = HEIGHT >> 1;

	GetCursorPos(&mousePos);

	if ((mousePos.x == middleX) && (mousePos.y == middleY)) return;

	SetCursorPos(middleX, middleY);

	fDeltaX = (float)((middleX - mousePos.x)) / 10;
	fDeltaY = (float)((middleY - mousePos.y)) / 10;

	// Rotaciona apenas a câmera
	pCamera->rotateGlob(-fDeltaX, 0.0f, 1.0f, 0.0f);
	pCamera->rotateLoc(-fDeltaY, 1.0f, 0.0f, 0.0f);
}

void CScene1::KeyPressed(void) // Tratamento de teclas pressionadas
{

	// Verifica se a tecla 'W' foi pressionada e move o Player para frente
	if (GetKeyState('W') & 0x80)
	{
		pCamera->moveGlob(pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);
	}
	// Verifica se a tecla 'S' foi pressionada e move o Player para tras
	else if (GetKeyState('S') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Forward[0], -pCamera->Forward[1], -pCamera->Forward[2]);
	}
	// Verifica se a tecla 'A' foi pressionada e move o Player para esquerda
	else if (GetKeyState('A') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Right[0], -pCamera->Right[1], -pCamera->Right[2]);
	}
	// Verifica se a tecla 'D' foi pressionada e move o Player para direira
	else if (GetKeyState('D') & 0x80)
	{
		pCamera->moveGlob(pCamera->Right[0], pCamera->Right[1], pCamera->Right[2]);
	}
	// Senão, interrompe movimento do Player
	else
	{
	}


	if (GetKeyState(VK_UP) & 0x80)
	{
		fPosZ -= fMovementFactor;
	}
	if (GetKeyState(VK_DOWN) & 0x80)
	{
		fPosZ += fMovementFactor;
	}
	if (GetKeyState(VK_LEFT) & 0x80)
	{
		fPosX -= fMovementFactor;
	}
	if (GetKeyState(VK_RIGHT) & 0x80)
	{
		fPosX += fMovementFactor;
	}
	if (GetKeyState(VK_PRIOR) & 0x80)
	{
		fPosY += fMovementFactor;
	}
	if (GetKeyState(VK_NEXT) & 0x80)
	{
		fPosY -= fMovementFactor;
	}

	
	
}

void CScene1::KeyDownPressed(WPARAM	wParam) // Tratamento de teclas pressionadas
{
	switch (wParam)
	{
	case VK_TAB:
		bIsWireframe = !bIsWireframe;
		break;

	case VK_SPACE:
	{
		pTimer->Init();
	}
		break;

	case VK_RETURN:

		break;


	}

}

//	Cria um grid horizontal ao longo dos eixos X e Z
void CScene1::Draw3DSGrid(float width, float length)
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0f, 0.3f, 0.0f);
	glPushMatrix();
	for (float i = -width; i <= length; i += 1)
	{
		for (float j = -width; j <= length; j += 1)
		{
			// inicia o desenho das linhas
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(i, 0.0f, j + 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(i + 1, 0.0f, j + 1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(i + 1, 0.0f, j);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(i, 0.0f, j);
			glEnd();
		}
	}
	glPopMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void CScene1::DrawCube(float pX, float pY, float pZ,
	float rX, float rY, float rZ, float angle,
	float sX, float sY, float sZ,
	int texID)
{

	// Seta a textura ativa
	if (texID >= 0)
		pTextures->ApplyTexture(texID);

	glPushMatrix();
	glTranslatef(pX, pY, pZ);
	glRotatef(angle, rX, rY, rZ);
	glScalef(sX, sY, sZ);

	glBegin(GL_QUADS);
	// face frente
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f, 0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f, 0.5f);

	// face trás
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	
	// face direita
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);

	// face esquerda
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

	// face baixo
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f( 0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f( 0.5f, -0.5f,  0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.5f);

	// face cima
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f,  0.5f,  0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f, -0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f,  0.5f,  -0.5f);

	glEnd();

	glPopMatrix();
}


void CScene1::DrawAxis()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	// Eixo X
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1000.0f, 0.0f, 0.0f);
	glVertex3f(1000.0f, 0.0f, 0.0f);

	// Eixo Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1000.0f, 0.0f);
	glVertex3f(0.0f, -1000.0f, 0.0f);

	// Eixo Z
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1000.0f);
	glVertex3f(0.0f, 0.0f, -1000.0f);
	glEnd();
	glPopMatrix();
}


void CScene1::CreateSkyBox(float x, float y, float z,
	float width, float height, float length,
	CTexture* pTextures)
{
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glPushMatrix();

	// Centraliza o Skybox em torno da posição especificada(x, y, z)
	x = x - width / 2;
	y = y - height / 2;
	z = z - length / 2;


	// Aplica a textura que representa a parte da frente do skybox (BACK map)
	pTextures->ApplyTexture(0);

	// Desenha face BACK do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (FRONT map)
	pTextures->ApplyTexture(1);

	// Desenha face FRONT do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (DOWN map)
	pTextures->ApplyTexture(2);

	// Desenha face BOTTOM do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (UP map)
	pTextures->ApplyTexture(3);

	// Desenha face TOP do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + height, z + length);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (LEFT map)
	pTextures->ApplyTexture(4);

	// Desenha face LEFT do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (RIGHT map)
	pTextures->ApplyTexture(5);

	// Desenha face RIGHT do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();

	glPopMatrix();
}


