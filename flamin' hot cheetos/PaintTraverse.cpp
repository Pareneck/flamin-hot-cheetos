#include "PaintTraverse.h"

void __stdcall PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
	// call original function

	const char* pszPanel = g_pPanel->GetName(vguiPanel);
	if (!pszPanel)
		return;

	// MatSystemTopPanel
	if (pszPanel[0] == 'M' && pszPanel[3] == 'S' && pszPanel[9] == 'T')
	{
		// draw shit
	}
}