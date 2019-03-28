Most known bugs are related to proper collision detection.

1. Since the heading angle of the colliding entity is not being used in calculations, collision calculation is inherently flawed (not angle of incidence). This is due to the way arguments are set up in Arena::CheckForEntityCollision (I could not get casting to work).
2. Collisions off obstacles (not walls) look reasonable about 30% of the time for the robot. It seems to depend on the angle of approach (and definitely on the speed; higher speeds work better), but I can't seem to determine a rule for when it will work.
3. Since Robot slows down after collisions, it tends to get stuck in objects when colliding at low speeds (reasonable collisions can sometimes be seen at higher speeds).
4. HomeBase can not be set to change angle often (randomly), because it overrides the angle set by the collision. While this happens rarely (HomeBase does not change angle often currently), it still occurs on occasion.
6. While wall collisions tend to work well, coming in at angles close to parallel can cause mobile entities to get stuck in the wall. 
7. Sometimes when stuck the Robot can escape with repeated speed up commands, but other times it gets permanently trapped.

Other bugs include:

7. The heading angle doesn't initialize to the same value as restart sets it to.
8. The angle of the text on the robot does not correspond
to the actual heading angle. I'd prefer if it didn't rotate at all but that hasn't been tried
either as of right now.

