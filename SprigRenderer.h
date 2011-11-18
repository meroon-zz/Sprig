#pragma once

#include "SprigRectangle.h"
#include "SprigColor.h"
#include "SprigTexture.h"
#include "SprigMesh.h"

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
	
    void PushMatrix();
    void PopMatrix();
    
    void Translate(GLfloat x, GLfloat y, GLfloat z);
    
    void setVertexColor(Color color);
    
    void DrawMesh(Mesh& mesh);
    
private:
    
	Rectangle _viewRect;
};