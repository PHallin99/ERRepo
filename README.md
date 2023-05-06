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
The second part of this project firstly involved a redesign of the original idea of the game. The original idea was having a sort of platforming game where you dodge
obstacles coming through the level while at the same time moving key objects to other objective objects. The new idea I had with the game was making a more mobile type
where you control 2 characters that can move sideways between 3 lanes and dodging obstacles coming from in front of the screen in the three lanes.

In the project, just like the part one of the turn in I kept using smart pointers in Unreal instead of naked pointers. This ensured memory safety where I don't have to
worry about deallocating memory and therefore not having to worry about memory leaks. The smart pointers also avoid some runtime errors caused by null pointers because
the smart pointers can check for null pointers.

I have used my GameMode class to do a lot of the managing of the game such as counting lives, the score, spawning in most actors and keeping track of them. I found 
this design useful for the ease of control for the flow of the game and also game state. In terms of the collision detection in the game I went with a solution where 
the logic starts at the obstacles coming at the players. Since the players characters are always on the same X axis value the entire time, the platforms only start the
collision detection checks when they are on that same X axis. The next obvious check is if the player is even in the same lane as the obstacle is traveling in. Only 
after those two test have been passed the detection can return true. This logic can be found in the Platform.cpp Tick() then also in 
AEndlessRunnerGameMode::RemoveLife(). 

The movement of the characters are designed to be instant between the 3 possible lanes to stand in. This design of not being able to control the finer adjustments of
sideways movement makes the game focus more on the reactionary and "getting in the zone" type of experience for the player where you can rack up a bunch of points
in one run very rapidly. This instant position change works in a way where I already at startup of the game have 3 predefined positions the player can stand in. One 
for every lane and they are all saved in a TArray<FVector> type. The movement then only needs to check if the player is at one of the ends of the array of positions 
before moving the player and updating the lane index of where the player is positioned. 

The games difficulty gets increased over time where every time a platform spawns the next one will be spawned at a more frequent interval and also have more movement 
speed. This uses the Unreal Timer feature where it keeps looping until the GameMode stops the Timer from doing so when the player has 0 lives left. Whenever the player 
collides with obstacles the lives go down one at a time and to make it obvious for the player, every platform gets destroyed. This happens when the detection logic 
recognizes a collision and tells the platform factory to despawn all of the spawned obstacles in the level. The timer will still be running at this point and gets
adjusted back to the starting values again only to gradually increase until the player collides again.

At this point in the project I haven't been able to get the Input working properly, the controller I spawn in possess the correct pawns and the input actions are setup
but every time I build the project there is always an Assert failure with the PlayerInputComponent which I think is connected to why I can't get the input to work.
