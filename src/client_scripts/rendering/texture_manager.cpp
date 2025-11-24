#include<SDL3_image/SDL_image.h>
#include<SDL3/SDL.h>
#include<unordered_map>
#include<string>

class TextureManager{
private:
    //preperation
    TextureManager(){}
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    SDL_Renderer *sdl_renderer;
    std::unordered_map<std::string, SDL_Texture*> texture_map;
public:
    //get only instance
    static TextureManager& getOnlyInstance(){
        static TextureManager instance;
        return instance;
    }

    /*this function should only be called once on the rendering script*/
    void initialize(SDL_Renderer * renderer){
        sdl_renderer = renderer;
    }

    /*get a texture, if texture not exsist, load it in and store it in the unordered_map*/
    SDL_Texture* getTexture(const char* texture_dir){
        std::string dir_str = texture_dir;

        SDL_Texture *texture_temp = texture_map[dir_str];
        if(texture_temp == nullptr){
            texture_temp = IMG_LoadTexture(sdl_renderer, texture_dir);
            if (!texture_temp){SDL_Log("IMG_LoadTexture error:");}
            texture_map[dir_str] = texture_temp;
        }

        return texture_temp;
    }

};