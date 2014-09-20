/*******************************************************************//*
 * Interface containing one method that all render components must
 * implement
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-17
 * @modified    2014-09-19
 *********************************************************************/
#ifndef SPACESHOOTER_RENDERCOMPONENT_
    #define SPACESHOOTER_RENDERCOMPONENT_

#include <SDL2/SDL.h>

class GameEntity;

struct WindowElements;

class RenderComponent
{
    public:
        //Fields
        SDL_Rect renderRect;
        SDL_Texture* sprite;
        int spriteWidth;
        int spriteHeight;

        //Destructor
        virtual ~RenderComponent(){};

        //Methods
        virtual void update() = 0;

    protected:
        GameEntity* gameEntity;
        WindowElements* windowElements;
};

#endif
