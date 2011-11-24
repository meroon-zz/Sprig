#include <string>

#include "SprigSprite.h"

using std::string;

Sprite::Sprite()
{
    _x = 0;
    _y = 0;
    _width = 100;
    _height = 100;
    
    /* 
     
     1 ------- 3
     |         |
     |         |
     |         |
     2 ------- 4
     
     */
    
    _mesh.AddVertex(0, 0, 0);
    _mesh.AddVertex(0, 0, 0);
    _mesh.AddVertex(0, 0, 0);
    _mesh.AddVertex(0, 0, 0);    
    
    _mesh.AddNormal(0, 0, 1);
    _mesh.AddNormal(0, 0, 1);
    _mesh.AddNormal(0, 0, 1);
    _mesh.AddNormal(0, 0, 1);
    
    _mesh.AddTextureCoor(0.0f, 1.0f);
    _mesh.AddTextureCoor(0.0f, 0.0f);
    _mesh.AddTextureCoor(1.0f, 1.0f);
    _mesh.AddTextureCoor(1.0f, 0.0f);
    
    
    calculateMesh();    
}

Sprite::~Sprite()
{
    
}

void Sprite::setPosition(float x, float y)
{
    _x = x;
    _y = y;
    
    calculateMesh();
}

void Sprite::setSize(float width, float height)
{
    _width = width;
    _height = height;
    
    calculateMesh();
}

void Sprite::calculateMesh()
{
    //unsigned int screenWidth = 320;
    unsigned int screenHeight = 480;
    
    
    //update the vertex data
    _mesh.vertices[0]->x = _x;
    _mesh.vertices[0]->y = screenHeight - _y;
    _mesh.vertices[1]->x = _x;
    _mesh.vertices[1]->y = screenHeight - (_y + _height);
    _mesh.vertices[2]->x = _x + _width;
    _mesh.vertices[2]->y = screenHeight - _y;
    _mesh.vertices[3]->x = _x + _width;
    _mesh.vertices[3]->y = screenHeight - (_y + _height);
}

void Sprite::AddBitmap(Bitmap &bitmap)
{
    Texture texture = Texture(bitmap);
    _texture.Apply(texture);
}


void Sprite::Update()
{
    
}





/*-----------------------------------------------------------*/
// AnimatedSprite



void AnimatedSprite::LoadSheet(string &xmlPath, string &imagePath)
{
    if(_atlas.LoadSheet(xmlPath.c_str()))
    {
        Bitmap newSheet = Bitmap(imagePath);
        AddBitmap(newSheet);
    }
}

void AnimatedSprite::GotoFrame(int frame)
{
    _atlas.setRectIndex(frame - 1);
    
    calculateTexCoor(*_atlas.CurrentRect());
}

unsigned int AnimatedSprite::CurrentFrame()
{
    return 1;
}

void AnimatedSprite::Update()
{
    Rectangle *clipRect = _atlas.NextRect();
 
    calculateTexCoor(*clipRect);
}

void AnimatedSprite::calculateTexCoor(Rectangle &clipRect)
{
    _mesh.textureCoor[0]->x = clipRect.x / (float)_texture.GetWidth();
    _mesh.textureCoor[0]->y = clipRect.y / (float)_texture.GetHeight();
    
    _mesh.textureCoor[1]->x = clipRect.x / (float)_texture.GetWidth();
    _mesh.textureCoor[1]->y = (clipRect.y + clipRect.height) / (float)_texture.GetHeight();
    
    _mesh.textureCoor[2]->x = (clipRect.x + clipRect.width) / (float)_texture.GetWidth();
    _mesh.textureCoor[2]->y = clipRect.y / (float)_texture.GetHeight();
    
    _mesh.textureCoor[3]->x = (clipRect.x + clipRect.width) / (float)_texture.GetWidth();
    _mesh.textureCoor[3]->y = (clipRect.y + clipRect.height) / (float)_texture.GetHeight();
    
    
    float diffX = _width - clipRect.width;
    //float diffY = _height - clipRect.height;
    
    setPosition(_x + diffX / 2, _y);
    setSize(clipRect.width, clipRect.height);
    
    
    //    printf("-- UPDATE -----\n\n");
    //    
    //    printf("[%d, %d]\n", _texture.GetWidth(), _texture.GetHeight());
    //    
    //    clipRect.Print();
    //    
    //    for(int i = 0; i < 4; i++)
    //    {
    //        printf("coor %d [%f, %f]", i, _mesh.textureCoor[i]->x, _mesh.textureCoor[i]->y);
    //    }
    //    
    //    
    //    printf("\n\n");
}