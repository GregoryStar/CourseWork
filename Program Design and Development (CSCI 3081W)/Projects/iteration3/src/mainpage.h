#ifndef PROJECT_ITERATION3_SRC_MAINPAGE_H_
#define PROJECT_ITERATION3_SRC_MAINPAGE_H_
/**
 * @file mainpage.h
 *
 * @copyright 2017 Gregory Star, All rights reserved.
 */

/*! \mainpage CSCI3081 Robot Simulator Project
 *
 * \section intro_sec Introduction
 *
 * GraphicsArenaView is responsible for actually drawing the Arena and everything in it. It asks for updates from
 * Arena, and Arena returns information required to draw entities correctly. Since Arena contains all of the entities,
 * it asks all of them to update themselves and then reports the results. Arena keeps track of winning and losing
 * conditions; now, you win if all Robots are frozen and you lose if either you run out of battery or all Robots become
 * SuperBots.
 *
 * All entities inherit from ArenaEntity and then are subdivided into whether they’re mobile or not. As of Iteration2,
 * “Robot” has now become Player, and a new Robot class was created to represent autonomous entities. SuperBots are
 * actually just Robots with the isSuperBot flag activated.
 *
 * All Sensors inherit from Sensor. A generalized sensor can only be activated and reset, as well as being able to Accept
 * all sensor-based events (but it can’t react to them). SensorTouch, SensorDistress, SensorEntityType, and SensorProximity
 * inherit from Sensor. Each one actually implements one of the different Accept methods in Sensor.
 *
 * All Events inherit from EventBaseClass. Old Events include EventKeyPress, EventCommand, EventRecharge, and EventCollision.
 * However, there are now new Events that are specially made to interact with sensors, including EventDistress,
 * EventProximity, and EventTypeEmit.
 *
 * There is now a struct named robot_params to make the initialization of Robot easier.
 *
 * There is now an enumeration called EntityType which contains a list of all the entities types in Arena. This interacts with
 *  SensorEntityType to get the type of an entity in range of the Sensor.
 *
 * Note: Many changes were made to the code since the start of Iteration2; it is impossible to mention all of them. To my
 * knowledge, all structural changes are mentioned here. Also, since there were many changes in Iteration2, the code is practically
 * unrecognizable from how it started. For this reason, it is difficult to even decide what to include.
 * 
 * As of Iteration3, win and loss conditions have been changed: if you freeze all Robots you win, if you run out of battery or
 * every Robot becomes a SuperBot, you lose. If somehow you win and lose at the same time, it's counted as a loss.
 *
 * SensorProximity has been changed to actually detect proximity, and Robots now react accordingly (although it's kind of buggy).
 *
 * Note: Most changes in Iteration3 were strictly bug fixes; to my knowledge, the structure of the program has not changed since
 * Iteration2.
 *
 * \section install_sec Installation
 *
 * \subsection libsimplegraphics Installing and Using libsimplegraphics
 *
 * etc...
 */
#endif  // PROJECT_ITERATION3_SRC_MAINPAGE_H_
