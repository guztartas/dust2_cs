#pragma once

#include <windows.h>	// Header File For Windows
#include <stdio.h>
#include <stdarg.h>
#include <gl.h>			// Header File For The OpenGL32 Library

class CTexto
{
public:

	CTexto();
	~CTexto();


	// Fun��o que escreve o texto na tela
	void glPrint(const char *fmt, ...);

private:

	// Fun��o que cria a fonte
	void BuildFont();

	// Fun��o usada para deletar as lista de caracteres da mem�ria no final do programa
	void KillFont(void);

	int base;				// Display List BASE para armazenar o texto

};
