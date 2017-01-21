//
//  Entity.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 8/3/15.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "Entity.h"

Entity::Entity() : m_fStateTime(0.0f), m_isRequestingDeletion(false), m_ID(getUniqueEntityID())
{
    // Empty
}

void Entity::update(float deltaTime)
{
    m_fStateTime += deltaTime;
}

void Entity::onDeletion()
{
    // Empty
}

int Entity::getID()
{
    return m_ID;
}

float Entity::getStateTime()
{
    return m_fStateTime;
}

void Entity::setStateTime(float stateTime)
{
    m_fStateTime = stateTime;
}

void Entity::requestDeletion()
{
    m_isRequestingDeletion = true;
}

bool Entity::isRequestingDeletion()
{
    return m_isRequestingDeletion;
}

int Entity::getUniqueEntityID()
{
    static int entityID = 0;
    
    return entityID++;
}

RTTI_IMPL_NOPARENT(Entity);
