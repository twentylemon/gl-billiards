
gl-billiards
COSC 3P98 Project
Dan Lapp
Taras Mychaskiw

Run the exe
	exe/Billiards.exe

Supporting Document
	readme.pdf

Development Notes
	- We tried to get sound working. It does work somewhat, but if too many sounds fire off
	at once, then no sounds play at all. We recorded a "break" sound and throught about how to
	use that, but it's hard to determine in the middle of a collision, "is this the break?"
	To turn sounds on, go into "physics.h" and uncomment the #define SOUND_ON line, and rebuild the project.

	- We wanted to implement spin (angular momentum) in the physics, but apparently no books
	have equations for collisions between rotating objects or spheres. Figured rotating sphere
	collisions would have been around somewhere, seems pretty standard, but guess not.

	- We also tried to implement a glut sub window, containing a list of the remaining balls.
	This was almost working, but for some reason the balls would not draw. If we replaced "model.draw()"
	by "glutSolidSphere(RADIUS,..)" in Ball::draw(), then the solid spheres would draw no problem.
	Very strange.
