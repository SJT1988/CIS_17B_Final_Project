# CIS_17B_Final_Project

# Major Update 11/10/19

Repo updated. Unnecessary files removed, untangled and then deleted old repos (sorry for the confusion).

We are using the design method and base engine layed out by **Carl Birch** on
the YouTube channel [**Let's Make Games**](https://www.youtube.com/user/creaper/about).

As of this update I have finished video **#19** (Scrolling Map & Press ESC to Quit). The scrolling map part is not implemented, I skipped most of the [short] video. This project is the result of at least 3 hours of tutorials so far.
I have uploaded my version of the project with necessary (mostly trivial) differences
so far. This is the folder **BirchEngine_Mod** and I think we should stick with this.

## So What Does This Thing Do?

The BirchEngine is just what this guy is calling his project. The majority of code here
is from the SDL2 and SDL_image libraries. However, I expect that to tilt towards original,
object-oriented code for the remainder of videos until we have the minimum we need to jump off.

## What is ECS?

"ECS" := "Entity-Component System". This is a design pattern where objects can be assigned properties that have their own override methods for Init(), Draw(), Update(), Render(), etc. which keeps us from having to have a laundry list of code several times in the game loop. If a component needs to render something to the screen as an animation, it will do that via its own Init(), Update(), and Render Functions at runtime, but these are defined in that component's class files, not in the game loop.

This is how Unity works.

## If Something Doesn't Work...

...it is because of either of 2 things, one broad, one specific:
1. I use Windows. Kristian uses Liux. William uses Windows on a Mac. 9/10 problems you
will encounter will be LINKER errors. this means that the project is not properly set up to locate the SDL and SDL_Image
libraries.
    * This can be resolved in **Visual Studio 2017** on **Windows** by following [**this tutorial**](https://www.youtube.com/watch?v=QQzAHcojEKg).
    * This can be resolved in **XCode** on a **Mac** by following [**this tutorial**](https://www.youtube.com/watch?v=lHAUc6F_B3Y).
Both tutorials are by the author of the project our SDL tutorials are using.
    * Keep in mind that whatever you do for the SDL2 library, you will need to do almost the same for the SDL_Image library. I have already included the necessary dll's from both directories in the project. If you are struggling to get up and running, PLEASE do not be too embarrassed to ask for assistance. I know what a pain in the ass this whole thing is.


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

* see "Projects"
* Learn more about SDL -- see what we can do
 * upload to github
* flesh out combat system
* flesh out crafting mechanics
* once we find our focus, assign roles

## End Goal
* ~ 6 weeks to make
