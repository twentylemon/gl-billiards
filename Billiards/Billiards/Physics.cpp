/**
 * Physics.cpp
 * Game master and physics handler.
 *
 * @author Taras Mychaskiw
 * @version 1.0
 * @since 2013-12-18
**/
#include "Physics.h"
#define WONT_HAPPEN_THIS_FRAME 3600.0
static Physics* instance = NULL;

/**
 * Default constructor.
**/
Physics::Physics(void){
    /** cue to ball collision **/
    cueBallContactTime = 0.01;  //10ms
    cueSpringConstant = 10;     //10 kg m/s^2

    /** ball properties **/
    ballMass = 0.170079;        //6 oz (in kg)
    ballRadius = 0.028575;      //1.125in (in m)
    ballRadiusSq = ballRadius * ballRadius;

    /** table properties **/
    tableWidth = 9.0 * 0.0254;          //9 ft (in m), along the x axis
    tableHeight = 4.5 * 0.0254;         //4.5 ft (in m), along the y axis
    tablePlayWidth = 100.0 * 0.0254;    //100in (in m)
    tablePlayHeight = 50.0 * 0.0254;    //50in (in m)
    tableRailSize = 0;                  //don't know this

    /** animation **/
    timeStep = 0.1;
}


/**
 * Returns the instance of the physics object.
**/
Physics* Physics::getInstance(){
    if (instance == NULL){
        instance = new Physics();
    }
    return instance;
}


/**
 * Returns the hit spot on the ball sent, for { @see cueShot(Cue*, Ball*, Vector*) }
 *
 * @param cue the cue
 * @param ball the ball to find the hit spot for
 * @param x the x offset from the center of the ball
 * @param y the y offset from the center of the ball
 * @see diagram below
**/
Vector Physics::getHitSpot(Cue* cue, Ball* ball, double x, double y){
    /*  so we have a 2d circle to represent the hit spot for the UI
           ---
         /     \    C = center, no spin will be applied
        |   Cxx |   + = the spot the user will strike
         \  y +/    in this example, x = 2, y = -1
           ---
        we can find the hit spot by using the equation of a sphere
        x^2 + y^2 + z^2 = r^2
        the only unknown is z, which will have two solutions, the point closer to the
        cue is the hit point on the ball
    */
    double z = sqrt(ballRadiusSq - x*x - y*y);
    Vector neg = Vector(x, y, -z);
    Vector pos = Vector(x, y, z);
    double negDist = cue->getPosition().distance(x, y, -z);
    double posDist = cue->getPosition().distance(x, y, z);
    if (cue->getPosition().distance(neg) < cue->getPosition().distance(pos)){
        return Vector::add(cue->getPosition(), neg);
    }
    return Vector::add(cue->getPosition(), pos);
}


/**
 * Takes a shot. Returns the velocity of the ball after the shot occurs.
 * The distance between the cue and the ball determines the power of the shot.
 *
 * @param cue the cue
 * @param ball the ball being struck by the cue
 * @return the speed that the ball struck should be travelling
**/
Vector Physics::cueShot(Cue* cue, Ball* ball){
    /*  assume the Cue acts like a spring, and apply Hooke's law
        - k t
    v = ------  x
           m
        where k is the spring constant
              t is the amount of time the cue is in contact with the ball
              m is the mass of the ball
              x is the direction vector between the ball and the cue
              v the the need velocity of the ball
    */

    //get the vector between the cue and the ball
    Vector direction = Vector::subtract(ball->getPosition(), cue->getPosition());
    direction.scale(-cueSpringConstant * cueBallContactTime / ballMass);
    return direction;
}


/**
 * Takes a shot with spin. (Wish I could return multiple values.)
 * 
 * @param cue the cue
 * @param ball the ball being struck by the cue
 * @param hitSpot where the ball will be struck by the cue
 * @return the rotational velocity that the ball with have after the shot
 * @see Phyics::cueShot(Cue*, Ball*)
**/
Vector Physics::cueShot(Cue* cue, Ball* ball, Vector hitSpot){
    /* this one is more complex, hitting the ball off center applies torque
        torque needs to overcome the rotational interia of the ball
        dw              2
        -- = I_sphere = - m R^2
        dt              5
        where m is the mass of the sphere (ball)
              R is the radius of the sphere
              w is the rotational velocity

        torque:
        T = r x F  = r x (-kx)
        where r is the vector between the point of rotation and where the force is applied
              F is the force applied, in our case is Hooke's Law, so F = -kx { @see cueShot(Cue*, Ball*) }

        so setting them equal to each other, and assuming the initial rotation velocity is zero, we get
              5 t
        w = ------- r x -kx
            2 m R^2
    */
    //get the vector from the center of the ball's rotation to the hitSpot
    Vector r = Vector::subtract(hitSpot, ball->getPosition());
    
    //get the vector between the cue and the ball
    Vector x = Vector::subtract(ball->getPosition(), cue->getPosition());
    x.scale(-cueSpringConstant);

    Vector omega = Vector::crossProduct(r, x);
    omega.scale(5.0 * cueBallContactTime / (2.0 * ballMass * ballRadiusSq));
    return omega;
}


/**
 * Takes a shot with spin. (Wish I could return multiple values.)
 * 
 * @param cue the cue
 * @param ball the ball being struck by the cue
 * @param x the x offset from the center of the ball
 * @param y the y offset from the center of the ball
 * @return the rotational velocity that the ball with have after the shot
 * @see Phyics::cueShot(Cue*, Ball*), Physics::getHitSpot(Cue*, Ball*, double, double)
**/
Vector Physics::cueShot(Cue* cue, Ball* ball, double x, double y){
    return cueShot(cue, ball, getHitSpot(cue, ball, x, y));
}


/**
 * Does the actual movement of the pool balls. No events will occur within dt, so we can just roll
 * them happily along. We do have to check for pocketed balls though.
 *
 * @param balls the set of balls to update
 * @param dt the amount of time to pass
**/
void Physics::rollBalls(std::vector<Ball*> balls, double dt){
    for (unsigned int i = 0; i < balls.size(); i++){
        if (!balls[i]->isSunk() && balls[i]->isMoving()){
            //get how far they moved
            Vector dr = Vector::scale(balls[i]->getVelocity(), dt);
            balls[i]->setPosition(Vector::add(balls[i]->getPosition(), dr));

            // TODO check if they sunk into pockets
        }
    }
}


/**
 * Calculates when the two balls will collide and returns when they will, in seconds.
 *
 * @param ball1 one ball
 * @param ball2 the ball ball1 may collide with
 * @return the amount of time that will pass before ball1 and ball2 collide
**/
double Physics::calcCollisionTime(Ball* ball1, Ball* ball2){
    /* the two balls collide when they are 2 radii apart, and we know their position over time is
        r = s + vt
        where s is the starting position
              v is the velocity
              t is the time elapsed
        we get...
        |r1 - r2| = 2R
        | |s1 - s2| + 2(s1 - s2)(v1 - v2)t + |v1 - v2|t^2 | = 2R
        where |x| is the length of x
              R is the radius of a ball
        solving for t gives a quadratic equation
    */
    //get their differences in position and velocity
    Vector dr = Vector::subtract(ball1->getPosition(), ball2->getPosition());   //s1 - s2
    Vector dv = Vector::subtract(ball1->getVelocity(), ball2->getVelocity());   //v1 - v2

    double a = Vector::dotProduct(dv, dv);
    double b = Vector::dotProduct(dr, dv) / a;
    double c = (Vector::dotProduct(dr, dr) - 4.0 * ballRadiusSq) / a;
    /* now t^2 + 2bt + c = 0; */
    //check for imaginary roots
    c = b*b - c;
    if (c > 0){
        c = sqrt(c);
        return std::min(-b + c, -b - c);
    }
    return WONT_HAPPEN_THIS_FRAME;
}


/**
 * Calculates when the ball with hit the bank axis specified
 *
 * @param ball the ball to check when it hits the bank
 * @param axis which bank axis we are checking against, X axis or Y
 * @return the amount of time that will pass before ball hits the bank
**/
double Physics::calcBankTime(Ball* ball, Event::BankAxis axis){
    double pos = 0, speed = 0;
    double rail = 0;
    //determne when the ball will hit (rail, 0, 0) or (0, rail, 0)
    if (axis == Event::BankAxis::X){
        pos = ball->getPosition(Vector::X);
        speed = ball->getVelocity(Vector::X);
        rail = tablePlayWidth / 2.0;    //divide by 2 since center of table is (0,0,0)
    }
    else if (axis == Event::BankAxis::Y){
        pos = ball->getPosition(Vector::Y);
        speed = ball->getVelocity(Vector::Y);
        rail = tablePlayHeight / 2.0;
    }
    if (speed > 0){
        return std::abs((rail - ballRadius) / speed);
    }
    return WONT_HAPPEN_THIS_FRAME;
}


/**
 * Moves all of the balls. Loops through every ball to check if any events occur with time dt,
 * such as a collision or a bank. If one occurs, the game is played up until the event, then the event
 * is handled. After which, we just recurse until a total time dt is reached.
 *
 * @param balls the set of balls to update
 * @param dt the amount of time passed sicne the last frame
**/
void Physics::moveBalls(std::vector<Ball*> balls, double dt){
    Event event = Event(dt);

    //check if any balls will collide with each other or the rails within time dt
    //find the earliest event that will occur
    for (unsigned int i = 0; i < balls.size(); i++){
        if (!balls[i]->isSunk() && balls[i]->isMoving()){
            //check for collisions with other balls
            for (unsigned int j = 0; j < balls.size(); j++){
                if (i != j){
                    double collisionTime = calcCollisionTime(balls[i], balls[j]);
                    if (collisionTime >= 0 && collisionTime < event.getTime()){
                        event = CollisionEvent(collisionTime, balls[i], balls[j]);
                    }
                }
            }

            //check for a bank off the side
            double bankTimeX = calcBankTime(balls[i], Event::BankAxis::X);
            double bankTimeY = calcBankTime(balls[i], Event::BankAxis::Y);
            if (bankTimeX >= 0 && bankTimeX < event.getTime()){
                event = BankEvent(bankTimeX, balls[i], Event::BankAxis::X);
            }
            if (bankTimeY >= 0 && bankTimeY < event.getTime()){
                event = BankEvent(bankTimeY, balls[i], Event::BankAxis::Y);
            }
        }
    }

    //update the positions of all balls up until the event occurs, or until dt is reached if none
    rollBalls(balls, event.getTime());

    //handle the event, if any
    event.handle();

    //recurse if need be
    if (event.getTime() < dt){
        moveBalls(balls, dt - event.getTime());
    }
}


/**
 * Updates all of the positions/speeds of the balls, does collisions etc if needed.
 * The default time step is used.
 *
 * @param balls the set of balls to update
 * @return true if any balls are still moving on the table
**/
bool Physics::update(std::vector<Ball*> balls){
    return update(balls, timeStep);
}


/**
 * Updates all of the positions/speeds of the balls, does collisions etc if needed.
 *
 * @param balls the set of balls to update
 * @param dt the amount of time passed sicne the last frame
 * @return true if any balls are still moving on the table
**/
bool Physics::update(std::vector<Ball*> balls, double dt){
    moveBalls(balls, dt);
    return true;
}


/**
 * Destructor.
**/
Physics::~Physics(void){
}
