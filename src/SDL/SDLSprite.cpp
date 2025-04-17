#include "SDLSprite.h"

using namespace std;

SDLSprite::SDLSprite() : m_surface(nullptr), m_texture(nullptr), m_hasChanged(false)
{
}

SDLSprite::~SDLSprite()
{
    if (m_surface) SDL_FreeSurface(m_surface);
    if (m_texture) SDL_DestroyTexture(m_texture);

    m_surface = nullptr;
    m_texture = nullptr;
    m_hasChanged = false;
}

SDL_Texture* SDLSprite::getTexture() const { 
    return m_texture; }

void SDLSprite::setSurface(SDL_Surface *surf)  { 
    if (m_surface!=nullptr) SDL_FreeSurface(m_surface); m_surface = surf; }

void SDLSprite::loadFromFile(const char *filename, SDL_Renderer *renderer)
{
    m_surface = IMG_Load(filename);
    if (m_surface == nullptr)
    {
        cout << "Error: cannot load " << filename << endl;
        SDL_Quit();
        exit(1);
    }

    SDL_Surface *surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(m_surface, SDL_PIXELFORMAT_ARGB8888, 0);
    SDL_FreeSurface(m_surface);
    m_surface = surfaceCorrectPixelFormat;

    m_texture = SDL_CreateTextureFromSurface(renderer, surfaceCorrectPixelFormat);
    if (m_texture == NULL)
    {
        cout << "Error: problem to create the texture of " << filename << endl;
        SDL_Quit();
        exit(1);
    }
}

void SDLSprite::loadFromCurrentSurface(SDL_Renderer *renderer)
{
    m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
    if (m_texture == nullptr)
    {
        cout << "Error: problem to create the texture from surface " << endl;
        SDL_Quit();
        exit(1);
    }
}

void SDLSprite::draw(SDL_Renderer *renderer, int x, int y, int w, int h)
{
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w < 0) ? m_surface->w : w;
    r.h = (h < 0) ? m_surface->h : h;

    if (m_hasChanged)
    {
        if (SDL_UpdateTexture(m_texture, nullptr, m_surface->pixels, m_surface->pitch) != 0)
        {
            std::cerr << "Erreur SDL_UpdateTexture: " << SDL_GetError() << std::endl;
            return;
        }
        m_hasChanged = false;
    }

    if (SDL_RenderCopy(renderer, m_texture, nullptr, &r) != 0)
    {
        std::cerr << "Erreur SDL_RenderCopy: " << SDL_GetError() << std::endl;
        return;
    }

}

