#include "PaintTraverse.h"

tPaintTraverse g_fnPaintTraverse = nullptr;

void __stdcall PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
	g_fnPaintTraverse(g_pPanel, vguiPanel, forceRepaint, allowForce);

	if (GetAsyncKeyState(VK_DELETE) & 1)
		bUnload = true;

	static bool bOnce = false;
	if (!bOnce)
	{
		g_Drawing.InitializeFonts();
		bOnce = true;
	}

	const char* pcPanel = g_pPanel->GetName(vguiPanel);
	if (!pcPanel)
		return;

	// MatSystemTopPanel
	if (pcPanel[0] == 'M' && pcPanel[3] == 'S' && pcPanel[9] == 'T')
	{
		g_Drawing.DrawString(g_Drawing.m_ESPFont, false, 3, 3, 255, 255, 255, 255, "flamin' hot cheetos");
	}
}