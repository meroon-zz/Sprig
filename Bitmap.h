#include <string>

class Bitmap {
    
    
    public:
    
        Bitmap(unsigned int width, unsigned int height, bool transparent);
        Bitmap(const std::string& filepath); 
        
        
        Bitmap();
        ~Bitmap();
        
        char * getBitmapData();
    
        bool isLoaded();
    
        void fill(unsigned int color);
        
    
    private:
    
        bool loadPNG(const std::string& filepath);
        void createEmpty(unsigned int width, unsigned int height);
        void setTransparency(bool transparent);
    
        unsigned int _pixelSize;
        char *_bitmapData;
        unsigned int _width;
        unsigned int _height;
        bool _transparent;
        bool _loaded;
    
};