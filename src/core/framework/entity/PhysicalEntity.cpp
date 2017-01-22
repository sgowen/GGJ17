//
//  PhysicalEntity.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "PhysicalEntity.h"

#include "macros.h"
#include "VectorUtil.h"

PhysicalEntity::PhysicalEntity(float x, float y, float width, float height) : Entity(),
m_position(x, y),
m_velocity(),
m_acceleration(),
m_fWidth(width),
m_fHeight(height),
m_fAngle(0)
{
    m_bounds.push_back(new NGRect(x - width / 2, y - height / 2, width, height));
}

PhysicalEntity::~PhysicalEntity()
{
    VectorUtil::cleanUpVectorOfPointers(m_bounds);
}

void PhysicalEntity::update(float deltaTime)
{
    Entity::update(deltaTime);
    
    m_velocity.add(m_acceleration.getX() * deltaTime, m_acceleration.getY() * deltaTime);
    m_position.add(m_velocity.getX() * deltaTime, m_velocity.getY() * deltaTime);
    
    updateBounds();
}

void PhysicalEntity::resetBounds(float width, float height)
{
    Vector2D &lowerLeft = m_bounds.at(0)->getLowerLeft();
    lowerLeft.set(m_position.getX() - width / 2, m_position.getY() - height / 2);
    m_bounds.at(0)->setWidth(width);
    m_bounds.at(0)->setHeight(height);
}

void PhysicalEntity::updateBounds()
{
    Vector2D &lowerLeft = m_bounds.at(0)->getLowerLeft();
    lowerLeft.set(m_position.getX() - m_bounds.at(0)->getWidth() / 2, m_position.getY() - m_bounds.at(0)->getHeight() / 2);
}

void PhysicalEntity::placeOn(float itemTopY)
{
	getPosition().setY(itemTopY + getMainBounds().getHeight() / 2 * .99f);

	updateBounds();
}

Vector2D& PhysicalEntity::getPosition()
{
    return m_position;
}

Vector2D& PhysicalEntity::getVelocity()
{
    return m_velocity;
}

Vector2D& PhysicalEntity::getAcceleration()
{
    return m_acceleration;
}

std::vector<NGRect*>& PhysicalEntity::getBounds()
{
    return m_bounds;
}

NGRect& PhysicalEntity::getMainBounds()
{
    return *m_bounds.at(0);
}

const float& PhysicalEntity::getWidth()
{
    return m_fWidth;
}

void PhysicalEntity::setWidth(float width)
{
    m_fWidth = width;
}

const float& PhysicalEntity::getHeight()
{
    return m_fHeight;
}

void PhysicalEntity::setHeight(float height)
{
    m_fHeight = height;
}

float PhysicalEntity::getAngle()
{
    return m_fAngle;
}

RTTI_IMPL(PhysicalEntity, Entity);
