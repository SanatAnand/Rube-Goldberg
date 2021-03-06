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

/**
* Group-30 Hackstreet Boys
* Siddhant Garg , Ritwick Chaudhry , Sanat Anand
*/


#include "cs251_base.hpp"
#include "render.hpp"
#include <iostream>
#ifdef __APPLE__
#include <cmath.h>
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
    b2Body* b1;

    ///Ground (Long) at the level of the GATE-
    /// New shape is created and set as a vector edge between the mentioned endpoints
    ///then a body is created having a fixture with this shape.
    {

        b2EdgeShape shape;
        shape.Set(b2Vec2(-90.0f, -47.0f), b2Vec2(45.0f, -47.0f));
        b2BodyDef bd;
        b1 = m_world->CreateBody(&bd);
        b1->CreateFixture(&shape, 0.0f);
    }

    ///Horizontal shelf of the Dam on which the water rests-
    ///New shape is created and set as a rectangle box of dimensions 13 x 0.5
    ///then a body is created having a fixture with this shape.
    {
        b2PolygonShape shape;
        shape.SetAsBox(6.5f, 0.25f);

        b2BodyDef bd;
        bd.position.Set(-32.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->SetTransform( ground->GetPosition(), 0 );
        ground->CreateFixture(&shape, 0.0f);
    }

    ///Top Control Gate Left Wall of Dam
    ///New shape is created and set as a rectangle box of dimensions 1 x 4
    ///then a body is created having a fixture with this shape.
    {
        b2PolygonShape shapeleft;
        shapeleft.SetAsBox(0.5f, 2.0f);

        b2BodyDef bd2;
        bd2.position.Set(-39.0f, 31.5f);
        b2Body* ground2 = m_world->CreateBody(&bd2);
        ground2->CreateFixture(&shapeleft, 0.0f);
    }


    /*//Top Control Gate Right
    {
    	b2PolygonShape shaperight;
    	shaperight.SetAsBox(1.0f, 6.0f);

    	b2BodyDef bd;
    	bd.type = b2_dynamicBody;
    	bd.position.Set(-27.5f, 36.0f);
    	b2Body* ground = m_world->CreateBody(&bd);
    	b2FixtureDef *a=new b2FixtureDef ;
    	bd.fixedRotation=true;
    	a->shape=&shaperight;
    	a->density=10000000.0f;
    	ground->CreateFixture(a);

    	//ground->CreateFixture(&shaperight, 0.0f);


    }*/

    ///Sliding Pipe for Dam water Bottom Piece
    /// New shape is created and set as a vector edge between the mentioned endpoints
    ///then a body is created having a fixture with this shape.
    {
        b2EdgeShape shape;
        shape.Set(b2Vec2(-26.0f, 30.0f), b2Vec2(-18.0f, 20.0f));
        b2BodyDef bd;
        b1 = m_world->CreateBody(&bd);
        b1->CreateFixture(&shape, 0.0f);

    }

    ///Sliding Pipe for Dam water Upper Piece
    /// New shape is created and set as a vector edge between the mentioned endpoints
    ///then a body is created having a fixture with this shape.
    {
        b2EdgeShape shape;
        shape.Set(b2Vec2(-24.0f, 36.0f), b2Vec2(-14.0f, 26.0f));
        b2BodyDef bd;
        b1 = m_world->CreateBody(&bd);
        b1->CreateFixture(&shape, 0.0f);

    }
    ///Right side Dam Vertical Cover
    /// New shape is created and set as a vector edge between the mentioned endpoints
    ///then a body is created having a fixture with this shape.
    {
        b2EdgeShape shape;
        shape.Set(b2Vec2(-24.0f, 36.0f), b2Vec2(-24.0f, 44.8f));
        b2BodyDef bd;
        b1 = m_world->CreateBody(&bd);
        b1->CreateFixture(&shape, 0.0f);

    }

    ///Water Balls in Dam
    ///A circular shape is created of radius 0.4 . A nested for loop is run over 2 variables to 
    ///create 120 water drops which are dynamic bodies created with the given desitites and friction
    /// having a fixture with this circular shape and the center is set to position using nested for loops.
    {

        b2CircleShape shape;
        shape.m_p.Set(0, 0); //position, relative to body position
        shape.m_radius = 0.2;
        b2FixtureDef fd;
        fd.shape = &shape;
        fd.density = 500000.0f;
        fd.friction = 0.1f;
        int j=0;
        //int i=0;
        while(j<15)
        {
            int i=0;
            while(i<8)
            {
                b2BodyDef bd;
                bd.type = b2_dynamicBody;
                bd.position.Set(-32.1f + 0.40f * i, 31.25f + 0.40f * j);
                b2Body* body = m_world->CreateBody(&bd);
                body->CreateFixture(&fd);
                i++;
            }
            j++;
        }
    }

    ///Turbine
    ///The turbine comprises of 4 rectnagular blocks and a cirular body at the center
    ///For the circular body, a circular shape is created of radius 1.5 . 
    /// A dynamic body is created having a fixture with this above circular shape.
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

        ///For the horizontal plank,a rectangular shape of spcecified dimensions is created.
        ///A fixture is made having the required density and the above shape.
        b2PolygonShape horizontal;
        horizontal.SetAsBox(4.0f + 2* rad, 0.2f );
        b2FixtureDef *fd2 = new b2FixtureDef;
        fd2->density = 100000.0f;
        fd2->shape = new b2PolygonShape;
        fd2->shape = &horizontal;

         ///For the vertical plank,a rectangular shape of spcecified dimensions is created.
        ///A fixture is made having the required density and the above shape.
        b2PolygonShape vertical;
        vertical.SetAsBox(0.2f , 4.0f + 2* rad);
        b2FixtureDef *fd3 = new b2FixtureDef;
        fd3->density = 100000.0f;
        fd3->shape = new b2PolygonShape;
        fd3->shape = &vertical;

        ///For the left-inclined plank,a rectangular shape of spcecified dimensions is created at an angle.
        ///A fixture is made having the required density and the above shape.
        b2PolygonShape inclinedleft;
        inclinedleft.SetAsBox(4.0f + 2*rad, 0.2f, b2Vec2(0.0, 0.0), (3.1412)/4);
        b2FixtureDef *fd4 = new b2FixtureDef;
        fd4->density = 100000.0f;
        fd4->shape = new b2PolygonShape;
        fd4->shape = &inclinedleft;

        ///For the right-inclined plank,a rectangular shape of spcecified dimensions is created at an angle.
        ///A fixture is made having the required density and the above shape.
        b2PolygonShape inclinedright;
        inclinedright.SetAsBox(4.0f + 2*rad, 0.2f, b2Vec2(0.0, 0.0), -(3.1412)/4);
        b2FixtureDef *fd5 = new b2FixtureDef;
        fd5->density = 100000.0f;
        fd5->shape = new b2PolygonShape;
        fd5->shape = &inclinedright;

        ///The body which had the circular shape fixture is added multiple fixtures which were specified earlier
        ///for the different rectangular bodies.
        ground->CreateFixture(fd4);
        ground->CreateFixture(fd2);
        ground->CreateFixture(fd3);
        ground->CreateFixture(fd5);

        
        ///Another shape is created for a second body which will not be visible on the screen
        ///but will provide the support for the revolute joint. This body does not have a fixture . 
        ///This body can be of any shape and is set at the same cooordinates as center of initial body.
	b2PolygonShape shape2;        
	shape2.SetAsBox(2.0f, 2.0f);
        b2BodyDef bd2;
        bd2.position.Set(-10.0f, 17.0f);
        b2Body* body2 = m_world->CreateBody(&bd2);

        ///To create the revolute joint, a variable of type b2RevoluteJointDef is created and these 2 bodies are set to it.
        ///The (0,1.4) and (0,0) indicate that the revolute joint is at the center of both bodies.
        b2RevoluteJointDef jointDef;
        jointDef.bodyA = ground;
        jointDef.bodyB = body2;
        jointDef.localAnchorA.Set(0,0);
        jointDef.localAnchorB.Set(0,0);
        jointDef.collideConnected = true;
        m_world->CreateJoint(&jointDef);

        ///Pulley System between the turbine and the the hanging block
        {
            ///Turbine as the body
            ///A new dynamic body is created which rotates along side the turbine.
            b2BodyDef *bd = new b2BodyDef;
            bd->type = b2_dynamicBody;
            //bd->position.Set(10,8);
            bd->position.Set(10,20);
            bd->fixedRotation = true;

            ///Block hanging on the other side
            ///A shape of the form of a rectangle of dimensions 2.0 x 5.0 is created. 
            ///A fixture is created having this shape and the specified density and friction value.
            ///A body is created having this fixture of the rectangular shape.
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

            /// The pulley joint-
            ///A variable of the type of b2PulleyJointDef is defined and the 4 anchor points are specified-
            ///One each at the left and right top (pulley anchors or Ground1 andd Ground2) and the other 
            ///two anchors on the body (Body1 and Body2). Then the pulley joint is created having these anchors 
            /// and the bodies made earlier- the turbine and the rectangular block.
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

    ///The partition between left side and right side of the screen  (Walls)
    {
        ///Inclined plank-
        /// New shape is created and set as a vector edge between the mentioned endpoints
        ///then a body is created having a fixture with this shape.
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

        ///vertical partition for dam water balls on ground-
        /// New shape is created and set as a vector edge between the mentioned endpoints
        ///then a body is created having a fixture with this shape.
        {
            b2EdgeShape shape;
            shape.Set(b2Vec2(-10.0f, 8.0f), b2Vec2(0.0f, 13.0f));
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
            b2EdgeShape shape;
            shape.Set(b2Vec2(0.0f, 0.0f), b2Vec2(20.0f, 0.0f));
            b2BodyDef bd;
            b1 = m_world->CreateBody(&bd);
            b1->CreateFixture(&shape, 0.0f);

        }
    }

    ///Open Box which will collect and return the water back to the top of the dam
    ///3 fixtures are created each having different shapes representing the sides of an open box
    ///A new body is created having these 3 fixtures (multiple fixture body).
    {
        b2BodyDef *bd = new b2BodyDef;
        bd->type = b2_dynamicBody;
        bd->position.Set(-17.3,5.0);
        bd->fixedRotation = true;

        ///The open box
        b2FixtureDef *fd1 = new b2FixtureDef;
        fd1->density = 100000000.0;
        fd1->friction = 0.0;
        fd1->restitution = 0.f;
        fd1->shape = new b2PolygonShape;
        b2PolygonShape bs1;
        bs1.SetAsBox(7,0.2, b2Vec2(0.f,-2.4f), 0);
        fd1->shape = &bs1;
        b2FixtureDef *fd2 = new b2FixtureDef;
        fd2->density = 100000000.0;
        fd2->friction = 0.5;
        fd2->restitution = 0.f;
        fd2->shape = new b2PolygonShape;
        b2PolygonShape bs2;
        bs2.SetAsBox(0.2,2.5, b2Vec2(7.0f,0.f), 0);
        fd2->shape = &bs2;
        b2FixtureDef *fd3 = new b2FixtureDef;
        fd3->density = 10000000.0;
        fd3->friction = 0.0;
        fd3->restitution = 0.f;
        fd3->shape = new b2PolygonShape;
        b2PolygonShape bs3;
        bs3.SetAsBox(0.2,2.5, b2Vec2(-7.0f,0.0f), 0);
        fd3->shape = &bs3;
        //b2Vec2 vel = b2Vec2(-10.0f,0.0f);

        b2Body* box1 = m_world->CreateBody(bd);
        box1->CreateFixture(fd1);
        box1->CreateFixture(fd2);
        box1->CreateFixture(fd3);

    }

    ///The ground on which the open water box is resting
    ///New shape is created and set as a rectangle box of dimensions 30 x 1.5
    ///then a body is created having a fixture with this shape.
    {
        b2PolygonShape shape;
        shape.SetAsBox(15.0f, 0.75f);

        b2BodyDef bd;
        bd.position.Set(-25.0f, 2.25f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->SetTransform( ground->GetPosition(), 0 );
        ground->CreateFixture(&shape, 0.0f);
    }

    ///The flying plank (which takes the water back to the top of the Dam)
    ///New shape is created and set as a rectangle box of dimensions 10 x 0.2
    ///then a body is created having a fixture with this shape.
    ///Also, the gravity of this plank is set to negative which causes it to fly upwards.
    {
        b2PolygonShape shaperight;
        shaperight.SetAsBox(5.0f, 0.1f);

        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position.Set(-45.1f, -46.9f);
        b2Body* ground = m_world->CreateBody(&bd);
        b2FixtureDef *a=new b2FixtureDef ;
        bd.fixedRotation=true;
        a->shape=&shaperight;
        a->friction=100000.0;
        a->density=500000000000.0f;
        ground->CreateFixture(a);
        ground->SetGravityScale(-0.002);
    }
    ///Right side vertical cover for the lift of the open water box
    /// New shape is created and set as a vector edge between the mentioned endpoints
    ///then a body is created having a fixture with this shape.
    {

        b2EdgeShape shape;
        shape.Set(b2Vec2(-39.0f, 10.0f), b2Vec2(-39.0f, 30.0f));
        b2BodyDef bd;
        b1 = m_world->CreateBody(&bd);
        b1->CreateFixture(&shape, 0.0f);
    }
    ///Left side vertical cover for the lift of the open water box
    /// New shape is created and set as a vector edge between the mentioned endpoints
    ///then a body is created having a fixture with this shape.
    {

        b2EdgeShape shape;
        shape.Set(b2Vec2(-55.0f, 10.0f), b2Vec2(-55.0f, 40.0f));
        b2BodyDef bd;
        b1 = m_world->CreateBody(&bd);
        b1->CreateFixture(&shape, 0.0f);
    }
    ///The Vertical revolving plank which pushes the open  water box towards the right
    /// New shape is created and set as a rectangle with dimensions 20 x 0.4.
    ///Then a dynamic body is created having a fixture with this shape and given density and set to (-5.4, 0.0).
    ///Another shape is created for a second body which will not be visible on the screen
    //but will provide the support for the revolute joint. This body does not have a fixture . 
    ///This body can be of any shape and is set at the same cooordinates as center of initial body.
    ///To create the revolute joint, a variable of type b2RevoluteJointDef is created and these 2 bodies are set to it.
    ///The (0,1.4) and (0,0) indicate that the revolute joint is at the center of body 2 and 1.4 units vertically above center of body 1.
    {
        b2PolygonShape shape;
        shape.SetAsBox(0.2f, 10.0f);

        b2BodyDef bd;
        bd.position.Set(-5.4f, 0.0f);
        bd.type = b2_dynamicBody;
        b2Body* body = m_world->CreateBody(&bd);
        b2FixtureDef *fd = new b2FixtureDef;
        fd->density = 100000000.0f;
        fd->shape = new b2PolygonShape;
        fd->shape = &shape;
        body->CreateFixture(fd);

        b2PolygonShape shape2;
        shape2.SetAsBox(5.4f, 6.0f);
        b2BodyDef bd2;
        bd2.position.Set(-5.4f, 0.0f);
        b2Body* body2 = m_world->CreateBody(&bd2);

        b2RevoluteJointDef jointDef;
        jointDef.bodyA = body;
        jointDef.bodyB = body2;
        jointDef.localAnchorA.Set(0,1.4);
        jointDef.localAnchorB.Set(0,0);
        jointDef.collideConnected = true;
        m_world->CreateJoint(&jointDef);
    }
    ///Ball resting to strike the air-pump
    /// A circular shape is created of radius 0.5 , a dynamic body is created with the given desitites and friction
    ///having a fixture with this circular shape and the center is set to position (13,18)
    {

        b2CircleShape shape;
        shape.m_p.Set(0, 0); //position, relative to body position
        shape.m_radius = 0.5;
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
    ///Top-most revolving platform (Hit by the balloon second)
    /// New shape is created and set as a rectangle with dimensions 16.4 x 0.4.
    ///Then a dynamic body is created having a fixture with this shape and given density and set to (0.0, 49.0).
    ///Another shape is created for a second body which will not be visible on the screen
    //but will provide the support for the revolute joint. This body does not have a fixture . 
    ///This body can be of any shape and is set at the same cooordinates as center of initial body.
    ///To create the revolute joint, a variable of type b2RevoluteJointDef is created and these 2 bodies are set to it.
    ///The (0,0) and (0,0) indicate that the revolute joint is at the center of both bodies.
    {
        b2PolygonShape shape;
        shape.SetAsBox(8.2f, 0.2f);

        b2BodyDef bd;
        bd.position.Set(0.0f, 49.0f);
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
        bd2.position.Set(0.0f, 49.0f);
        b2Body* body2 = m_world->CreateBody(&bd2);

        b2RevoluteJointDef jointDef;
        jointDef.bodyA = body;
        jointDef.bodyB = body2;
        jointDef.localAnchorA.Set(0,0);
        jointDef.localAnchorB.Set(0,0);
        jointDef.collideConnected = false;
        m_world->CreateJoint(&jointDef);
    }
    ///Ball resting on topmost revolving platform
    /// A circular shape is created of radius 0.75 , a dynamic body is created with the given desitites and friction
    ///having a fixture with this circular shape and the center is set to position (0.0,49.75)
    {
        b2Body* sbody;
        b2CircleShape circle;
        circle.m_radius = 0.75;

        b2FixtureDef ballfd;
        ballfd.shape = &circle;
        ballfd.density = 2.0f;
        ballfd.friction = 0.0f;
        ballfd.restitution = 0.0f;
        b2BodyDef ballbd;
        ballbd.type = b2_dynamicBody;
        ballbd.position.Set(0.0f, 49.75f);
        sbody = m_world->CreateBody(&ballbd);
        sbody->CreateFixture(&ballfd);
    }
    ///top horizontal surface on which the dominos rest-
    /// New shape is created and set as a vector edge between the mentioned endpoints
    ///then a body is created having a fixture with this shape.
    {


        b2EdgeShape shape;
        shape.Set(b2Vec2(-46.0f, 45.0f), b2Vec2(0.0f, 45.0f));
        b2BodyDef bd;
        b1 = m_world->CreateBody(&bd);
        b1->CreateFixture(&shape, 0.0f);
    }
    ///Dominos at the topmost horizontal plank
    ///A shape is created of a rectangle of dimensions 0.4 x 2.0
    ///A fixture having this above shape and specified density and friction is created.
    ///Using a for loop, each domino body is created with each having the same fixture as above and the position 
    ///of each differening by a fixed amount to create the chain of dominos. The last 3 dominoes made needed to be
    ///individual and so they have been created separately out of the for loop.
    {
        b2PolygonShape shape;
        shape.SetAsBox(0.2f, 1.0f);

        b2FixtureDef fd;
        fd.shape = &shape;
        fd.density = 4.0f;
        fd.friction = 1.0f;

        b2PolygonShape shape2;
        shape2.SetAsBox(1.0f, 0.2f);

        b2FixtureDef fd2;
        fd2.shape = &shape2;
        fd2.density = 20.0f;
        fd2.friction = 0.1f;

        ///first set of 30 dominos
        for (int i = 0; i < 10; ++i)
        {
            for(int j=0; j<3 ; j++)
            {
                b2BodyDef bd;
                bd.type = b2_dynamicBody;
                bd.position.Set(-30.f + 1.5f * i, 45.7f + 2.0f * j);
                b2Body* body = m_world->CreateBody(&bd);
                body->CreateFixture(&fd);
            }
        }

        ///next set of 21 dominos
        for (int i = 3; i < 10; ++i)
        {
            for(int j=0; j<3 ; j++)
            {
                b2BodyDef bd;
                bd.type = b2_dynamicBody;
                bd.position.Set(-44.0f + 1.5f * i, 45.7f + 2.0f * j);
                b2Body* body = m_world->CreateBody(&bd);
                body->CreateFixture(&fd);
            }
        }

        /// last three single dominos
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position.Set(-44.0f , 45.7f );
        b2Body* body = m_world->CreateBody(&bd);
        body->CreateFixture(&fd);

        b2BodyDef bd2;
        bd2.type = b2_dynamicBody;
        bd2.position.Set(-42.5f , 45.7f );
        b2Body* body2 = m_world->CreateBody(&bd2);
        body2->CreateFixture(&fd);

        b2BodyDef bd3;
        bd3.type = b2_dynamicBody;
        bd3.position.Set(-41.0f , 45.7f );
        b2Body* body3 = m_world->CreateBody(&bd3);
        body3->CreateFixture(&fd);
    }

    ///Heavy ball at the leftmost end of the domino chain at the top horizontal surface
    /// A circular shape is created of radius 0.75 , a dynamic body is created with the given desitites and friction
    ///having a fixture with this circular shape and the center is set to position (-46.0001,45,8)
    {
        b2Body* sbody;
        b2CircleShape circle;
        circle.m_radius = 0.75;

        b2FixtureDef ballfd;
        ballfd.shape = &circle;
        ballfd.density = 100000000.0f;
        ballfd.friction = 0.0f;
        ballfd.restitution = 0.0f;
        b2BodyDef ballbd;
        ballbd.type = b2_dynamicBody;
        ballbd.position.Set(-46.0001f, 45.8f);
        sbody = m_world->CreateBody(&ballbd);
        sbody->CreateFixture(&ballfd);


    }
    ///Inclined surface for the heavy ball to fall on-
    /// New shape is created and set as a vector edge between the mentioned endpoints
    ///then a body is created having a fixture with this shape.
    {
        b2EdgeShape shape;
        shape.Set(b2Vec2(-46.0f, 45.0f), b2Vec2(-65.0f, 39.0f));
        b2BodyDef bd;
        b1 = m_world->CreateBody(&bd);
        b1->CreateFixture(&shape, 0.0f);
    }
    ///Chain Object
    ///Using a chain shape we create the required shape of the arc by using the formula for the curve .
    ///Here the formula used is x*x + y*y = 3000 and using a for loop, the points on this curve are found.
    ///These points are then added to the shape which is used in the fixture of a body.
    {
        b2Vec2 vs[50];
        float x=0,y=0;
        for(int i=0; i<50; ++i)
        {
            x = sqrt(3000.0 - (y*y));
            y-=1.0;
            vs[i].Set(-28.0f - x, 49.0f + y);
        }
        //cout<<"djhbdik";
        b2ChainShape chain;

        chain.CreateChain(vs, 50);
        b2BodyDef bd;
        b1 = m_world->CreateBody(&bd);
        b1->CreateFixture(&chain, 0.0f);

    }
    ///Chain Object
    ///Using a chain shape we create the required shape of the arc by using the formula for the curve .
    ///Here the formula used is x*x + y*y = 1000 and using a for loop, the points on this curve are found.
    ///These points are then added to the shape which is used in the fixture of a body.
    {
        b2Vec2 vs[40];
        float x=0,y=0;
        for(int i=0; i<40; ++i)
        {
            x = sqrt(1000.0 - (y*y));
            y-=0.5;
            vs[i].Set( -20.0f + x, 0.0f + y);
        }
        //cout<<"djhbdik";
        b2ChainShape chain;

        chain.CreateChain(vs, 40);
        b2BodyDef bd;
        b1 = m_world->CreateBody(&bd);
        b1->CreateFixture(&chain, 0.0f);

    }
    ///Chain Object
    ///Using a chain shape we create the required shape of the arc by using the formula for the curve .
    ///Here the formula used is x*x + y*y = 500 and using a for loop, the points on this curve are found.
    ///These points are then added to the shape which is used in the fixture of a body.
    {
        b2Vec2 vs[40];
        float x=0,y=0;
        for(int i=0; i<40; ++i)
        {
            x = sqrt(500.0 - (y*y));
            y-=0.5;
            vs[i].Set( 12.0f - x, -27.0f + y);
        }
        //cout<<"djhbdik";
        b2ChainShape chain;

        chain.CreateChain(vs, 40);
        b2BodyDef bd;
        b1 = m_world->CreateBody(&bd);
        b1->CreateFixture(&chain, 0.0f);

    }
    ///Horizontal surface below the open water box for the heavy ball to fall on and push the revolving plank-
    /// New shape is created and set as a vector edge between the mentioned endpoints
    ///then a body is created having a fixture with this shape.
    {

        b2EdgeShape shape;
        shape.Set(b2Vec2(-40.0f, -12.5f), b2Vec2(0.0f, -12.5f));
        b2BodyDef bd;
        b1 = m_world->CreateBody(&bd);
        b1->CreateFixture(&shape, 0.0f);
    }

    ///Edges for the Shape of the Air-Pump
    {
        ///left edge-
        /// New shape is created and set as a vector edge between the mentioned endpoints
        ///then a body is created having a fixture with this shape.
        {
            b2EdgeShape shape;
            shape.Set(b2Vec2(8.4f, 0.0f), b2Vec2(8.4f, 5.0f));
            b2BodyDef bd;
            b1 = m_world->CreateBody(&bd);
            b1->CreateFixture(&shape, 0.0f);

        }
        ///right edge upper-
        /// New shape is created and set as a vector edge between the mentioned endpoints
        ///then a body is created having a fixture with this shape.
        {
            b2EdgeShape shape;
            shape.Set(b2Vec2(9.4f, 1.8f), b2Vec2(9.4f, 5.0f));
            b2BodyDef bd;
            b1 = m_world->CreateBody(&bd);
            b1->CreateFixture(&shape, 0.0f);

        }
        ///right edge lower-
        /// New shape is created and set as a vector edge between the mentioned endpoints
        ///then a body is created having a fixture with this shape.
        {
            b2EdgeShape shape;
            shape.Set(b2Vec2(9.4f, 0.0f), b2Vec2(9.4f, 0.9f));
            b2BodyDef bd;
            b1 = m_world->CreateBody(&bd);
            b1->CreateFixture(&shape, 0.0f);

        }
        ///horizontal pipe edge-
        /// New shape is created and set as a vector edge between the mentioned endpoints
        ///then a body is created having a fixture with this shape.
        {
            b2EdgeShape shape;
            shape.Set(b2Vec2(9.4f, 0.4f), b2Vec2(12.8f, 0.40f));
            b2BodyDef bd;
            b1 = m_world->CreateBody(&bd);
            b1->CreateFixture(&shape, 0.0f);
        }
    }
    ///The Pump pf the Air-PumpS
    ///2 fixtures are created each having different shapes - one vertical rectangle and the
    /// other horizontal rectangle. A new body is created having these 2 fixtures (multiple fixture body).
    {
        b2BodyDef *bd = new b2BodyDef;
        bd->type = b2_dynamicBody;
        bd->position.Set(9.0,5.6);
        //bd->fixedRotation = false;
        ///The open box
        b2FixtureDef *fd1 = new b2FixtureDef;
        fd1->density = 0.000000001;
        fd1->friction = 0.5;
        fd1->restitution = 0.f;
        b2PolygonShape bs1;
        bs1.SetAsBox(3,0.4, b2Vec2(0.0f,0.0f), 0);
        fd1->shape = &bs1;
        b2FixtureDef *fd2 = new b2FixtureDef;
        fd2->density = 0.000000001;
        fd2->friction = 0.5;
        fd2->restitution = 0.f;
        b2PolygonShape bs2;
        bs2.SetAsBox(0.4,3, b2Vec2(0.0f,-2.0f), 0);
        fd2->shape = &bs2;
        b2Body* box1 = m_world->CreateBody(bd);
        box1->CreateFixture(fd1);
        box1->CreateFixture(fd2);
    }
    ///Extremely thin revolving plank for the Air-Pump
    /// New shape is created and set as a rectangle with dimensions 5.0 x 0.000010
    ///then a dynamic body is created having a fixture with this shape and given density and set to (25.0, 33.0) 
    ///Another shape is created for a second body which will not be visible on the screen
    ///but will provide the support for the revolute joint. This body does not have a fixture . 
    ///This body can be of any shape and is set at the same cooordinates as center of initial body.
    ///To create the revolute joint, a variable of type b2RevoluteJointDef is created and these 2 bodies are set to it.
    ///The (0,0) and (0,0) indicate that the revolute joint is at the center of both the bodies.
        {
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
    ///Balloon
    /// A circular shape is created of radius 0.6 , a dynamic body is created with the given desitites and friction
    ///having a fixture with this circular shape and the center is set to position (13.501,0.62).
    /// Also the baloon iset a negative gravity so that it is able to rise.
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
    ///Extremely Small ball helping in working of the Air-Pump (helps in balancing the revolving platform by balancing torque)
    /// A circular shape is created of radius 0.00741 , a dynamic body is created with the given desitites and friction
    ///having a fixture with this circular shape and the center is set to position (12.5,1.245)
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
    ///The ball-hinge system
    {
        ///Revolving Platform at the top to which the balloon strikes first-
        /// New shape is created and set as a rectangle with dimensions 16.4x 0.4
        ///then a dynamic body is created having a fixture with this shape and given density and set to (25.0, 33.0) 
        ///Another shape is created for a second body which will not be visible on the screen
        ///but will provide the support for the revolute joint. This body does not have a fixture . 
        ///This body can be of any shape and is set at the same cooordinates as center of initial body.
        ///To create the revolute joint, a variable of type b2RevoluteJointDef is created and these 2 bodies are set to it.
        ///The (0,0) and (0,0) indicate that the revolute joint is at the center of both the bodies.
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
        ///Ball resting on the above horizontal revolving platform
        /// A circular shape is created of radius 0.75 , a dynamic body is created with the given desitites and friction
        ///having a fixture with this circular shape and the center is set to position (25,33.95)
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
        ///Top plank of the ball-hinge system
        ///New shape is created and set as a rectangle box of dimensions 12 x 0.4
        ///then a body is created having a fixture with this shape.
        {
            b2PolygonShape shape;
            shape.SetAsBox(6.0f, 0.2f);

            b2BodyDef bd;
            bd.position.Set(35.0f, 27.0f);
            b2Body* ground = m_world->CreateBody(&bd);
            ground->SetTransform( ground->GetPosition(), 0 );
            ground->CreateFixture(&shape, 0.0f);
        }
        ///Left cover at the top plank for the ball-hinge on the left side
        ///New shape is created and set as a rectangle box of dimensions o.4 x 0.8
        ///then a body is created having a fixture with this shape.
        {
            b2PolygonShape shape;
            shape.SetAsBox(0.2f, 0.4f);

            b2BodyDef bd;
            bd.position.Set(29.2f, 27.4f);
            b2Body* ground = m_world->CreateBody(&bd);
            ground->SetTransform( ground->GetPosition(), 0 );
            ground->CreateFixture(&shape, 0.0f);
        }
        /// Vertical revolving plank (Right side of the top plank of the ball-hinge system)
        /// New shape is created and set as a rectangle with dimensions 6 x 0.2
        ///then a dynamic body is created having a fixture with this shape and given density and set to (41.1, 25.6) 
        ///Another shape is created for a second body which will not be visible on the screen
        ///but will provide the support for the revolute joint. This body does not have a fixture . 
        ///This body can be of any shape and is set at the same cooordinates as center of initial body.
        ///To create the revolute joint, a variable of type b2RevoluteJointDef is created and these 2 bodies are set to it.
        ///The (0,1.4) and (0,0) indicate that the revolute joint is at the center of body 2 and at 1.4 units veritically above center of body 1
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
        ///Ball resting on the right side of the 2nd plank of the ball-hinge system
        /// A circular shape is created of radius 0.75 , a dynamic body is created with the given desitites and friction
        ///having a fixture with this circular shape and the center is set to position (40.25,22.75)
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
        ///The second plank from top of the ball-hinge system
        ///New shape is created and set as a rectangle box of dimensions 12 x 0.4
        ///then a body is created having a fixture with this shape.
        {
            b2PolygonShape shape;
            shape.SetAsBox(6.0f, 0.2f);

            b2BodyDef bd;
            bd.position.Set(35.0f, 22.0f);
            b2Body* ground = m_world->CreateBody(&bd);
            ground->SetTransform( ground->GetPosition(), 0 );
            ground->CreateFixture(&shape, 0.0f);
        }
        /// Vertical revolving plank (Left side of the second plank of the ball-hinge system)
        /// New shape is created and set as a rectangle with dimensions 6 x 0.2
        ///then a dynamic body is created having a fixture with this shape and given density and set to (28.9, 20.6) 
        ///Another shape is created for a second body which will not be visible on the screen
        ///but will provide the support for the revolute joint. This body does not have a fixture . 
        ///This body can be of any shape and is set at the same cooordinates as center of initial body.
        ///To create the revolute joint, a variable of type b2RevoluteJointDef is created and these 2 bodies are set to it.
        ///The (0,1.4) and (0,0) indicate that the revolute joint is at the center of body 2 and at 1.4 units veritically above center of body 1
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
        ///Ball resting on the left side of the 3rd plank of the ball-hinge system
        /// A circular shape is created of radius 0.75 , a dynamic body is created with the given desitites and friction
        ///having a fixture with this circular shape and the center is set to position (29.75,17.75)
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
        ///The third plank from top of the ball-hinge system
        ///New shape is created and set as a rectangle box of dimensions 12 x 0.4
        ///then a body is created having a fixture with this shape.
        {
            b2PolygonShape shape;
            shape.SetAsBox(6.0f, 0.2f);

            b2BodyDef bd;
            bd.position.Set(35.0f, 17.0f);
            b2Body* ground = m_world->CreateBody(&bd);
            ground->SetTransform( ground->GetPosition(), 0 );
            ground->CreateFixture(&shape, 0.0f);
        }
        /// Vertical revolving plank (Right side of the third plank of the ball-hinge system)
        /// New shape is created and set as a rectangle with dimensions 6 x 0.2
        ///then a dynamic body is created having a fixture with this shape and given density and set to (41.1, 15.6) 
        ///Another shape is created for a second body which will not be visible on the screen
        ///but will provide the support for the revolute joint. This body does not have a fixture . 
        ///This body can be of any shape and is set at the same cooordinates as center of initial body.
        ///To create the revolute joint, a variable of type b2RevoluteJointDef is created and these 2 bodies are set to it.
        ///The (0,1.4) and (0,0) indicate that the revolute joint is at the center of body 2 and at 1.4 units veritically above center of body 1
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
        ///Ball resting on the right side of the 4th plank of the ball-hinge system
        /// A circular shape is created of radius 0.75 , a dynamic body is created with the given desitites and friction
        ///having a fixture with this circular shape and the center is set to position (40.25,12.75)
        {
            b2Body* sbody;
            b2CircleShape circle;
            circle.m_radius = 0.75;

            b2FixtureDef ballfd;
            ballfd.shape = &circle;
            ballfd.density = 0.0001f;
            ballfd.friction = 0.0f;
            ballfd.restitution = 0.0f;
            b2BodyDef ballbd;
            ballbd.type = b2_dynamicBody;
            ballbd.position.Set(40.25f, 12.75f);
            sbody = m_world->CreateBody(&ballbd);
            sbody->CreateFixture(&ballfd);
        }
        ///The fourth plank from top of the ball-hinge system
        ///New shape is created and set as a rectangle box of dimensions 12 x 0.4
        ///then a body is created having a fixture with this shape.
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


    ///arc for the ball to fall on the glass from the ball-hinge system
    ///Using a chain shape we create the required shape of the arc by using the formula for the curve .
    ///Here the formula used is x*x + y*y = 150 and using a for loop, the points on this curve are found.
    ///These points are then added to the shape which is used in the fixture of a body.
    {
        b2Vec2 vs[20];
        float x=0,y=0;
        for(int i=0; i<20; ++i)
        {
            x = sqrt(150.0 - (y*y));
            y-=0.5;
            vs[i].Set( 33.0f - x, 16.0f + y);
        }
        //cout<<"djhbdik";
        b2ChainShape chain;

        chain.CreateChain(vs, 20);
        b2BodyDef bd;
        b1 = m_world->CreateBody(&bd);
        b1->CreateFixture(&chain, 0.0f);

    }



    ///path for ball (at the right end) after the arc
    {
        ///Flat surface after the arc-
        /// New shape is created and set as a vector edge between the mentioned endpoints
        ///then a body is created having a fixture with this shape.
        {
            b2EdgeShape shape;
            shape.Set(b2Vec2(33.7f, 6.0f), b2Vec2(25.0f, 6.0f));
            b2BodyDef bd;
            b1 = m_world->CreateBody(&bd);
            b1->CreateFixture(&shape, 0.0f);

        }
        ///Negative slope surface (going right)-
        /// New shape is created and set as a vector edge between the mentioned endpoints
        ///then a body is created having a fixture with this shape.
        {
            b2EdgeShape shape;
            shape.Set(b2Vec2(33.7f, 6.0f), b2Vec2(49.5f, -4.1f));
            b2BodyDef bd;
            b1 = m_world->CreateBody(&bd);
            b1->CreateFixture(&shape, 0.0f);

        }
        ///Negative slope surface (going right)-
        /// New shape is created and set as a vector edge between the mentioned endpoints
        ///then a body is created having a fixture with this shape.
        {
            b2EdgeShape shape;
            shape.Set(b2Vec2(52.4f, -6.25f), b2Vec2(55.0f, -8.0f));
            b2BodyDef bd;
            b1 = m_world->CreateBody(&bd);
            b1->CreateFixture(&shape, 0.0f);

        }
        ///Negative slope surface (going right) (Upper Side)-
        /// New shape is created and set as a vector edge between the mentioned endpoints
        ///then a body is created having a fixture with this shape.
        {
            b2EdgeShape shape;
            shape.Set(b2Vec2(56.9f, -6.1f), b2Vec2(55.0f, -4.8f));
            b2BodyDef bd;
            b1 = m_world->CreateBody(&bd);
            b1->CreateFixture(&shape, 0.0f);

        }
        ///Circular arc tunnel (Outer)-
        ///Using a chain shape we create the required shape of the arc by using the formula for the curve .
        ///Here the formula used is x*x + y*y = 25 and using a for loop, the points on this curve are found.
        ///These points are then added to the shape which is used in the fixture of a body.
        {
            b2Vec2 vs[24];
            float x=0,y=5;
            for(int i=0; i<21; ++i)
            {
                x = sqrt(25.0 - (y*y));
                y-=0.5;
                vs[i].Set( 58.5f + x, -4.65f + y);
            }
            y+=0.5;
            for(int i=1; i<5; ++i)
            {
                y+=0.5;
                x = sqrt(26.0 - (y*y));
                vs[20 + i].Set( 58.5f - x, -4.65f + y);
            }
            //cout<<"djhbdik";
            b2ChainShape chain;

            chain.CreateChain(vs, 24);
            b2BodyDef bd;
            b1 = m_world->CreateBody(&bd);
            b1->CreateFixture(&chain, 0.0f);

        }
        ///Circular arc tunnel (Inner)
        ///Using a chain shape we create the required shape of the arc by using the formula for the curve .
        ///Here the formula used is x*x + y*y = 4.1 and using a for loop, the points on this curve are found.
        ///These points are then added to the shape which is used in the fixture of a body.
        {
            b2Vec2 vs[24];
            float x=0,y=2;
            for(int i=0; i<21; ++i)
            {
                x = sqrt(4.1 - (y*y));
                y-=0.2;
                vs[i].Set( 58.5f + x, -4.75f + y);
            }
            y+=0.2;
            for(int i=1; i<5; ++i)
            {
                y+=0.2;
                x = sqrt(4.2- (y*y));
                vs[20 + i].Set( 58.5f - x, -4.75f + y);
            }
            //cout<<"djhbdik";
            b2ChainShape chain;

            chain.CreateChain(vs, 24);
            b2BodyDef bd;
            b1 = m_world->CreateBody(&bd);
            b1->CreateFixture(&chain, 0.0f);

        }
        ///Positive slope surface (Going left downwards)-
        /// New shape is created and set as a vector edge between the mentioned endpoints
        ///then a body is created having a fixture with this shape.
        {
            b2EdgeShape shape;
            shape.Set(b2Vec2(58.5f, -3.0f), b2Vec2(55.0f, -4.8f));
            b2BodyDef bd;
            b1 = m_world->CreateBody(&bd);
            b1->CreateFixture(&shape, 0.0f);

        }
        ///Positive slope surface (Going left downwards)-
        /// New shape is created and set as a vector edge between the mentioned endpoints
        ///then a body is created having a fixture with this shape.
        {
            b2EdgeShape shape;
            shape.Set(b2Vec2(58.5f, 0.0f), b2Vec2(53.0f, -2.8f));
            b2BodyDef bd;
            b1 = m_world->CreateBody(&bd);
            b1->CreateFixture(&shape, 0.0f);

        }
        ///Positive slope surface (Going left downwards)-
        /// New shape is created and set as a vector edge between the mentioned endpoints
        ///then a body is created having a fixture with this shape.
        {
            b2EdgeShape shape;
            shape.Set(b2Vec2(52.4f, -6.25f), b2Vec2(35.0f, -15.0f));
            b2BodyDef bd;
            b1 = m_world->CreateBody(&bd);
            b1->CreateFixture(&shape, 0.0f);

        }
        ///arc for the ball to come to the surface containing dominos
        ///Using a chain shape we create the required shape of the arc by using the formula for the curve .
        ///Here the formula used is x*x + y*y = 25 and using a for loop, the points on this curve are found.
        ///These points are then added to the shape which is used in the fixture of a body.
        {
            b2Vec2 vs[11];
            float x=0,y=5;
            for(int i=0; i<11; ++i)
            {
                x = sqrt(25 - (y*y));
                y-=0.5;
                vs[i].Set( 33.5f - x, -16.0f - y);
            }
            b2ChainShape chain;

            chain.CreateChain(vs, 11);
            b2BodyDef bd;
            b1 = m_world->CreateBody(&bd);
            b1->CreateFixture(&chain, 0.0f);

        }
        ///flat surface for dominoes (upper surface)-
        /// New shape is created and set as a vector edge between the mentioned endpoints
        ///then a body is created having a fixture with this shape.
        {
            b2EdgeShape shape;
            shape.Set(b2Vec2(33.5f, -20.5f), b2Vec2(74.0f, -20.5f));
            b2BodyDef bd;
            b1 = m_world->CreateBody(&bd);
            b1->CreateFixture(&shape, 0.0f);

        }
        ///flat surface for dominoes (lower surface)-
        /// New shape is created and set as a vector edge between the mentioned endpoints
        ///then a body is created having a fixture with this shape.
        {
            b2EdgeShape shape;
            shape.Set(b2Vec2(61.0f, -23.0f), b2Vec2(74.0f, -23.0f));
            b2BodyDef bd;
            b1 = m_world->CreateBody(&bd);
            b1->CreateFixture(&shape, 0.0f);

        }
    }

    ///Dominos at bottom
    {

        ///revolute joint to push dominos at the bottom surface-
        /// New shape is created and set as a rectangle with dimensions 4 x 0.2.
        ///Then a dynamic body is created having a fixture with this shape and given density and set to (74.2, -20.7).
        ///Another shape is created for a second body which will not be visible on the screen
        ///but will provide the support for the revolute joint. This body does not have a fixture . 
        ///This body can be of any shape and is set at the same cooordinates as center of initial body.
        ///To create the revolute joint, a variable of type b2RevoluteJointDef is created and these 2 bodies are set to it.
        ///The (0,0) and (0,0) indicate that the revolute joint is at the center of both bodies.
            b2PolygonShape shape;
            shape.SetAsBox(0.1f, 2.0f);

            b2BodyDef bd;
            bd.position.Set(74.2f, -20.7f);
            bd.type = b2_dynamicBody;
            b2Body* body = m_world->CreateBody(&bd);
            b2FixtureDef *fd = new b2FixtureDef;
            fd->density = 0.00001f;
            fd->shape = new b2PolygonShape;
            fd->shape = &shape;
            body->CreateFixture(fd);

            b2PolygonShape shape2;
            shape2.SetAsBox(2.0f, 0.2f);
            b2BodyDef bd2;
            bd2.position.Set(74.2f, -20.7f);
            b2Body* body2 = m_world->CreateBody(&bd2);

            b2RevoluteJointDef jointDef;
            jointDef.bodyA = body;
            jointDef.bodyB = body2;
            jointDef.localAnchorA.Set(0,0);
            jointDef.localAnchorB.Set(0,0);
            jointDef.collideConnected = true;
            m_world->CreateJoint(&jointDef);
        }
        ///Dominos
        ///A shape is created of a rectangle of dimensions 0.4 x 2.0
        ///A fixture having this above shape and specified density and friction is created.
        ///Using a for loop, each domino body is created with each having the same fixture as above and the position 
        ///of each differening by a fixed amount to create the 2 chains of dominos. 
        {
            b2PolygonShape shape;
            shape.SetAsBox(0.2f, 1.0f);

            b2FixtureDef fd;
            fd.shape = &shape;
            fd.density = 0.001f;
            fd.friction = 1.0f;

            b2PolygonShape shape2;
            shape2.SetAsBox(1.0f, 0.2f);

            b2FixtureDef fd2;
            fd2.shape = &shape2;
            fd2.density = 20.0f;
            fd2.friction = 0.1f;
            ///upper surface
            for (int i = 0; i < 3; ++i)
            {

                b2BodyDef bd;
                bd.type = b2_dynamicBody;
                bd.position.Set(69.4f + 1.8f * i, -19.5f );
                b2Body* body = m_world->CreateBody(&bd);
                body->CreateFixture(&fd);

            }
            ///lower surface
            for (int i = 0; i < 7; ++i)
            {

                b2BodyDef bd;
                bd.type = b2_dynamicBody;
                bd.position.Set(62.f + 1.8f * i, -22.0f );
                b2Body* body = m_world->CreateBody(&bd);
                body->CreateFixture(&fd);

            }

        }



    }


    ///Pulley system on lower right side (Right)
    {
        b2BodyDef *bd = new b2BodyDef;
        bd->type = b2_dynamicBody;
        bd->position.Set(60,-27);
        bd->fixedRotation = true;

        ///The open box-
        ///3 diffreent fixtures are created each having diffrent shapes representing the 3 sides
        /// of the open rectangular box. a body is created having these 3 fixtures (multiple fixture body)
        /// and set to the position (60,-27).
        b2FixtureDef *fd1 = new b2FixtureDef;
        fd1->density = 0.0001;
        fd1->friction = 0.5;
        fd1->restitution = 0.f;
        fd1->shape = new b2PolygonShape;
        b2PolygonShape bs1;
        bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0);
        fd1->shape = &bs1;
        b2FixtureDef *fd2 = new b2FixtureDef;
        fd2->density = 0.0001;
        fd2->friction = 0.5;
        fd2->restitution = 0.f;
        fd2->shape = new b2PolygonShape;
        b2PolygonShape bs2;
        bs2.SetAsBox(0.2,2, b2Vec2(2.0f,0.f), 0);
        fd2->shape = &bs2;
        b2FixtureDef *fd3 = new b2FixtureDef;
        fd3->density = 0.0001;
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

        ///The bar-
        ///A shape of the form of a rectangle of dimensions 0.4 x 4 is created. 
        ///A fixture is created having this shape and the specified density and friction value.
        ///A body is created having this fixture of the rectangular shape.
        bd->position.Set(40,-32);
        b2FixtureDef *fd4 = new b2FixtureDef;
        fd4->density = 0.0003;
        fd4->friction = 0.5;
        fd4->restitution = 0.f;
        fd4->shape = new b2PolygonShape;
        b2PolygonShape bs4;
        bs4.SetAsBox(2,0.2, b2Vec2(0.f,0.f), 0);
        fd4->shape = &bs4;
        //fd1->density = 30.0;
        b2Body* box2 = m_world->CreateBody(bd);
        box2->CreateFixture(fd4);

        /// The pulley joint
        ///A variable of the type of b2PulleyJointDef is defined and the 4 anchor points are specified-
        ///One each at the left and right top (pulley anchors or Ground1 andd Ground2) and the other 
        ///two anchors on the body (Body1 and Body2). Then the pulley joint is created having these anchors 
        /// and the bodies made earlier- the open box and the rectangular bar.
        b2PulleyJointDef* myjoint = new b2PulleyJointDef();
        b2Vec2 worldAnchorOnBody1(40, -27); // Anchor point on body 1 in world axis
        b2Vec2 worldAnchorOnBody2(60, -27); // Anchor point on body 2 in world axis
        b2Vec2 worldAnchorGround1(60, -22); // Anchor point for ground 1 in world axis
        b2Vec2 worldAnchorGround2(40, -22); // Anchor point for ground 2 in world axis
        float32 ratio = 1.0f; // Define ratio
        myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
        m_world->CreateJoint(myjoint);
    }

    ///Revolving Platform at the bottom
    /// New shape is created and set as a rectangle with dimensions 6.4 x 0.4.
    ///Then a dynamic body is created having a fixture with this shape and given density and set to (36.0, -25.0).
    ///Another shape is created for a second body which will not be visible on the screen
    ///but will provide the support for the revolute joint. This body does not have a fixture . 
    ///This body can be of any shape and is set at the same cooordinates as center of initial body.
    ///To create the revolute joint, a variable of type b2RevoluteJointDef is created and these 2 bodies are set to it.
    ///The (0,0) and (0,0) indicate that the revolute joint is at the center of both bodies.
     {
	b2PolygonShape shape;
        shape.SetAsBox(3.2f, 0.2f);

        b2BodyDef bd;
        bd.position.Set(36.0f, -25.0f);
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
        bd2.position.Set(36.0f, -25.0f);
        b2Body* body2 = m_world->CreateBody(&bd2);

        b2RevoluteJointDef jointDef;
        jointDef.bodyA = body;
        jointDef.bodyB = body2;
        jointDef.localAnchorA.Set(0,0);
        jointDef.localAnchorB.Set(0,0);
        jointDef.collideConnected = false;
        m_world->CreateJoint(&jointDef);
    }

    ///The heavy sphere on the revolving platform at the bottom
    /// A circular shape is created of radius 1.0 , a dynamic body is created with the given desitites and friction
    ///having a fixture with this circular shape and the center is set to position (36,-24.4)
    {
        b2Body* sbody;
        b2CircleShape circle;
        circle.m_radius = 1.0;

        b2FixtureDef ballfd;
        ballfd.shape = &circle;
        ballfd.density = 0.01f;
        ballfd.friction = 0.0f;
        ballfd.restitution = 0.0f;
        b2BodyDef ballbd;
        ballbd.type = b2_dynamicBody;
        ballbd.position.Set(36.0f, -24.4f);
        sbody = m_world->CreateBody(&ballbd);
        sbody->CreateFixture(&ballfd);
    }
    ///Pulley system on lower right side (Left)
    {
        b2BodyDef *bd = new b2BodyDef;
        bd->type = b2_dynamicBody;
        bd->position.Set(33,-35);
        bd->fixedRotation = true;

        ///The open box-
        ///3 diffreent fixtures are created each having diffrent shapes representing the 3 sides
        /// of the open rectangular box. a body is created having these 3 fixtures (multiple fixture body)
        /// and set to the position (35,-35).
        b2FixtureDef *fd1 = new b2FixtureDef;
        fd1->density = 0.01;
        fd1->friction = 0.5;
        fd1->restitution = 0.f;
        fd1->shape = new b2PolygonShape;
        b2PolygonShape bs1;
        bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0);
        fd1->shape = &bs1;
        b2FixtureDef *fd2 = new b2FixtureDef;
        fd2->density = 0.01;
        fd2->friction = 0.5;
        fd2->restitution = 0.f;
        fd2->shape = new b2PolygonShape;
        b2PolygonShape bs2;
        bs2.SetAsBox(0.2,2, b2Vec2(2.0f,0.f), 0);
        fd2->shape = &bs2;
        b2FixtureDef *fd3 = new b2FixtureDef;
        fd3->density = 0.01;
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

        ///The bar
        ///A shape of the form of a rectangle of dimensions 0.8 x 6 is created. 
        ///A fixture is created having this shape and the specified density and friction value.
        ///A body is created having this fixture of the rectangular shape.
        bd->position.Set(23,-38);
        b2FixtureDef *fd4 = new b2FixtureDef;
        fd4->density = 0.011;
        fd4->friction = 0.5;
        fd4->restitution = 0.f;
        fd4->shape = new b2PolygonShape;
        b2PolygonShape bs4;
        bs4.SetAsBox(0.4,3, b2Vec2(0.f,0.f), 0);
        fd4->shape = &bs4;
        //fd1->density = 30.0;
        b2Body* box2 = m_world->CreateBody(bd);
        box2->CreateFixture(fd4);

        /// The pulley joint-
        ///A variable of the type of b2PulleyJointDef is defined and the 4 anchor points are specified-
        ///One each at the left and right top (pulley anchors or Ground1 andd Ground2) and the other 
        ///two anchors on the body (Body1 and Body2). Then the pulley joint is created having these anchors 
        /// and the bodies made earlier- the open box and the rectangular bar.
        b2PulleyJointDef* myjoint = new b2PulleyJointDef();
        b2Vec2 worldAnchorOnBody1(23, -38); // Anchor point on body 1 in world axis
        b2Vec2 worldAnchorOnBody2(33, -35); // Anchor point on body 2 in world axis
        b2Vec2 worldAnchorGround1(33, -28); // Anchor point for ground 1 in world axis
        b2Vec2 worldAnchorGround2(23, -28); // Anchor point for ground 2 in world axis
        float32 ratio = 1.0f; // Define ratio
        myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
        m_world->CreateJoint(myjoint);
        ///Small Edge to stop movement of the open box to an extent (connected to the door)
        /// New shape is created and set as a vector edge between the mentioned endpoints
        ///then a body is created having a fixture with this shape.
        {
            b2EdgeShape shape;
            shape.Set(b2Vec2(31.0f, -37.0f), b2Vec2(35.0f, -37.0f));
            b2BodyDef bd;
            b1 = m_world->CreateBody(&bd);
            b1->CreateFixture(&shape, 0.0f);

        }
    }

    ///Glass of water
    ///3 diffrent fixtures are created each having different shapes and the specified densities.
    ///Then a single body is created having the above 3 fixtures (combined body)
    ///Another shape is created for a second body which will not be visible on the screen
    ///but will provide the support for the revolute joint. This body does not have a fixture . 
    ///This body can be of any shape and is set at the same cooordinates as center of initial body.
    ///To create the revolute joint, a variable of type b2RevoluteJointDef is created and these 2 bodies are set to it.
    ///The (0,0) and (0,0) indicate that the revolute joint is at the center of both bodies.
    {
        b2BodyDef *bd = new b2BodyDef;
        bd->type = b2_dynamicBody;
        bd->position.Set(47,-47);
        //bd->fixedRotation = false;
        ///The open box
        b2FixtureDef *fd1 = new b2FixtureDef;
        fd1->density = 3500000.f;
        fd1->friction = 0.5;
        fd1->restitution = 0.f;
        //fd1->shape = new b2PolygonShape;
        b2PolygonShape bs1;
        bs1.SetAsBox(1,0.1, b2Vec2(0.0f,-0.9f), 0);
        fd1->shape = &bs1;
        b2FixtureDef *fd2 = new b2FixtureDef;
        fd2->density = 3500000.f;
        fd2->friction = 0.5;
        fd2->restitution = 0.f;
        //fd2->shape = new b2PolygonShape;
        b2PolygonShape bs2;
        bs2.SetAsBox(0.1,1, b2Vec2(1.0f,0.0f), 0);
        fd2->shape = &bs2;
        b2FixtureDef *fd3 = new b2FixtureDef;
        fd3->density = 3500000.f;
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
        bd2.position.Set(47.f, -47.f);
        b2Body* body2 = m_world->CreateBody(&bd2);

        b2RevoluteJointDef jointDef;
        jointDef.bodyA = box1;
        jointDef.bodyB = body2;
        jointDef.localAnchorA.Set(0,0);
        jointDef.localAnchorB.Set(0,0);
        jointDef.collideConnected = false;
        m_world->CreateJoint(&jointDef);

    }
    ///Water inside the glass of water
    // A circular shape is created of radius 0.75 . A nested for loop is run over 2 variables to 
    ///create 360 water drops which are dynamic bodies created with the given desitites and friction
    /// having a fixture with this circular shape and the center is set to position (25,33.95)
    {

        b2CircleShape shape;
        shape.m_p.Set(0, 0);
        shape.m_radius = 0.05;
        b2FixtureDef fd;
        fd.shape = &shape;
        fd.density = 200000.f;
        fd.friction = 0.0f;
        for (int j = 0; j< 20; j++)
        {
            for (int i = 0; i < 18; ++i)
            {
                b2BodyDef bd;
                bd.type = b2_dynamicBody;
                bd.position.Set(46.55f + 0.05f * i, -47.2f + 0.05f * j);
                b2Body* body = m_world->CreateBody(&bd);
                body->CreateFixture(&fd);
            }
        }
    }
    ///Lower surface having fire
    /// New shape is created and set as a vector edge between the mentioned endpoints
    ///then a body is created having a fixture with this shape.
    {
        b2EdgeShape shape;
        shape.Set(b2Vec2(35.0f, -55.0f), b2Vec2(55.0f, -55.0f));
        b2BodyDef bd;
        b1 = m_world->CreateBody(&bd);
        b1->CreateFixture(&shape, 0.0f);

    }


    ///Fire (in the form of close collection of rectangular dynamic bodies of different heights)
    ///5 different shapes are created of rectangles of varying dimensions (especially heights).
    ///A fixture having this above shape and specified density and friction is created.
    ///Using a for loop, each domino body is created with each having the same fixture as above and the position 
    ///of each differening by a fixed amount to create the chain of dominos. The combination of different height rectangles
    /// gives the effect of a burning fire.
    {
        b2PolygonShape shape;
        shape.SetAsBox(0.01f, 1.0f);

        b2FixtureDef fd;
        fd.shape = &shape;
        fd.density = 2000.0f;
        fd.friction = 1.0f;

        b2PolygonShape shape2;
        shape2.SetAsBox(0.01f, 0.8f);

        b2FixtureDef fd2;
        fd2.shape = &shape2;
        fd2.density = 2000.0f;
        fd2.friction = 0.1f;

        b2PolygonShape shape3;
        shape3.SetAsBox(0.001f, 1.7f);

        b2FixtureDef fd3;
        fd3.shape = &shape3;
        fd3.density = 2000.0f;
        fd3.friction = 0.1f;

        b2PolygonShape shape4;
        shape4.SetAsBox(0.001f, 2.2f);

        b2FixtureDef fd4;
        fd4.shape = &shape4;
        fd4.density = 2000.0f;
        fd4.friction = 0.1f;

        b2PolygonShape shape5;
        shape5.SetAsBox(0.001f, 2.8f);

        b2FixtureDef fd5;
        fd5.shape = &shape5;
        fd5.density = 2000.0f;
        fd5.friction = 0.1f;


        for (int i = 0; i < 40; ++i)
        {

            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(43.3f + 0.25f * i, -53.5f );
            b2Body* body = m_world->CreateBody(&bd);
            body->CreateFixture(&fd);

        }
        for (int i = 0; i < 10; ++i)
        {

            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(43.3f + 1.f * i, -53.5f );
            b2Body* body = m_world->CreateBody(&bd);
            body->CreateFixture(&fd2);

        }
        for (int i = 0; i < 20; ++i)
        {

            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(43.4f + 0.5f * i, -53.5f );
            b2Body* body = m_world->CreateBody(&bd);
            body->CreateFixture(&fd3);

        }
        for (int i = 0; i < 10; ++i)
        {

            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(44.f + 1.f * i, -53.5f );
            b2Body* body = m_world->CreateBody(&bd);
            body->CreateFixture(&fd4);

        }
        for (int i = 0; i < 6; ++i)
        {

            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(44.f + 1.5f * i, -53.5f );
            b2Body* body = m_world->CreateBody(&bd);
            body->CreateFixture(&fd5);

        }
    }
}
sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
