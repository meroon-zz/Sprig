#pragma once

#include "Rectangle.h"
#include "Color.h"
#include "Texture.h"

class Renderer  {

public:	
	
	enum CameraType {
		Orthographic, Perspective
	};
	
	void Setup(Rectangle rect, CameraType cameraType);
	void Clear();
    
    void DrawRect(Rectangle rect, Color color);
    void DrawTexture(int x, int y, Texture &texture, int mainWidth, int mainHeight);
    
    Color backgroundColor;
	
private:
    
	Rectangle _viewRect;
};