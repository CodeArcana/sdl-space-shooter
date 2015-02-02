/*******************************************************************//*
 * Physics component for PlayerInstructions.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-01
 * @modified    2015-02-01
 *********************************************************************/
#ifndef SPACESHOOTER_PLAYERINSTRUCTIONSPHYSICSCOMPONENTCOMPONENT_
    #define SPACESHOOTER_PLAYERINSTRUCTIONSPHYSICSCOMPONENTCOMPONENT_

#include "PhysicsComponent.h"
#include <SDL2/SDL.h>
#include "Timer.h"
#include "Vector2D.h"

class GameEntity;
class GameEntityManager;
class RenderComponent;

struct WindowElements;

class PlayerInstructionsPhysicsComponent : public PhysicsComponent
{
    private:
        GameEntityManager* gameEntityManager;

        RenderComponent* render;
        Timer timeBasedMovementTimer;
        Timer projectileCapTimer;

        int xGrid;
        int yGrid;
        int xMin;
        int yMin;
        int xMax;
        int yMax;

    public:
        Vector2D velocity;
        int velocityPerSecond;
        bool shooting;

        //Constructor
        PlayerInstructionsPhysicsComponent(GameEntity* gameEntity, WindowElements* windowElements,
                                GameEntityManager* gameEntityManager);

        //Destructor
        ~PlayerInstructionsPhysicsComponent();

        //Methods
        void update();
        void pauseTimers();
        void resumeTimers();
        void onDestroy();
};

#endif