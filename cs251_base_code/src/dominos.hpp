/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 251 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * 
 */

#ifndef _DOMINOS_HPP_
#define _DOMINOS_HPP_

namespace cs251
{
  //! This is the class that sets up the Box2D simulation world
  //! Notice the public inheritance - why do we inherit the base_sim_t class?
  class dominos_t : public base_sim_t
  {
  public:
    
    dominos_t();
    
    static base_sim_t* create()
    {
      return new dominos_t;
    }
   
	class QueryCallback : public b2QueryCallback
	{
	public:
	    b2Vec2 m_point;
	    b2Fixture* m_fixture;
	    QueryCallback(const b2Vec2& point)
	    {
		m_point = point;
		m_fixture = NULL;

	    }

	    bool ReportFixture(b2Fixture* fixture)
	    {
		b2Body* body = fixture->GetBody();
		if (body->GetType() == b2_dynamicBody)

		{

		    bool inside = fixture->TestPoint(m_point);
		    if (inside)
		    {
			m_fixture = fixture;

			// We are done, terminate the query.
			return false;
		    }
		}

		// Continue the query.
		return true;
	    }


	};


    
b2MouseJoint* _mouseJoint;
b2Vec2 _worldPosition;
b2Body* b1;

bool mouse_down(const b2Vec2& p) 
    { ////B2_NOT_USED(p);
	   _worldPosition = p;

	    if (_mouseJoint != NULL)
	    {
		return false;
	    }


	    b2AABB aabb;
	    b2Vec2 d;
	    d.Set(1.0f/0.5, 1.0f/0.5);
	    aabb.lowerBound = p - d;
	    aabb.upperBound = p + d;
	    QueryCallback callback(p);
	    
		m_world->QueryAABB(&callback, aabb);

	    if (callback.m_fixture) {

		b2Body* body = callback.m_fixture->GetBody();
		b2MouseJointDef md;
		md.bodyA = b1;
		md.bodyB = body;
		md.target = p;
		md.maxForce = 1000.0f * body->GetMass();
		_mouseJoint = (b2MouseJoint*)m_world->CreateJoint(&md);
		body->SetAwake(true);
		return true;

	    }


	    return false;
	    }

void mouse_up(const b2Vec2& p) 
	{ //B2_NOT_USED(p); 
		if (_mouseJoint)
	    {
		m_world->DestroyJoint(_mouseJoint);
		_mouseJoint = NULL;
	    }
	}

void mouse_move(const b2Vec2& p) 
	{ 
		_worldPosition = p;
	    if (_mouseJoint)
	    {
		_mouseJoint->SetTarget(p);
	    }
		    
	}
   };
}
  
#endif
