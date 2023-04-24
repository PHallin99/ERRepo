# Endless Runner Repo
This project is my implementation of a endless runner but more in a platformer way. The player is supposed to dodge platforms flying accross the level at different 
heights while also moving key boxes to locked objective boxes that will give the player more score. The platforms will eventually spawn at an increased rate and speed
making the game harder and harder the longer the player manages to survive.

## Part 1 Turn-in

Part 1 of the Turn-in is quite bare boned since I've never worked in Unreal or C++ before but I am making progress with my understanding of the engine and creating the
features I want in the game.

So far in the project I have not gotten much functionality in but the classes I have been working in have been the ER_Factory class creating platforms at the same place
it is located. I have made this class remember the platforms it is spawning by using smart pointers (in unreal the AActor*) for the platforms. In the process of spawning
them I use the Unreal Cast when they first get created as AActor* smart pointers then cast to APlatform* smart pointer if they successfully spawned through the engine
to avoid problems related to naked pointers. The mesh of the platforms are created with Unreals TObjectPtr smart pointers then I set their mesh to the Unreal cube mesh
and set the scale of the actor in the constructor.

The Current work I'm doing now that I've gotten myself a bit deeper into the workflow and understanding how I'll build most of the things I want in the game together 
is on my character class called EndlessRunnerCharacter and I haven't gotten the functionality to work just yet but the functions and variables I think are relevant are in
at least so far.


## Part 2 Turn-in
Not Done Yet
