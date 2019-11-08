# CIS_17B_Final_Project

# Major Update 09/07/2019:
We are using the design method and base engine layed out by
the YouTube channel "Let's Make Games"

https://www.youtube.com/user/creaper/about

As of this update I have finished video #12. This is between 2-3 hours of content.
I have uploaded my version of the project with necessary (mostly trivial) differences
so far. This is the folder **BirchEngine_Mod** and I think we should stick with this.

## So What Does This Thing Do?

The BirchEngine is just what this guy is calling his project. The majority of code here
is from the SDL2 and SDL_image libraries. However, I expect that to tilt towards original,
object-oriented code for the remainder of videos until we have the minimum we need to jump off.

## What is ECS?

"ECS" := "Entity-Component System". This is a design pattern where objects can be assigned properties that have their own override methods for Init(), Draw(), Update(), Render(), etc. which keeps us from having to have a laundry list of code several times in the game loop. If a component needs to render something to the screen as an animation, it will do that via its own Init(), Update(), and Render Functions at runtime, but these are defined in that component's class files, not in the game loop.

This is how Unity works.

## Roles:

Spencer Trumbore: Physics, BirchEngine de-mystifier

## Brainstorm
### Keep in mind we are a larger group. Must have a bigger but still managable scope
* Top Down 2D RPG
* collect to build to fight
* leveling system: gear or point based (decided)
  * stats? skills?
* story based - linear ? optional ?
  * Laura will have a draft
  * nvm - keeping it simple
  * text will be simple, just for tutorial
 * real time combat
 * story
  * what gets the player going?
  * 3 levels - get mcguffin - win game
   * this may also need to be simplified
  * comedy

## TODO
* Learn more about SDL -- see what we can do
 * upload to github
* flesh out combat system
* flesh out crafting mechanics
* once we find our focus, assign roles

## End Goal
* ~ 6 weeks to make
