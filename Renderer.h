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
    void DrawTexture(Rectangle& rect, Texture &texture); //renders a texture with clipping
    
    Color backgroundColor;
	
private:
    
	Rectangle _viewRect;
};