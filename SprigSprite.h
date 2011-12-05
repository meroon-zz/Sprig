#include <string>

#include "SprigEntity.h"
#include "SprigBitmap.h"
#include "SprigSpriteAtlas.h"

using std::string;

class Sprite : public Entity
{
    
public:
    
    Sprite();
    virtual ~Sprite();

    virtual void Update();
    
    void setPosition(float x, float y);
    void setSize(float width, float height);
    void AddBitmap(Bitmap &bitmap);
    
    float _x;
    float _y;
    
protected:
    
    void calculateMesh();
    
    unsigned int _width;
    unsigned int _height;
    
    
};

class AnimatedSprite : public Sprite
{
  
public: 
    
    void Update();
    void LoadSheet(string &xmlPath, string &imagePath);
    void GotoFrame(int frame);
    unsigned int CurrentFrame();
    
private:
    
    void calculateTexCoor(Rectangle &clipRect);
    
    SpriteAtlas _atlas;
    
    
};