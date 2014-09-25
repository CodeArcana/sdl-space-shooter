/*******************************************************************//*
 * Implementation of the PlayerPhysicsComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-06
 * @modified    2014-09-25
 *********************************************************************/
#include "PlayerPhysicsComponent.h"

#include "GameEntity.h"
#include "GameEntityManager.h"
#include "RenderComponent.h"
#include "WindowElements.h"

PlayerPhysicsComponent::PlayerPhysicsComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements,
                                            GameEntityManager* gameEntityManager)
:   gameEntityManager(gameEntityManager), render(NULL),
    velocity(0, 0), velocityPerSecond(500), shooting(false)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;
    render = gameEntity->getRenderComponent();
}

PlayerPhysicsComponent::~PlayerPhysicsComponent()
{
    gameEntityManager->createExplosion(gameEntity);
}

void PlayerPhysicsComponent::update()
{
	float timeSinceLastFrame = timeBasedMovementTimer.getTimeOnTimer() / 1000.f;
    //x = x + speedPerSeconds*secondsSinceLastFrame
    //gameEntity->xPos += (xVel * timeSinceLastFrame);
    gameEntity->position += velocity*timeSinceLastFrame;

    if (gameEntity->position.x > windowElements->WINDOW_WIDTH)
    {
        gameEntity->position.x = windowElements->WINDOW_WIDTH;
    }
    else if (gameEntity->position.x < 0)
    {
        gameEntity->position.x = 0;
    }

    //y = y + speedPerSeconds*secondsSinceLastFrame
    //gameEntity->yPos += (yVel * timeSinceLastFrame);
    if (gameEntity->position.y > windowElements->WINDOW_HEIGHT - render->spriteHeight/2)
    {
        gameEntity->position.y = windowElements->WINDOW_HEIGHT - render->spriteHeight/2;
    }
    else if (gameEntity->position.y < 0 + render->spriteHeight/2)
    {
        gameEntity->position.y = 0 + render->spriteHeight/2;
    }
    timeBasedMovementTimer.stop();
    timeBasedMovementTimer.start();

    if (shooting)
    {
        if (projectileCapTimer.isStarted())
        {
            if (projectileCapTimer.getTimeOnTimer()>150)
            {
                gameEntityManager->createPlayerProjectile(gameEntity);
                projectileCapTimer.stop();
            }
        }
        else
        {
            gameEntityManager->createPlayerProjectile(gameEntity);
        }
        projectileCapTimer.start();
    }
}

void PlayerPhysicsComponent::pauseTimers()
{
    timeBasedMovementTimer.pause();
    projectileCapTimer.pause();
}

void PlayerPhysicsComponent::resumeTimers()
{
    timeBasedMovementTimer.resume();
    projectileCapTimer.resume();
}
