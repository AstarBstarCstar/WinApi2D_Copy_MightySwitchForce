#pragma once

class CTexture;

class CCore
{
	SINGLETON(CCore);
	

public:
	bool g_isRendering;
	void update();
	void render();
	void init();
	void	SetRender(bool _render) { g_isRendering = _render; }
};

