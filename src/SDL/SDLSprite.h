#ifndef _SDLSPRITE_H
#define _SDLSPRITE_H

#include <SDL2/SDL.h>

//! \brief Pour gérer une image avec SDL2
class SDLSprite
{

private:
    SDL_Surface* m_surface;
    SDL_Texture* m_texture;
    bool m_hasChanged;

public:
    SDLSprite();
    ~SDLSprite();
    SDLSprite(const SDLSprite &im);
    SDLSprite &operator=(const SDLSprite &im);

    void loadFromFile(const char *filename, SDL_Renderer *renderer);
    void loadFromCurrentSurface(SDL_Renderer *renderer);
    void draw(SDL_Renderer *renderer, int x, int y, int w = -1, int h = -1);
    SDL_Texture* getTexture() const { return m_texture; }
    void setSurface(SDL_Surface *surf)  { if (m_surface!=nullptr) SDL_FreeSurface(m_surface); m_surface = surf; }
};

#endif

