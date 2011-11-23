#include <string>

#include "SprigGameObject.h"
#include "SprigBitmap.h"
#include "SprigSpriteAtlas.h"

using std::string;

class Sprite : public GameObject
{
    
public:
    
    Sprite();
    virtual ~Sprite();

    virtual void Update();
    
    void setPosition(float x, float y);
    void setSize(float width, float height);
    void AddBitmap(Bitmap &bitmap);
    
protected:
    
    void calculateMesh();
    
    unsigned int _width;
    unsigned int _height;
    
    float _x;
    float _y;
};

class AnimatedSprite : public Sprite
{
  
public: 
    
    void Update();
    void LoadSheet(string &xmlPath, string &imagePath);
    
private:
    
    SpriteAtlas _atlas;
    
};