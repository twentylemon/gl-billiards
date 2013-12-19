/**
 * Game master and physics handler.
 *
 * @author Taras Mychaskiw
 * @version 1.0
 * @since 2013-12-18
**/
#include "Physics.h"
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

    /** table properties **/
    tableWidth = 2.7432;        //9 ft (in m), along the x axis
    tableHeight = 1.3716;       //4.5 ft (in m), along the y axis
    tableRailSize = 0;          //don't know this
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
 * Returns the hit spot on the ball sent, for { @see cueShot(Cue*, Ball*, Array3*) }
 *
 * @param cue the cue
 * @param ball the ball to find the hit spot for
 * @param x the x offset from the center of the ball
 * @param y the y offset from the center of the ball
 * @see diagram below
**/
Array3* Physics::getHitSpot(Cue* cue, Ball* ball, double x, double y){
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
    double z = sqrt(ballRadius*ballRadius - x*x - y*y);
    double negDist = cue->getPosition()->distance(x, y, -z);
    double posDist = cue->getPosition()->distance(x, y, z);
    if (negDist < posDist){
        return Array3::add(cue->getPosition(), x, y, -z);
    }
    return Array3::add(cue->getPosition(), x, y, z);
}


/**
 * Takes a shot. Returns the velocity of the ball after the shot occurs.
 * The distance between the cue and the ball determines the power of the shot.
 *
 * @param cue the cue
 * @param ball the ball being struck by the cue
 * @return the speed that the ball struck should be travelling
**/
Array3* Physics::cueShot(Cue* cue, Ball* ball){
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
    Array3* direction = Array3::subtract(ball->getPosition(), cue->getPosition());
    direction->multiply(-cueSpringConstant * cueBallContactTime / ballMass);
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
Array3* Physics::cueShot(Cue* cue, Ball* ball, Array3* hitSpot){
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
    Array3* r = Array3::subtract(hitSpot, ball->getPosition());
    
    //get the vector between the cue and the ball
    Array3* x = Array3::subtract(ball->getPosition(), cue->getPosition());
    x->multiply(-cueSpringConstant);

    Array3* omega = Array3::crossProduct(r, x);
    omega->multiply(5.0 * cueBallContactTime / ( 2.0 * ballMass * ballRadius * ballRadius));
    delete r, x;
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
Array3* Physics::cueShot(Cue* cue, Ball* ball, double x, double y){
    Array3* hitSpot = getHitSpot(cue, ball, x, y);
    Array3* omega = cueShot(cue, ball, hitSpot);
    delete hitSpot;
    return omega;
}


/**
 * Destructor.
**/
Physics::~Physics(void){
}
