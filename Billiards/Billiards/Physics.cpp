/**
 * physics.cpp
 * Game master and physics handler.
 *
 * @author Taras Mychaskiw
 * @version 1.0
 * @since 2013-12-18
**/
#include "physics.h"
#define WONT_HAPPEN_THIS_FRAME 3600.0

namespace physics {

/**
 * Cushion constructor.
 *
 * @param start where this cushion starts
 * @param finish where this cushion ends
 * @param radius the radius of each ball
**/
Cushion::Cushion(Vector start, Vector finish, double radius){
    this->start = start;
    this->finish = finish;
    line = Vector::subtract(finish, start);
    normal = Vector::normalize(line.crossProduct(Vector(0, 0, 1)));
    negRadius = Vector::scale(normal, -1.0);
    length = line.length();
    lengthSq = line.lengthSq();
    setRadius(radius);
}


/**
 * Getters/Setters
**/
void Cushion::setRadius(double ballRadius){ negRadius.normalize(ballRadius); }
Vector Cushion::getStart(){ return start; }
Vector Cushion::getFinish(){ return finish; }
Vector Cushion::getLine(){ return line; }
Vector Cushion::getNormal(){ return normal; }
Vector Cushion::getNegRadius(){ return negRadius; }
double Cushion::getLength(){ return length; }
double Cushion::getLengthSq(){ return lengthSq; }


/**
 * Event constructor. Just stores the original dt for the frame time span.
 *
 * @param dt the time at which this event occurs
**/
Event::Event(double dt){
    time = dt;
}


/**
 * Getters/Setters.
**/
double Event::getTime(){ return time; }


/**
 * CollisionEvent constructor.
 *
 * @param time the time at which this event occurs
 * @param ball1 the first ball in the collision
 * @param ball2 the second ball in the collision
**/
CollisionEvent::CollisionEvent(double time, Ball* ball1, Ball* ball2) : Event(time){
    this->ball1 = ball1;
    this->ball2 = ball2;
}


/**
 * Handles speed updates of the collision event.
**/
void CollisionEvent::handle(){
    //got the normal to the collision plane
    Vector normal = Vector::subtract(ball1->getPosition(), ball2->getPosition());
    normal.normalize();
    Vector negNormal = Vector::scale(normal, -1.0);

    //find the normal/tangential components for each of the balls velocities
    Vector norm1 = Vector::scale(negNormal, Vector::dotProduct(ball1->getVelocity(), negNormal));
    Vector tan1 = Vector::subtract(ball1->getVelocity(), norm1);
    Vector norm2 = Vector::scale(normal, Vector::dotProduct(ball2->getVelocity(), normal));
    Vector tan2 = Vector::subtract(ball2->getVelocity(), norm2);

    //conservation of linear momentum, assume the collision is 100% elastic
    ball1->setVelocity(Vector::add(tan1, norm2));
    ball2->setVelocity(Vector::add(tan2, norm1));
}


/**
 * BankEvent constructor.
 *
 * @param time the time at which this event occurs
 * @param ball the ball involved in the bank
 * @param axis the bank axis against which the ball hits
**/
BankEvent::BankEvent(double time, Ball* ball, Cushion cushion) : Event(time){
    this->ball = ball;
    this->cushion = cushion;
}


/**
 * Handles the velocity update after a bank event.
**/
void BankEvent::handle(){
    Vector velocity = ball->getVelocity();
    Vector normal = cushion.getNormal();

    //reflect the velocity through the cushion normal
    normal.scale(2.0 * velocity.dotProduct(normal));
    velocity.subtract(normal);

    //loss some speed due to friction
    velocity.scale(1.0 - cushionFrictionLoss);
    ball->setVelocity(velocity);

    if (getTime() == 0){
        //if it happened at 0 seconds, add a larger bounce
        ball->addPosition(Vector::scale(cushion.getNormal(), 0.002));
    }
    ball->addPosition(Vector::scale(cushion.getNormal(), 0.001));   //add a little bounce
}


/**
 * Takes a shot. Returns the velocity of the ball after the shot occurs.
 * The distance between the cue and the ball determines the power of the shot.
 *
 * @param cue the cue
 * @param ball the ball being struck by the cue
 * @return the speed that the ball struck should be travelling
**/
Vector cueShot(Cue cue, Ball* ball){
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
 * @param ball the ball to check
 * @param cushion the cushion to check
 * @return the squared distance between the ball and the cushion
**/
double distance(Ball* ball, Cushion cushion){
    Vector position = ball->getPosition();
    double t = cushion.getLine().dotProduct(Vector::subtract(position, cushion.getStart()));
    if (t < 0){
        return cushion.getStart().distance(position);
    }
    else if (t > 1){
        return cushion.getFinish().distance(position);
    }
    Vector proj = Vector::add(cushion.getStart(), Vector::scale(cushion.getLine(), t));
    return proj.distance(position);
}


/**
 * @param position to point to check if it's near/in a pocket
 * @return which pocket it should fall into, or -1 if none
**/
int detectPocket(Vector position){
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
void rollBalls(std::vector<Ball*> balls, double dt){
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
                std::cerr << "Ball " << i << " has been pocketed." << std::endl;
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
double calcCollisionTime(Ball* ball1, Ball* ball2){
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
double calcBankTime(Ball* ball, Cushion cushion, double dt){
    if (distance(ball, cushion) < ballRadiusSq){
        return 0;
    }
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
        return dist.length() / velocity.length();
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
void moveBalls(std::vector<Ball*> balls, double dt){
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
 * The value in firstCueHit will be modified if the cue ball hits something this frame.
 * firstCueHit will be 0 if the cue ball hit nothing this frame, otherwise the ball number.
 *
 * @param balls the set of balls to update
 * @param dt the amount of time passed sicne the last frame
 * @return true if any balls are still moving on the table
**/
bool update(std::vector<Ball*> balls, double dt){
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
}
