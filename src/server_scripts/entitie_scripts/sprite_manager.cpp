
#include<string>

class TextureManager{
private:
    //preperation
    TextureManager(){}
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    
public:
    //get only instance
    static TextureManager& getOnlyInstance(){
        static TextureManager instance;
        return instance;
    }

};