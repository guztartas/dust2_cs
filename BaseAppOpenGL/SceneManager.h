#pragma once
#include "SceneBaseClass.h"		// Classe Base
#include "Scene1.h"
#include "Scene2.h"


class CSceneManager : public CSceneBaseClass
{
public:
	CSceneManager(int l, int a);
	virtual ~CSceneManager(void);

	virtual void MouseMove(void); // Tratamento de movimento do mouse
	virtual void KeyPressed(void); // Tratamento de teclas pressionadas
	virtual void KeyDownPressed(WPARAM	wParam);	// Tratamento de teclas pressionadas
	virtual int DrawGLScene(void);	// Função que desenha a cena
	void ChangeScene(unsigned int _uiCurrentScene);

	void ReSizeGLScene(int width, int height); // Redimensiona e inicial a janela OpenGL

	void InitIL(void);
	void DeInitIL();

	void InitGLEW(void);
	void DeInitGLEW();

private:
	bool InitGL(void); // Configurações iniciais OpenGL (pré-render)
	void DeInitGL(void); // Destrói todos os gerenciadores alocados em InitGL() 

	// Ponteiro para cenas do jogo
	CSceneBaseClass* Scene;

	// ID da cena
	unsigned int uiCurrentScene;
};

