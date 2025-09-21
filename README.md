# Space Invaders - CS50 Final Project
#### Video Demo:  <URL HERE>
#### Running the game
1. Clone the repository:
-> git clone https://github.com/plutial/space-invaders.git
2. Go into the directory:
-> cd space-invaders
3. Build and run the game:
-> make clean; make run

### Dependencies
cmake, gcc

#### Description
The game is built with Raylib, a library for opening windows, rendering sprites, playing audio etc.
For cross-platform compatibility, the game is built with cmake.

The objective of the game is to get the highest score possible. The score is shown in the bottom-left corner of the screen.
If the player gets hit by an enemy's bullet, or when the enemy gets too close to the player, the player will lose the game.

To move the player, use WASD or Arrows Keys.
To attack, press the spacebar or click the left mouse button.

#### How does the project work?
body.h, entity.h, sprite.h, and sprite.c are used to make low-level functions more high-level, so that it is easier to work with. They allow for structures to be used that are helpful, but not necessarily in the Raylib library. For example, the sprite structure makes it easier to render the textures.

player.h and player.c control the player. The NewPlayer function initializes the player. It sets the scaling of the sprite, sets the player's initial position, loads the player's texture, and set the source and destination rectangles for the sprite. The MovePlayer function takes in input from the user and moves the player. The function also prevents the player from going out of bounds by setting the limits of the player to the bounds of the screen. The PlayerAttack function is responsible for the attack of the enemy. Firstly, it sets a delay. This stops the player from constantly shooting bullets, and controls how frequently the player can shoot bullets. Then, when it takes an input, it checks to see if the delay is over. If the delay is over, then the bullet is shot, and then the delay is reset. When the player shoots a bullet, a sound is made.

enemy.h and enemy.c control the enemy. The groups of enemies are stored in a structure called Army, which stores data such as: the number of alive enemies, the width of the army, the height of the army, the alive/dead of the enemies etc. The NewArmy initializes the army, and the enemies in it. The UpdateArmy updates the enemies' positions and the delay of the updates. It also controls the movement of the army. The ArmyAttack function picks a random alive enemy, and makes it attack. This attack is called every enemy delay (the delay is stored and calculated separately in the structure). The RenderArmy renders all alive enemies' sprites.

bullet.h and bullet.c control the bullets. The bullets have owners: the player and the enemy. This is used later in collision calculations. The bullets are stored in BulletArray. The structure stores the bullets and their metadata. The capacity of the array is 100 by default, as it is near impossible for 100 bullets to be on the screen at the same time. The AddBullet function takes in the BulletArray and the Bullet and appends it to the array; the UpdateBullets function updates their positions, and RenderBullets the rendering.

tile.h and tile.c are like their bullet counterparts with them having a specific array for them. However, the tiles are created at intiailization when the NewTileArray function is called. The function creates the tiles by creating the five tile barrier, four times, across the screen. The tiles serve as a defense for the player, but can be broken by the player.

All the structures and code come into play in collisions.h and collisions.c. The only function in collisions.h is UpdateCollisions, but the function is actually made up of many parts: BodyCollisions, UpdateTileCollsions, and UpdateEnemyCollsions. The BodyCollisions takes in two bodies, and returns true if they overlap, and false if not. The UpdateTileCollsions updates the tile collisions, then the enemy collisions, and the player collisions, mostly with their own functions. Whenever anything is hit, a sound is made, confirming to the player that the collision happened.

main.c brings all of this together and updates and renders all entities. It creates the window, handles the win-lose logic, the score etc. However, only high-level elements of the program are seen in main.c.
