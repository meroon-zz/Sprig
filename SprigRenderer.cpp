#include "SprigRenderer.h"
#include <iostream>
#include "Constants.h"

#include <OpenGLES/ES1/gl.h>
#include <cmath>
#include "MathUtil.h"

using std::cout;
using std::endl;

void Renderer::Setup(Rectangle rect, CameraType cameraType)
{
	_viewRect = rect;
	
    glViewport(0,0,_viewRect.width,_viewRect.height);
    
    if(cameraType == Renderer::Orthographic)
    {
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrthof(_viewRect.x,_viewRect.width,_viewRect.y,_viewRect.height,kZNear,kZFar);
        glMatrixMode(GL_MODELVIEW);
    }
    else
    {
        GLfloat size = kZNear * tanf(DegreesToRadians(kFieldOfView) / 2.0); 
        
        glEnable(GL_DEPTH_TEST);
        
        glMatrixMode(GL_PROJECTION); 
        glLoadIdentity();
        glFrustumf(-size, size, -size / (_viewRect.width / _viewRect.height), size / (_viewRect.width / _viewRect.height), kZNear, kZFar); 
        glMatrixMode(GL_MODELVIEW);
    }
    
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_ONE, GL_SRC_COLOR);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);	
}

void Renderer::Clear()
{
    glLoadIdentity();
    
	glClearColor(backgroundColor.red, backgroundColor.green, backgroundColor.blue, backgroundColor.alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::DrawRect(Rectangle rect, Color color)
{
    GLfloat vertices[] = {
        rect.x,  _viewRect.height - rect.y, -0.0,
        rect.x,  _viewRect.height - (rect.y + rect.height), -0.0,
        rect.x + rect.width, _viewRect.height - rect.y, -0.0,
        rect.x + rect.width, _viewRect.height - (rect.y + rect.height), -0.0
    };
    
    glPushMatrix();
    glEnableClientState(GL_VERTEX_ARRAY);
    glTranslatef(0.0, 0.0, -3.0);
    
    glColor4f(color.red, color.green, color.blue, color.alpha);
    
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
}


void Renderer::PushMatrix()
{
    glPushMatrix();
}

void Renderer::PopMatrix()
{
    glPopMatrix();
}

void Renderer::Translate(GLfloat x, GLfloat y, GLfloat z)
{
    glTranslatef(x, y, z);
}

void Renderer::setVertexColor(Color color)
{
    glColor4f(color.red, color.green, color.blue, color.alpha);
}

void Renderer::DrawMesh(Mesh &mesh)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    
    GLfloat *vertices = new GLfloat[mesh.vertices.size() * 3];
    int bufferIndex = 0;
    
    //printf("vertex count: %lu\n", mesh.vertices.size());
    
    for(int i = 0; i < mesh.vertices.size(); ++i)
    {
        bufferIndex = i * 3;
        
        Vector3 *vertex = mesh.vertices[i];
        
        vertices[bufferIndex] = vertex->x;
        vertices[bufferIndex + 1] = vertex->y;
        vertices[bufferIndex + 2] = vertex->z;
        
        printf("Vertex %d: ", i);
        vertex->Print();
    }
    
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    
    delete vertices;
}

void Renderer::DrawTexture(Rectangle& rect, Texture &texture)
{	    
    GLfloat vertices[] = {
        rect.x,  _viewRect.height - rect.y, 0.0,
        rect.x + rect.width, _viewRect.height - rect.y, 0.0,
        rect.x,  _viewRect.height - (rect.y + rect.height), 0.0,    
        rect.x + rect.width, _viewRect.height - (rect.y + rect.height), 0.0
    };
    
    static const GLfloat normals[] = {
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0
    };
    
	static const GLfloat texCoors[] =
    {
        0.0, 1.0,
        1.0, 1.0,
        0.0, 0.0,
        1.0, 0.0
    };
    
	
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -50.0);
	
    glBindTexture(GL_TEXTURE_2D, texture.textureID);
    
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normals);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoors);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}


