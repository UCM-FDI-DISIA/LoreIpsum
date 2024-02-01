//
// Activa la comprobación de fugas de memoria de Visual C++
//
// Esta cabecera solo tiene efecto en Windows. En Linux o macOS
// añade -fsanitize=address a la línea de comandos del compilador
// para comprobar las fugas.
//

#ifndef CHECKML_H
#define CHECKML_H

#if defined(_WIN32) && defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#if defined(_MSC_VER) && !defined(DBG_NEW)
#define DBG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DBG_NEW
#endif

// El siguiente código activa el análisis de las fugas de memoria al finalizar
// el programa. Utiliza variables inline, una novedad de C++17, que no está
// disponible en versiones antiguas de Visual Studio (anteriores a VS 2017).
// En tal caso se ha de comentar la línea que empieza por inline y llamar a
// la función _CrtSetDbgFlag manualmente en el main.

class crt_leak_setflag_dummy {
	struct constructor {
		constructor() {
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		}
	};
	static constructor ctor;
};
inline crt_leak_setflag_dummy::constructor crt_leak_setflag_dummy::ctor;

#endif

#endif // CHECKML_H
