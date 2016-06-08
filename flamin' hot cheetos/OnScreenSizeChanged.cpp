#include "OnScreenSizeChanged.h"

OnScreenSizeChanged_t originalOnScreenSizeChanged;

void __stdcall OnScreenSizeChanged(int nOldWidth, int nOldHeight)
{
	originalOnScreenSizeChanged(interfaces::surface, nOldWidth, nOldHeight);

	drawing.initializeFonts();
}