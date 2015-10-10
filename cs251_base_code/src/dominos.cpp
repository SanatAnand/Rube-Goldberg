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


#include "cs251_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif
//#include<settings>
#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs251
{
	/**  The is the constructor
	* This is the documentation block for the constructor.
	*/
	
	dominos_t::dominos_t()
	{
		//Ground
		/*! \var b1
		* \brief pointer to the body ground
		*/
		//b2Body* b1;
		{
			
			b2EdgeShape shape;
			shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
			b2BodyDef bd;
			b1 = m_world->CreateBody(&bd);
			b1->CreateFixture(&shape, 0.0f);
		}
		
		//Top horizontal shelf
		{
			b2PolygonShape shape;
			shape.SetAsBox(6.0f, 0.25f);
			
			b2BodyDef bd;
			bd.position.Set(-31.0f, 30.0f);
			b2Body* ground = m_world->CreateBody(&bd);
			ground->SetTransform( ground->GetPosition(), 0 );
			ground->CreateFixture(&shape, 0.0f);
		}
		
		//Top Control Gate Left Wall
		{
			b2PolygonShape shapeleft;
			shapeleft.SetAsBox(0.5f, 6.0f);
			
			b2BodyDef bd2;
			bd2.position.Set(-37.5f, 36.4f);
			b2Body* ground2 = m_world->CreateBody(&bd2);
			ground2->CreateFixture(&shapeleft, 0.0f);
		}		

		//Top Control Gate Right
		{	
			b2PolygonShape shaperight;
			shaperight.SetAsBox(1.0f, 6.0f);
			
			b2BodyDef bd;
			bd.type = b2_dynamicBody;				
			bd.position.Set(-27.7f, 36.0f);
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&shaperight, 0.0f);
			
		}
		
		//Sliding Pipe Bottom
		{
			b2EdgeShape shape;
			shape.Set(b2Vec2(-26.0f, 30.0f), b2Vec2(-18.0f, 20.0f));
			b2BodyDef bd;
			b1 = m_world->CreateBody(&bd);
			b1->CreateFixture(&shape, 0.0f);
	
		}
		
		//Sliding Pipe Upper
		{
			b2EdgeShape shape;
			shape.Set(b2Vec2(-26.0f, 36.0f), b2Vec2(-18.0f, 26.0f));
			b2BodyDef bd;
			b1 = m_world->CreateBody(&bd);
			b1->CreateFixture(&shape, 0.0f);
	
		}
		//Sliding Pipe Vertical Cover
		{
			b2EdgeShape shape;
			shape.Set(b2Vec2(-26.0f, 36.0f), b2Vec2(-26.0f, 50.0f));
			b2BodyDef bd;
			b1 = m_world->CreateBody(&bd);
			b1->CreateFixture(&shape, 0.0f);
	
		}

		//Turbine
		{	
			int rad=1.5;
			b2CircleShape circle;
			circle.m_radius = rad;
			
			b2BodyDef bd;
		        bd.position.Set(-10.0f, 15.0f);
			bd.type = b2_dynamicBody;
		        b2Body* ground = m_world->CreateBody(&bd);
			b2FixtureDef *fd = new b2FixtureDef;
			fd->density = 100000.0f;
			fd->shape = new b2PolygonShape;
			fd->shape = &circle;
		        ground->CreateFixture(&circle, 0.0f);
			
			b2PolygonShape horizontal;
			horizontal.SetAsBox(4.0f + 2* rad, 0.2f );
			b2FixtureDef *fd2 = new b2FixtureDef;
			fd2->density = 100000.0f;
			fd2->shape = new b2PolygonShape;
			fd2->shape = &horizontal;
			
			b2PolygonShape vertical;
			vertical.SetAsBox(0.2f , 4.0f + 2* rad);
			b2FixtureDef *fd3 = new b2FixtureDef;
			fd3->density = 100000.0f;
			fd3->shape = new b2PolygonShape;
			fd3->shape = &vertical;

			b2PolygonShape inclinedleft;
			inclinedleft.SetAsBox(4.0f + 2*rad, 0.2f, b2Vec2(0.0, 0.0), (3.1412)/4);
			b2FixtureDef *fd4 = new b2FixtureDef;
			fd4->density = 100000.0f;
			fd4->shape = new b2PolygonShape;
			fd4->shape = &inclinedleft;
		
			b2PolygonShape inclinedright;
			inclinedright.SetAsBox(4.0f + 2*rad, 0.2f, b2Vec2(0.0, 0.0), -(3.1412)/4);
			b2FixtureDef *fd5 = new b2FixtureDef;
			fd5->density = 100000.0f;
			fd5->shape = new b2PolygonShape;
			fd5->shape = &inclinedright;

			ground->CreateFixture(fd4);		
			ground->CreateFixture(fd2);
			ground->CreateFixture(fd3);
			ground->CreateFixture(fd5);

			b2PolygonShape shape2;
			shape2.SetAsBox(2.0f, 2.0f);
			b2BodyDef bd2;
			bd2.position.Set(-10.0f, 17.0f);
			b2Body* body2 = m_world->CreateBody(&bd2);

			b2RevoluteJointDef jointDef;
			jointDef.bodyA = ground;
			jointDef.bodyB = body2;
			jointDef.localAnchorA.Set(0,0);
			jointDef.localAnchorB.Set(0,0);
			jointDef.collideConnected = true;
			m_world->CreateJoint(&jointDef);					
		
			//Pulley System
			{
				//bar				
				b2BodyDef *bd = new b2BodyDef;
				bd->type = b2_dynamicBody;
				//bd->position.Set(10,8);
				bd->position.Set(10,20);
				bd->fixedRotation = true;
				b2FixtureDef *fd1 = new b2FixtureDef;
				fd1->friction = 1.5;
				fd1->restitution = 0.f;
				fd1->shape = new b2PolygonShape;				
				b2PolygonShape shape;	
				shape.SetAsBox(1.0f, 2.5f);				
				fd1->shape = &shape;
				//bd->position.Set(10,15);
				fd1->density = 94000.0f;
				b2Body* box2 = m_world->CreateBody(bd);
				box2->CreateFixture(fd1);
			
				// The pulley joint
				b2PulleyJointDef* myjoint = new b2PulleyJointDef();
				b2Vec2 worldAnchorOnBody1(-10, 30); // Anchor point on body 1 in world axis
				b2Vec2 worldAnchorOnBody2(10, 30); // Anchor point on body 2 in world axis
				b2Vec2 worldAnchorGround1(-10, 30); // Anchor point for ground 1 in world axis
				b2Vec2 worldAnchorGround2(10, 30); // Anchor point for ground 2 in world axis
				b2Vec2 rightAnchorPoint(-10, 16.0);//Right Anchor Point
				float32 ratio = 1.0f; //Define ratio
				myjoint->Initialize(ground, box2, worldAnchorGround1, worldAnchorGround2, rightAnchorPoint, box2->GetWorldCenter(), ratio);
				m_world->CreateJoint(myjoint);
			}
		}
				
		/*
			for(int i=0; i<8 ; i++)
			{
				b2BodyDef bd;
				bd.position.Set(0.0f + (2+rad)*cos((6.2824*i)/8), 20.0f + (2+rad)*sin((6.2824*i)/8));
				b2Body* ground = m_world->CreateBody(&bd);
				ground->SetTransform( ground->GetPosition(), (i*3.1412)/4 );				 
				ground->CreateFixture(&shape, 0.0f);					
						
			}
			
		*/

		//Inclined plank 
		{
			b2EdgeShape shape;
			shape.Set(b2Vec2(7.5f, 14.0f), b2Vec2(15.0f, 18.0f));
			b2BodyDef bd;
			b1 = m_world->CreateBody(&bd);
			b1->CreateFixture(&shape, 0.0f);
	
		}

		{
			b2EdgeShape shape;
			shape.Set(b2Vec2(5.5f, 7.0f), b2Vec2(0.0f, 10.0f));
			b2BodyDef bd;
			b1 = m_world->CreateBody(&bd);
			b1->CreateFixture(&shape, 0.0f);
	
		}

		/*
		{
			b2EdgeShape shape;
			shape.Set(b2Vec2(7.0f, 4.0f), b2Vec2(12.0f, 6.0f));
			b2BodyDef bd;
			b1 = m_world->CreateBody(&bd);
			b1->CreateFixture(&shape, 0.0f);
	
		}
		*/
		//vertical partition for dam water balls on ground
		{
			b2EdgeShape shape;
			shape.Set(b2Vec2(-10.0f, 7.0f), b2Vec2(0.0f, 10.0f));
			b2BodyDef bd;
			b1 = m_world->CreateBody(&bd);
			b1->CreateFixture(&shape, 0.0f);
	
		} 
		{
			b2EdgeShape shape;
			shape.Set(b2Vec2(0.0f, 20.0f), b2Vec2(0.0f, 0.0f));
			b2BodyDef bd;
			b1 = m_world->CreateBody(&bd);
			b1->CreateFixture(&shape, 0.0f);
	
		}
		{
			b2BodyDef *bd = new b2BodyDef;
			bd->type = b2_dynamicBody;
			bd->position.Set(-15,4.5);
			bd->fixedRotation = true;
			
			//The open box
			b2FixtureDef *fd1 = new b2FixtureDef;
			fd1->density = 1000000.0;
			fd1->friction = 0.5;
			fd1->restitution = 0.f;
			fd1->shape = new b2PolygonShape;
			b2PolygonShape bs1;
			bs1.SetAsBox(5,0.2, b2Vec2(0.f,-2.4f), 0);
			fd1->shape = &bs1;
			b2FixtureDef *fd2 = new b2FixtureDef;
			fd2->density = 1000000.0;
			fd2->friction = 0.5;
			fd2->restitution = 0.f;
			fd2->shape = new b2PolygonShape;
			b2PolygonShape bs2;
			bs2.SetAsBox(0.2,2.5, b2Vec2(5.0f,0.f), 0);
			fd2->shape = &bs2;
			b2FixtureDef *fd3 = new b2FixtureDef;
			fd3->density = 1000000.0;
			fd3->friction = 0.5;
			fd3->restitution = 0.f;
			fd3->shape = new b2PolygonShape;
			b2PolygonShape bs3;
			bs3.SetAsBox(0.2,2.5, b2Vec2(-5.0f,0.f), 0);
			fd3->shape = &bs3;
			b2Vec2* vel = b2Vec2(-400.0f,0.0f);
			
			b2Body* box1 = m_world->CreateBody(bd);
			box1->CreateFixture(fd1);
			box1->CreateFixture(fd2);
			box1->CreateFixture(fd3);
			box1->SetLinearVelocity(*vel);

		}

		{
			b2PolygonShape shape;
			shape.SetAsBox(20.0f, 1.0f);
			
			b2BodyDef bd;
			bd.position.Set(-30.0f, 1.0f);
			b2Body* ground = m_world->CreateBody(&bd);
			ground->SetTransform( ground->GetPosition(), 0 );
			ground->CreateFixture(&shape, 0.0f);
		}


		
		//ball resting to strike the air-pump
		{
			
			b2CircleShape shape;
			shape.m_p.Set(0, 0); //position, relative to body position
			shape.m_radius = 0.5;
			/*
			b2PolygonShape shape;
			shape.SetAsBox(0.1f, 1.0f);
			*/
			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 200000.0f;
			fd.friction = 0.1f;
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(13, 18 );
			b2Body* body = m_world->CreateBody(&bd);
			body->CreateFixture(&fd);

		}

	
		
		//Water Balls in Dam
		{
			
			b2CircleShape shape;
			shape.m_p.Set(0, 0); //position, relative to body position
			shape.m_radius = 0.2;
			/*
			b2PolygonShape shape;
			shape.SetAsBox(0.1f, 1.0f);
			*/
			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 500000.0f;
			fd.friction = 0.1f;
			int j=0;
			int i=0;
			/*for (float32 j = 0; j< 100;j++)
			{
				for (float32 i = 0; i < 80;i++ )
				{
					b2BodyDef bd;
					bd.type = b2_dynamicBody;
					bd.position.Set(-36.0f + 1.0f * i, 31.25f + 1.0f * j);
					b2Body* body = m_world->CreateBody(&bd);
					body->CreateFixture(&fd);
					i+=0.1;
				}
				j+=0.1;
			}*/
			while(j<35)
			{	int i=0;
				while(i<20)
				{	
					b2BodyDef bd;
					bd.type = b2_dynamicBody;
					bd.position.Set(-36.1f + 0.40f * i, 31.25f + 0.40f * j);
					b2Body* body = m_world->CreateBody(&bd);
					body->CreateFixture(&fd);
					i++;
				}
				j++;
			}
		}
		
		
	/*

		//Another horizontal shelf
		{
			b2PolygonShape shape;
			shape.SetAsBox(7.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);
			
			b2BodyDef bd;
			bd.position.Set(1.0f, 6.0f);
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&shape, 0.0f);
		}

	*/	
	/*	
		//The pendulum that knocks the dominos off
		{
			b2Body* b2;
			{
				b2PolygonShape shape;
				shape.SetAsBox(0.25f, 1.5f);
				
				b2BodyDef bd;
				bd.position.Set(-36.5f, 28.0f);
				b2 = m_world->CreateBody(&bd);
				b2->CreateFixture(&shape, 10.0f);
			}
			
			b2Body* b4;
			{
				b2PolygonShape shape;
				shape.SetAsBox(0.25f, 0.25f);
				
				b2BodyDef bd;
				bd.type = b2_dynamicBody;
				bd.position.Set(-40.0f, 33.0f);
				b4 = m_world->CreateBody(&bd);
				b4->CreateFixture(&shape, 2.0f);
			}
			
			b2RevoluteJointDef jd;
			b2Vec2 anchor;
			anchor.Set(-37.0f, 40.0f);
			jd.Initialize(b2, b4, anchor);
			m_world->CreateJoint(&jd);
		}
	

	
		//The train of small spheres
		{
			b2Body* spherebody;
			
			b2CircleShape circle;
			circle.m_radius = 0.5;
			
			b2FixtureDef ballfd;
			ballfd.shape = &circle;
			ballfd.density = 1.0f;
			ballfd.friction = 0.0f;
			ballfd.restitution = 0.0f;
			
			for (int i = 0; i < 10; ++i)
			{
				b2BodyDef ballbd;
				ballbd.type = b2_dynamicBody;
				ballbd.position.Set(-22.2f + i*1.0, 26.6f);
				spherebody = m_world->CreateBody(&ballbd);
				spherebody->CreateFixture(&ballfd);
			}
		}
	*/	
	/*
		//The pulley system
		{
			b2BodyDef *bd = new b2BodyDef;
			bd->type = b2_dynamicBody;
			bd->position.Set(-10,15);
			bd->fixedRotation = true;
			
			//The open box
			b2FixtureDef *fd1 = new b2FixtureDef;
			fd1->density = 10.0;
			fd1->friction = 0.5;
			fd1->restitution = 0.f;
			fd1->shape = new b2PolygonShape;
			b2PolygonShape bs1;
			bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0);
			fd1->shape = &bs1;
			b2FixtureDef *fd2 = new b2FixtureDef;
			fd2->density = 10.0;
			fd2->friction = 0.5;
			fd2->restitution = 0.f;
			fd2->shape = new b2PolygonShape;
			b2PolygonShape bs2;
			bs2.SetAsBox(0.2,2, b2Vec2(2.0f,0.f), 0);
			fd2->shape = &bs2;
			b2FixtureDef *fd3 = new b2FixtureDef;
			fd3->density = 10.0;
			fd3->friction = 0.5;
			fd3->restitution = 0.f;
			fd3->shape = new b2PolygonShape;
			b2PolygonShape bs3;
			bs3.SetAsBox(0.2,2, b2Vec2(-2.0f,0.f), 0);
			fd3->shape = &bs3;
			
			b2Body* box1 = m_world->CreateBody(bd);
			box1->CreateFixture(fd1);
			box1->CreateFixture(fd2);
			box1->CreateFixture(fd3);
			
			//The bar
			bd->position.Set(10,15);
			fd1->density = 34.0;
			b2Body* box2 = m_world->CreateBody(bd);
			box2->CreateFixture(fd1);
			
			// The pulley joint
			b2PulleyJointDef* myjoint = new b2PulleyJointDef();
			b2Vec2 worldAnchorOnBody1(-10, 15); // Anchor point on body 1 in world axis
			b2Vec2 worldAnchorOnBody2(10, 15); // Anchor point on body 2 in world axis
			b2Vec2 worldAnchorGround1(-10, 20); // Anchor point for ground 1 in world axis
			b2Vec2 worldAnchorGround2(10, 20); // Anchor point for ground 2 in world axis
			float32 ratio = 1.0f; // Define ratio
			myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
			m_world->CreateJoint(myjoint);
		}

	*/	
	/*
		//The revolving horizontal platform
		{
			b2PolygonShape shape;
			shape.SetAsBox(2.2f, 0.2f);
			
			b2BodyDef bd;
			bd.position.Set(14.0f, 14.0f);
			bd.type = b2_dynamicBody;
			b2Body* body = m_world->CreateBody(&bd);
			b2FixtureDef *fd = new b2FixtureDef;
			fd->density = 1.f;
			fd->shape = new b2PolygonShape;
			fd->shape = &shape;
			body->CreateFixture(fd);
			
			b2PolygonShape shape2;
			shape2.SetAsBox(0.2f, 2.0f);
			b2BodyDef bd2;
			bd2.position.Set(14.0f, 16.0f);
			b2Body* body2 = m_world->CreateBody(&bd2);
			
			b2RevoluteJointDef jointDef;
			jointDef.bodyA = body;
			jointDef.bodyB = body2;
			jointDef.localAnchorA.Set(0,0);
			jointDef.localAnchorB.Set(0,0);
			jointDef.collideConnected = false;
			m_world->CreateJoint(&jointDef);
		}
		
		//The heavy sphere on the platform
		{
			b2Body* sbody;
			b2CircleShape circle;
			circle.m_radius = 1.0;
			
			b2FixtureDef ballfd;
			ballfd.shape = &circle;
			ballfd.density = 50.0f;
			ballfd.friction = 0.0f;
			ballfd.restitution = 0.0f;
			b2BodyDef ballbd;
			ballbd.type = b2_dynamicBody;
			ballbd.position.Set(14.0f, 18.0f);
			sbody = m_world->CreateBody(&ballbd);
			sbody->CreateFixture(&ballfd);
		}
	*/
		{
			b2EdgeShape shape;
			shape.Set(b2Vec2(8.4f, 0.0f), b2Vec2(8.4f, 5.0f));
			b2BodyDef bd;
			b1 = m_world->CreateBody(&bd);
			b1->CreateFixture(&shape, 0.0f);
	
		}
		
		{
			b2EdgeShape shape;
			shape.Set(b2Vec2(9.4f, 1.8f), b2Vec2(9.4f, 5.0f));
			b2BodyDef bd;
			b1 = m_world->CreateBody(&bd);
			b1->CreateFixture(&shape, 0.0f);
	
		}

		{
			b2EdgeShape shape;
			shape.Set(b2Vec2(9.4f, 0.0f), b2Vec2(9.4f, 0.9f));
			b2BodyDef bd;
			b1 = m_world->CreateBody(&bd);
			b1->CreateFixture(&shape, 0.0f);
	
		}
		{
			b2EdgeShape shape;
			shape.Set(b2Vec2(9.4f, 0.50f), b2Vec2(12.8f, 0.5f));
			b2BodyDef bd;
			b1 = m_world->CreateBody(&bd);
			b1->CreateFixture(&shape, 0.0f);
	
		}
		{
			b2EdgeShape shape;
			shape.Set(b2Vec2(9.4f, 0.4f), b2Vec2(12.8f, 0.40f));
			b2BodyDef bd;
			b1 = m_world->CreateBody(&bd);
			b1->CreateFixture(&shape, 0.0f);
	
		}

		{
			b2BodyDef *bd = new b2BodyDef;
			bd->type = b2_dynamicBody;
			bd->position.Set(9.0,5.6);
			//bd->fixedRotation = false;
			//The open box
			b2FixtureDef *fd1 = new b2FixtureDef;
			fd1->density = 0.000000001;
			fd1->friction = 0.5;
			fd1->restitution = 0.f;
			//fd1->shape = new b2PolygonShape;
			b2PolygonShape bs1;
			bs1.SetAsBox(3,0.4, b2Vec2(0.0f,0.0f), 0);
			fd1->shape = &bs1;
			b2FixtureDef *fd2 = new b2FixtureDef;
			fd2->density = 0.000000001;
			fd2->friction = 0.5;
			fd2->restitution = 0.f;
			//fd2->shape = new b2PolygonShape;
			b2PolygonShape bs2;
			bs2.SetAsBox(0.4,3, b2Vec2(0.0f,-2.0f), 0);
			fd2->shape = &bs2;
			b2Body* box1 = m_world->CreateBody(bd);
			box1->CreateFixture(fd1);
			box1->CreateFixture(fd2);
		}
		{
			b2PolygonShape shape;
			shape.SetAsBox(2.5f, 0.000005f);
			
			b2BodyDef bd;
			bd.position.Set(11.0f, 1.23f);
			bd.type = b2_dynamicBody;
			b2Body* body = m_world->CreateBody(&bd);
			b2FixtureDef *fd = new b2FixtureDef;
			fd->density = 100000.0f;
			fd->shape = new b2PolygonShape;
			fd->shape = &shape;
			body->CreateFixture(fd);
			
			b2PolygonShape shape2;
			shape2.SetAsBox(0.2f, 1.23f);
			b2BodyDef bd2;
			bd2.position.Set(11.0f, 1.23f);
			b2Body* body2 = m_world->CreateBody(&bd2);
			
			b2RevoluteJointDef jointDef;
			jointDef.bodyA = body;
			jointDef.bodyB = body2;
			jointDef.localAnchorA.Set(0,0);
			jointDef.localAnchorB.Set(0,0);
			jointDef.collideConnected = false;
			m_world->CreateJoint(&jointDef);
		}

		{
			b2Body* sbody;
			b2CircleShape circle;
			circle.m_radius = 0.6;
			
			b2FixtureDef ballfd;
			ballfd.shape = &circle;
			ballfd.density = 0.00005f;
			ballfd.friction = 0.0f;
			ballfd.restitution = 0.0f;
			b2BodyDef ballbd;
			ballbd.type = b2_dynamicBody;
			ballbd.position.Set(13.501f, 0.62f);
			sbody = m_world->CreateBody(&ballbd);
			sbody->CreateFixture(&ballfd);
			sbody->SetGravityScale(-0.2);
		}
		{
			b2Body* sbody;
			b2CircleShape circle;
			circle.m_radius = 0.00741;
			
			b2FixtureDef ballfd;
			ballfd.shape = &circle;
			ballfd.density = 6.0f;
			ballfd.friction = 0.0f;
			ballfd.restitution = 0.0f;
			b2BodyDef ballbd;
			ballbd.type = b2_dynamicBody;
			ballbd.position.Set(12.5f, 1.245f);
			sbody = m_world->CreateBody(&ballbd);
			sbody->CreateFixture(&ballfd);
		}


		//The ball-hinge system 
		{
			{
				b2PolygonShape shape;
				shape.SetAsBox(8.2f, 0.2f);
				
				b2BodyDef bd;
				bd.position.Set(25.0f, 33.0f);
				bd.type = b2_dynamicBody;
				b2Body* body = m_world->CreateBody(&bd);
				b2FixtureDef *fd = new b2FixtureDef;
				fd->density = 0.001f;
				fd->shape = new b2PolygonShape;
				fd->shape = &shape;
				body->CreateFixture(fd);
				
				b2PolygonShape shape2;
				shape2.SetAsBox(0.2f, 2.0f);
				b2BodyDef bd2;
				bd2.position.Set(25.0f, 33.0f);
				b2Body* body2 = m_world->CreateBody(&bd2);
				
				b2RevoluteJointDef jointDef;
				jointDef.bodyA = body;
				jointDef.bodyB = body2;
				jointDef.localAnchorA.Set(0,0);
				jointDef.localAnchorB.Set(0,0);
				jointDef.collideConnected = false;
				m_world->CreateJoint(&jointDef);
			}
			{
				b2Body* sbody;
				b2CircleShape circle;
				circle.m_radius = 0.75;
				
				b2FixtureDef ballfd;
				ballfd.shape = &circle;
				ballfd.density = 1.0f;
				ballfd.friction = 0.0f;
				ballfd.restitution = 0.0f;
				b2BodyDef ballbd;
				ballbd.type = b2_dynamicBody;
				ballbd.position.Set(25.0f, 33.95f);
				sbody = m_world->CreateBody(&ballbd);
				sbody->CreateFixture(&ballfd);
			}
			{
				b2PolygonShape shape;
				shape.SetAsBox(6.0f, 0.2f);
				
				b2BodyDef bd;
				bd.position.Set(35.0f, 27.0f);
				b2Body* ground = m_world->CreateBody(&bd);
				ground->SetTransform( ground->GetPosition(), 0 );
				ground->CreateFixture(&shape, 0.0f);
			}
			{
				b2PolygonShape shape;
				shape.SetAsBox(0.2f, 0.4f);
				
				b2BodyDef bd;
				bd.position.Set(29.2f, 27.4f);
				b2Body* ground = m_world->CreateBody(&bd);
				ground->SetTransform( ground->GetPosition(), 0 );
				ground->CreateFixture(&shape, 0.0f);
			}
			{
				b2PolygonShape shape;
				shape.SetAsBox(0.1f, 3.0f);
				
				b2BodyDef bd;
				bd.position.Set(41.1f, 25.6f);
				bd.type = b2_dynamicBody;
				b2Body* body = m_world->CreateBody(&bd);
				b2FixtureDef *fd = new b2FixtureDef;
				fd->density = 0.1f;
				fd->shape = new b2PolygonShape;
				fd->shape = &shape;
				body->CreateFixture(fd);
				
				b2PolygonShape shape2;
				shape2.SetAsBox(2.0f, 0.2f);
				b2BodyDef bd2;
				bd2.position.Set(41.1f, 27.0f);
				b2Body* body2 = m_world->CreateBody(&bd2);
				
				b2RevoluteJointDef jointDef;
				jointDef.bodyA = body;
				jointDef.bodyB = body2;
				jointDef.localAnchorA.Set(0,1.4);
				jointDef.localAnchorB.Set(0,0);
				jointDef.collideConnected = true;
				m_world->CreateJoint(&jointDef);
			}
			{
				b2Body* sbody;
				b2CircleShape circle;
				circle.m_radius = 0.75;
				
				b2FixtureDef ballfd;
				ballfd.shape = &circle;
				ballfd.density = 0.1f;
				ballfd.friction = 0.0f;
				ballfd.restitution = 0.0f;
				b2BodyDef ballbd;
				ballbd.type = b2_dynamicBody;
				ballbd.position.Set(40.25f, 22.75f);
				sbody = m_world->CreateBody(&ballbd);
				sbody->CreateFixture(&ballfd);
			}

			{
				b2PolygonShape shape;
				shape.SetAsBox(6.0f, 0.2f);
				
				b2BodyDef bd;
				bd.position.Set(35.0f, 22.0f);
				b2Body* ground = m_world->CreateBody(&bd);
				ground->SetTransform( ground->GetPosition(), 0 );
				ground->CreateFixture(&shape, 0.0f);
			}
			{
				b2PolygonShape shape;
				shape.SetAsBox(0.1f, 3.0f);
				
				b2BodyDef bd;
				bd.position.Set(28.9f, 20.6f);
				bd.type = b2_dynamicBody;
				b2Body* body = m_world->CreateBody(&bd);
				b2FixtureDef *fd = new b2FixtureDef;
				fd->density = 0.1f;
				fd->shape = new b2PolygonShape;
				fd->shape = &shape;
				body->CreateFixture(fd);
				
				b2PolygonShape shape2;
				shape2.SetAsBox(2.0f, 0.2f);
				b2BodyDef bd2;
				bd2.position.Set(28.9f, 22.0f);
				b2Body* body2 = m_world->CreateBody(&bd2);
				
				b2RevoluteJointDef jointDef;
				jointDef.bodyA = body;
				jointDef.bodyB = body2;
				jointDef.localAnchorA.Set(0,1.4);
				jointDef.localAnchorB.Set(0,0);
				jointDef.collideConnected = true;
				m_world->CreateJoint(&jointDef);
			}
			{
				b2Body* sbody;
				b2CircleShape circle;
				circle.m_radius = 0.75;
				
				b2FixtureDef ballfd;
				ballfd.shape = &circle;
				ballfd.density = 0.01f;
				ballfd.friction = 0.0f;
				ballfd.restitution = 0.0f;
				b2BodyDef ballbd;
				ballbd.type = b2_dynamicBody;
				ballbd.position.Set(29.75f, 17.75f);
				sbody = m_world->CreateBody(&ballbd);
				sbody->CreateFixture(&ballfd);
			}
			{
				b2PolygonShape shape;
				shape.SetAsBox(6.0f, 0.2f);
				
				b2BodyDef bd;
				bd.position.Set(35.0f, 17.0f);
				b2Body* ground = m_world->CreateBody(&bd);
				ground->SetTransform( ground->GetPosition(), 0 );
				ground->CreateFixture(&shape, 0.0f);
			}
			{
				b2PolygonShape shape;
				shape.SetAsBox(0.1f, 3.0f);
				
				b2BodyDef bd;
				bd.position.Set(41.1f, 15.6f);
				bd.type = b2_dynamicBody;
				b2Body* body = m_world->CreateBody(&bd);
				b2FixtureDef *fd = new b2FixtureDef;
				fd->density = 0.001f;
				fd->shape = new b2PolygonShape;
				fd->shape = &shape;
				body->CreateFixture(fd);
				
				b2PolygonShape shape2;
				shape2.SetAsBox(2.0f, 0.2f);
				b2BodyDef bd2;
				bd2.position.Set(41.1f, 17.0f);
				b2Body* body2 = m_world->CreateBody(&bd2);
				
				b2RevoluteJointDef jointDef;
				jointDef.bodyA = body;
				jointDef.bodyB = body2;
				jointDef.localAnchorA.Set(0,1.4);
				jointDef.localAnchorB.Set(0,0);
				jointDef.collideConnected = true;
				m_world->CreateJoint(&jointDef);
			}
			{
				b2Body* sbody;
				b2CircleShape circle;
				circle.m_radius = 0.75;
				
				b2FixtureDef ballfd;
				ballfd.shape = &circle;
				ballfd.density = 0.001f;
				ballfd.friction = 0.0f;
				ballfd.restitution = 0.0f;
				b2BodyDef ballbd;
				ballbd.type = b2_dynamicBody;
				ballbd.position.Set(40.25f, 12.75f);
				sbody = m_world->CreateBody(&ballbd);
				sbody->CreateFixture(&ballfd);
			}
			{
				b2PolygonShape shape;
				shape.SetAsBox(6.0f, 0.2f);
				
				b2BodyDef bd;
				bd.position.Set(35.0f, 12.0f);
				b2Body* ground = m_world->CreateBody(&bd);
				ground->SetTransform( ground->GetPosition(), 0 );
				ground->CreateFixture(&shape, 0.0f);
			}

		}
		{
			b2EdgeShape shape;
			shape.Set(b2Vec2(22.5f, 18.0f), b2Vec2(28.0f, 5.0f));
			b2BodyDef bd;
			b1 = m_world->CreateBody(&bd);
			b1->CreateFixture(&shape, 0.0f);
	
		}
		{
			b2EdgeShape shape;
			shape.Set(b2Vec2(28.0f, 5.0f), b2Vec2(36.0f, 5.0f));
			b2BodyDef bd;
			b1 = m_world->CreateBody(&bd);
			b1->CreateFixture(&shape, 0.0f);
	
		}
		{	b2BodyDef *bd = new b2BodyDef;
			bd->type = b2_dynamicBody;
			bd->position.Set(37.8,4.7);
			//bd->fixedRotation = false;
			//The open box
			b2FixtureDef *fd1 = new b2FixtureDef;
			fd1->density = 0.0001;
			fd1->friction = 0.5;
			fd1->restitution = 0.f;
			//fd1->shape = new b2PolygonShape;
			b2PolygonShape bs1;
			bs1.SetAsBox(1,0.1, b2Vec2(0.0f,-0.9f), 0);
			fd1->shape = &bs1;
			b2FixtureDef *fd2 = new b2FixtureDef;
			fd2->density = 0.0001;
			fd2->friction = 0.5;
			fd2->restitution = 0.f;
			//fd2->shape = new b2PolygonShape;
			b2PolygonShape bs2;
			bs2.SetAsBox(0.1,1, b2Vec2(1.0f,0.0f), 0);
			fd2->shape = &bs2;
			b2FixtureDef *fd3 = new b2FixtureDef;
			fd3->density = 0.0001;
			fd3->friction = 0.5;
			fd3->restitution = 0.f;
			//fd3->shape = new b2PolygonShape;
			b2PolygonShape bs3;
			bs3.SetAsBox(0.1,1, b2Vec2(-1.0f,0.0f), 0);
			fd3->shape = &bs3;
			
			b2Body* box1 = m_world->CreateBody(bd);
			box1->CreateFixture(fd1);
			box1->CreateFixture(fd2);
			box1->CreateFixture(fd3);

			b2PolygonShape shape2;
			shape2.SetAsBox(6.2f, 6.0f);
			b2BodyDef bd2;
			bd2.position.Set(37.8f, 4.7f);
			b2Body* body2 = m_world->CreateBody(&bd2);

			b2RevoluteJointDef jointDef;
			jointDef.bodyA = box1;
			jointDef.bodyB = body2;
			jointDef.localAnchorA.Set(0,0);
			jointDef.localAnchorB.Set(0,0);
			jointDef.collideConnected = false;
			m_world->CreateJoint(&jointDef);

		}
		{
			
			b2CircleShape shape;
			shape.m_p.Set(0, 0); 
			shape.m_radius = 0.05;
			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 0.00000002f;
			fd.friction = 0.0f;
			for (int j = 0; j< 20;j++)
			{
				for (int i = 0; i < 18; ++i)
				{
					b2BodyDef bd;
					bd.type = b2_dynamicBody;
					bd.position.Set(37.5f + 0.05f * i, 5.2f + 0.05f * j);
					b2Body* body = m_world->CreateBody(&bd);
					body->CreateFixture(&fd);
				}
			}
		}


	/*	
		//The see-saw system at the bottom
		{
			//The triangle wedge
			b2Body* sbody;
			b2PolygonShape poly;
			b2Vec2 vertices[3];
			vertices[0].Set(-1,0);
			vertices[1].Set(1,0);
			vertices[2].Set(0,1.5);
			poly.Set(vertices, 3);
			b2FixtureDef wedgefd;
			wedgefd.shape = &poly;
			wedgefd.density = 10.0f;
			wedgefd.friction = 0.0f;
			wedgefd.restitution = 0.0f;
			b2BodyDef wedgebd;
			wedgebd.position.Set(30.0f, 0.0f);
			sbody = m_world->CreateBody(&wedgebd);
			sbody->CreateFixture(&wedgefd);
			
			//The plank on top of the wedge
			b2PolygonShape shape;
			shape.SetAsBox(15.0f, 0.2f);
			b2BodyDef bd2;
			bd2.position.Set(30.0f, 1.5f);
			bd2.type = b2_dynamicBody;
			b2Body* body = m_world->CreateBody(&bd2);
			b2FixtureDef *fd2 = new b2FixtureDef;
			fd2->density = 1.f;
			fd2->shape = new b2PolygonShape;
			fd2->shape = &shape;
			body->CreateFixture(fd2);
			
			b2RevoluteJointDef jd;
			b2Vec2 anchor;
			anchor.Set(30.0f, 1.5f);
			jd.Initialize(sbody, body, anchor);
			m_world->CreateJoint(&jd);
			
			//The light box on the right side of the see-saw
			b2PolygonShape shape2;
			shape2.SetAsBox(2.0f, 2.0f);
			b2BodyDef bd3;
			bd3.position.Set(40.0f, 2.0f);
			bd3.type = b2_dynamicBody;
			b2Body* body3 = m_world->CreateBody(&bd3);
			b2FixtureDef *fd3 = new b2FixtureDef;
			fd3->density = 0.01f;
			fd3->shape = new b2PolygonShape;
			fd3->shape = &shape2;
			body3->CreateFixture(fd3);
		}
		*/
	}
	
	sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
