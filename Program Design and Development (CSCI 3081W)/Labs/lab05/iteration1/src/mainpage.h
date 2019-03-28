/*! \mainpage CSCI3081 Robot Simulator Project
 *
 * \section intro_sec Introduction
 *
 * The GraphicsArenaViewer class asks for updates from Arena by having an Arena object (Arena has no knowledge of GraphicsArenaViewer), which holds the information of all entities. Some "entities" move and some don't, but they all inherit from the class Arena_Entity. Events interact with the entities, which in turn end up interacting with Arena. All events inherit from "EventBaseClass". Events include thing like keypresses, collisions, and commands. In this way, the state of Arena changes, and then this state is reflected in the visuals vs GraphicsArenaViewer.
 *
 * \section install_sec Installation
 *
 * \subsection libsimplegraphics Installing and Using libsimplegraphics
 *
 * etc...
 */
