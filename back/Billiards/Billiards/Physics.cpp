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
Physics::Physics(){
    /** cue to ball collision **/
    cueBallContactTime = 0.01;  //10ms
    cueSpringConstant = 100;     //10 kg m/s^2

    /** ball properties **/
    ballMass = 0.170079;        //6 oz (in kg)
    ballRadius = 0.028575;      //1.125in (in m)
    ballRadiusSq = ballRadius * ballRadius;
    ballCircumference = 2.0 * PI * ballRadius;

    /*     width                 ^
     4--------5--------0 h     y |
     |                 | e
     |                 | i     x
     |                 | g     ->
     3--------2--------1 h
   pocket nums labelled  t
    */
    /** table properties **/
    tableWidth = 9.0 * 0.0254;          //9 ft (in m), along the x axis
    tableHeight = 4.5 * 0.0254;         //4.5 ft (in m), along the y axis
    tableRailSize = 4 * 0.0254 / 2.0;   //4in (in m), divided by 2
    tablePlayWidth = 100.0 * 0.0254;    //100in (in m)
    tablePlayHeight = 50.0 * 0.0254;    //50in (in m)

    /** pockets **/
    numPockets = 6;
    pocketSize = 4.8 * 0.0254 / 2.0;    //actually corner = 4.5, side = 5 in, close enough
    pockets[0] = Vector(tablePlayWidth / 2.0 + tableRailSize, tablePlayHeight / 2.0 + tableRailSize, 0);
    pockets[1] = Vector(tablePlayWidth / 2.0 + tableRailSize, -tablePlayHeight / 2.0 - tableRailSize, 0);
    pockets[2] = Vector(0, -tablePlayHeight / 2.0 - tableRailSize, 0);
    pockets[3] = Vector(-tablePlayWidth / 2.0 - tableRailSize, -tablePlayHeight / 2.0 - tableRailSize, 0);
    pockets[4] = Vector(-tablePlayWidth / 2.0 - tableRailSize, tablePlayHeight / 2.0 + tableRailSize, 0);
    pockets[5] = Vector(0, tablePlayHeight / 2.0 + tableRailSize, 0);

    /** cushions **/
    railSize = 2.0 * 0.0254;
    makeCushions();

    /** friction **/
    feltFriction = 0.005;
    velocityStop = 0.01 * 0.01; //use squared value so we can use squared length
    angularStop = 0.05;
    gravity = 9.8;

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
 * Constructor helper. Makes the cuhsions.
**/
void Physics::makeCushions(){
    double scale = 0.0254;
    //corner to corner, corner to side coords
    double ctcx[3], ctcy[3], ctsx[5], ctsy[5];
    double offset = 1.0/32.0 * scale;   //try to fix some bugs by extending some rails

    ctcx[0] = 52 + 17.0/32.0;   ctcy[0] = 24 + 3.0/32.0;
    ctcx[1] = 51 + 15.0/32.0;   ctcy[1] = 23;
    ctcx[2] = 50;               ctcy[2] = 20 + 16.0/32.0;

    ctsx[0] = 48 + 30.0/32.0;   ctsy[0] = 27 + 16.0/32.0;
    ctsx[1] = 47 + 31.0/32.0;   ctsy[1] = 26 + 16.0/32.0;
    ctsx[2] = 45 + 19.0/32.0;   ctsy[2] = 24 + 31.0/32.0;
    ctsx[3] = 3 + 3.0/32.0;     ctsy[3] = 25;
    ctsx[4] = 2 + 12.0/32.0;    ctsy[4] = 27 + 16.0/32.0;

    for (int i = 0; i < 5; i++){
        if (i < 3){
            ctcx[i] *= scale;   ctcy[i] *= scale;
        }
        ctsx[i] *= scale;   ctsy[i] *= scale;
    }

    numCushions = 26;

    /** from pocket 0 to pocket 1 **/
    cushions[0] = Cushion(Vector(ctcx[0], ctcy[0], 0), Vector(ctcx[1], ctcy[1], 0));
    cushions[1] = Cushion(Vector(ctcx[1], ctcy[1], 0), Vector(ctcx[2], ctcy[2], 0));
    cushions[2] = Cushion(Vector(ctcx[2], ctcy[2], 0), Vector(ctcx[2], -ctcy[2], 0));
    cushions[3] = Cushion(Vector(ctcx[2], -ctcy[2], 0), Vector(ctcx[1], -ctcy[1], 0));
    cushions[4] = Cushion(Vector(ctcx[1], -ctcy[1], 0), Vector(ctcx[0], -ctcy[0], 0));

    /** from pocket 1 to pocket 2 **/
    cushions[5] = Cushion(Vector(ctsx[0], -ctsy[0], 0), Vector(ctsx[1], -ctsy[1], 0));
    cushions[6] = Cushion(Vector(ctsx[1], -ctsy[1], 0), Vector(ctsx[2], -ctsy[2], 0));
    cushions[7] = Cushion(Vector(ctsx[2], -ctsy[2], 0), Vector(ctsx[3], -ctsy[3], 0));
    cushions[8] = Cushion(Vector(ctsx[3], -ctsy[3], 0), Vector(ctsx[4], -ctsy[4], 0));

    /** pocket 2 to pocket 3 **/
    cushions[9] = Cushion(Vector(-ctsx[4], -ctsy[4], 0), Vector(-ctsx[3], -ctsy[3], 0));
    cushions[10] = Cushion(Vector(-ctsx[3], -ctsy[3], 0), Vector(-ctsx[2], -ctsy[2], 0));
    cushions[11] = Cushion(Vector(-ctsx[2], -ctsy[2], 0), Vector(-ctsx[1], -ctsy[1], 0));
    cushions[12] = Cushion(Vector(-ctsx[1], -ctsy[1], 0), Vector(-ctsx[0], -ctsy[0], 0));

    /** pocket 3 to pocket 4 **/
    cushions[13] = Cushion(Vector(-ctcx[0], -ctcy[0], 0), Vector(-ctcx[1], -ctcy[1], 0));
    cushions[14] = Cushion(Vector(-ctcx[1], -ctcy[1], 0), Vector(-ctcx[2], -ctcy[2], 0));
    cushions[15] = Cushion(Vector(-ctcx[2], -ctcy[2], 0), Vector(-ctcx[2], ctcy[2], 0));
    cushions[16] = Cushion(Vector(-ctcx[2], ctcy[2], 0), Vector(-ctcx[1], ctcy[1], 0));
    cushions[17] = Cushion(Vector(-ctcx[1], ctcy[1], 0), Vector(-ctcx[0], ctcy[0], 0));
    
    /** pocket 4 to pocket 5 **/
    cushions[18] = Cushion(Vector(-ctsx[0], ctsy[0], 0), Vector(-ctsx[1], ctsy[1], 0));
    cushions[19] = Cushion(Vector(-ctsx[1], ctsy[1], 0), Vector(-ctsx[2], ctsy[2], 0));
    cushions[20] = Cushion(Vector(-ctsx[2], ctsy[2], 0), Vector(-ctsx[3], ctsy[3], 0));
    cushions[21] = Cushion(Vector(-ctsx[3], ctsy[3], 0), Vector(-ctsx[4], ctsy[4], 0));

    /** pocket 5 to pocket 0 **/
    cushions[22] = Cushion(Vector(ctsx[4], ctsy[4], 0), Vector(ctsx[3], ctsy[3], 0));
    cushions[23] = Cushion(Vector(ctsx[3], ctsy[3], 0), Vector(ctsx[2], ctsy[2], 0));
    cushions[24] = Cushion(Vector(ctsx[2], ctsy[2], 0), Vector(ctsx[1], ctsy[1], 0));
    cushions[25] = Cushion(Vector(ctsx[1], ctsy[1], 0), Vector(ctsx[0], ctsy[0], 0));

    /** normalize each negRadius to be length ballRadius **/
    for (int i = 0; i < numCushions; i++){
        cushions[i].setRadius(ballRadius);
    }
}


/**
 * Takes a shot. Returns the velocity of the ball after the shot occurs.
 * The distance between the cue and the ball determines the power of the shot.
 *
 * @param cue the cue
 * @param ball the ball being struck by the cue
 * @return the speed that the ball struck should be travelling
**/
Vector Physics::cueShot(Cue cue, Ball* ball){
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
    Vector direction = Vector::subtract(ball->getPosition(), cue.getPosition());
    direction.scale(cueSpringConstant * cueBallContactTime / ballMass);
    return direction;
}


/**
 * @param position to point to check if it's near/in a pocket
 * @return which pocket it should fall into, or -1 if none
**/
int Physics::detectPocket(Vector position){
    for (int p = 0; p < numPockets; p++){
        if (pockets[p].distance(position) < 2.0 * pocketSize * pocketSize){//4.0 * ballRadiusSq){
            return p;
        }
    }
    return -1;
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
            balls[i]->addPosition(dr);

            //rotate each ball
            Vector angle = Vector();
            double theta = 360.0 * dr.length() / ballCircumference;
            Vector axis = dr.crossProduct(Vector(0, 0, -1));
            balls[i]->pushRotation(axis, theta);

            //check for pocketing
            int p = detectPocket(balls[i]->getPosition());
            if (p != -1){
                std::cerr << "Ball " << i << " has been pocketed." << std::endl << balls[i]->getPosition().toString() << std::endl << pockets[p].toString() << std::endl;
                balls[i]->sink();
            }
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
    //now t^2 + 2bt + c = 0;
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
 * @param cushion which cushion we are checking against
 * @param dt the amount of time that will pass this frame (so far at least)
 * @return the amount of time that will pass before ball hits the bank
**/
double Physics::calcBankTime(Ball* ball, Cushion cushion, double dt){
    Vector position = ball->getPosition();
    Vector velocity = ball->getVelocity();
    Vector ballDirection = Vector::scale(velocity, dt);
    Vector wallDirection = cushion.getLine();
    Vector start = cushion.getStart();

    //offset the position by ballRadius in the opposite direction to the cushion normal
    position.add(cushion.getNegRadius());

    Vector diff = Vector::subtract(start, position);

    //get parametric forms of the lines
    double div = ballDirection.getY()*wallDirection.getX() - ballDirection.getX()*wallDirection.getY();
    double tBall = (wallDirection.getX()*diff.getY() - wallDirection.getY()*diff.getX()) / div;
    double tWall = (ballDirection.getX()*diff.getY() - ballDirection.getY()*diff.getX()) / div;

    if (tWall >= 0 && tBall >= 0 && tWall <= 1 && tBall <= 1){
        Vector collision = Vector::add(position, Vector::scale(ballDirection, tBall));
        Vector dist = Vector::subtract(collision, position);
        double time = dist.length() / velocity.length();
        if (time < dt){
            //std::cerr << tBall << std::endl;
        }
        return time;
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
    Event* event = new Event(dt);

    //check if any balls will collide with each other or the rails within time dt
    //find the earliest event that will occur
    for (unsigned int i = 0; i < balls.size(); i++){
        if (!balls[i]->isSunk() && balls[i]->isMoving()){
            //check for collisions with other balls
            for (unsigned int j = 0; j < balls.size(); j++){
                if (i != j){
                    double collisionTime = calcCollisionTime(balls[i], balls[j]);
                    if (collisionTime >= 0 && collisionTime < event->getTime()){
                        delete event;
                        event = new CollisionEvent(collisionTime, balls[i], balls[j]);
                    }
                }
            }
            
            //check for a bank off the side
            for (int c = 0; c < numCushions; c++){
                double bankTime = calcBankTime(balls[i], cushions[c], dt);
                if (bankTime >= 0 && bankTime < event->getTime()){
                    delete event;
                    event = new BankEvent(bankTime, balls[i], cushions[c]);
                }
            }
        }
    }

    //update the positions of all balls up until the event occurs, or until dt is reached if none
    rollBalls(balls, event->getTime());

    //handle the event, if any
    event->handle();

    //recurse if need be
    if (event->getTime() < dt){
        moveBalls(balls, dt - event->getTime());
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
    bool ballsMoving = false;

    /** calculate new velocities **/
    for (unsigned int i = 0; i < balls.size(); i++){
        if (!balls[i]->isSunk() && balls[i]->isMoving()){
            ballsMoving = true;

            //scale by negative friction so it slows down
            Vector friction = Vector::scale(balls[i]->getVelocity(), -feltFriction);
            balls[i]->addVelocity(friction);
            
            if (balls[i]->getVelocity().lengthSq() < velocityStop){
                balls[i]->stopMoving();
            }
        }
        else {
            balls[i]->consolidateRotation();
        }
    }

    return ballsMoving;
}


/**
 * Destructor.
**/
Physics::~Physics(void){
}
