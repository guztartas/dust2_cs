#pragma warning(disable:4996)

#include "CTexto.h"

CTexto::CTexto()
{
	this->BuildFont();
}


CTexto::~CTexto()
{
	this->KillFont();
}


void CTexto::BuildFont()
{

	HWND hWnd1 = FindWindow("OpenGL", "OpenGL Application");
	HDC hDC1 = GetDC(hWnd1); 

	HFONT font;		// Vari�vel para usar fontes do windows

	base = glGenLists(96);	// Cria 256 display list(uma lista para cada caracter da tabela ASCII)
	
	// Criando a fonte...
	font = CreateFont(-12,						// Altura da fonte (tem q ser negativo)
					    0,						// Largura da fonte (0 = default)
						0,						// Rota��o da fonte em graus (angulo de escape). Sempre 0
						0,						// Angulo de orienta��o. Sempre 0
						FW_BOLD,				// Espessura da fonte(FW_DONTCARE = 0 | FW_NORMAL = 400 | FW_BOLD = 700 | FW_BLACK = 900)
						FALSE,					// It�lico
						FALSE,					// Sobre-escrito
						FALSE,					// Sub-escrito
						ANSI_CHARSET,			// Tipo de caracter (Para fonte Webdings e Wingdings usar SYMBOL_CHARSET)
						OUT_TT_PRECIS,			// Se houver mais de uma fonte com o mesmo nome, usa a que for TRUETYPE
						CLIP_DEFAULT_PRECIS,	// Tipo de clipping usado na fonte (melhor deixar essa op��o default)
						ANTIALIASED_QUALITY,	// Qualidade da fonte na tela (essa � a melhor op��o)
						FF_DONTCARE | DEFAULT_PITCH,	// Familia que pertence a fonte: FF_DECORATIVE, FF_MODERN, FF_ROMAN, FF_SCRIPT, FF_SWISS   |   Pitch: FIXED_PITCH, VARIABLE_PITCH
						"Courier New");			// Nome da fonte a ser usada



	SelectObject(hDC1, font);					// Seleciona a fonte que foi criada

	wglUseFontBitmaps(hDC1, 32, 96, base);		// Cria 96 caracteres a partir do caracter 32 (espa�o em branco)

}






// Fun��o usada para deletar as lista de caracteres da mem�ria no final do programa
void CTexto::KillFont()
{
	glDeleteLists(base,   96);
}



// Fun��o que escreve o texto na tela
void CTexto::glPrint(const char *fmt, ...)
{

	char text[256];		// Armazena o texto

	va_list	ap;			// Ponteiro para lista de argumentos

	// Testa se h� algum texto para ser impresso
	if (fmt == NULL) return;


	// Converte simbolos no n�mero atual que representa o s�mbolo. O texto final e os 
	// s�mbolos s�o armazenados em TEXT
	va_start(ap, fmt);		// Passa a string para as vari�veis

		vsprintf(text, fmt, ap);	// Adiciona simbolos convertidos para seus valores atuais

	va_end(ap);				// O resultado � armazenado em text


	glPushAttrib(GL_LIST_BIT);	// Previne glBaseList para n�o afetar outras display Lists usadas no programa
	glListBase(base - 32);		// Localiza o caracter na tabela ASCII

	// Desenha na tela o texto contido na display list
	glCallLists(strlen(text),			// Analisa quantas letras ser�o impressas na tela
				GL_UNSIGNED_BYTE,		// Qual o n�mero m�ximo de caracteres (GL_UNSIGNED_BYTE = 0 at� 255)
				text);					// Vari�vel que cont�m o texto que ser� mostrado na tela

	glPopAttrib();

}

