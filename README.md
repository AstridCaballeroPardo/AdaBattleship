# 1. Challenge Outline  
### a. Summary and review of the problem, overall proposed solution. 
The [proposed solution](Documentation/designOverAll.draw) is to implement the State pattern to wrap up the game. 

This pattern allows to have different behaviours depending on the state it is at a given moment. for example, during the 'setup state' the 'enter()' method is all about setting the fleets of both players but when we transition to 'play state' the 'enter()' method is all about shooting. Similarly for the 'exit()' method, if the game is in the 'setup state' then to exit it only needs to reset the Fleets; if the game is in the 'play state' then 'exit()' needs to reset the fleet and also reset the tiles that were bombed.

The state pattern provides a good separation of concerns in terms of what we want to do at certain state of the game. It also, helps to loop through the game efforlestly, for example when a player decides to quit the game, the user is taken to the 'intro state' where she/he can either start a new game or exit the game completly.

In order to access the game's grids (one grid/board per player) the design also implements the Singleton pattern. The grids are instanciated inside the 'state machine', so making the 'state machine' a Singleton allows global access to the grids. 

### b. UML style diagram illustrating initial overall solution (linked to 1a) 
### c. Initial working plan, overall approach, development strategy and approach to quality (linked to 1a,  1b). 
### d. Analysis and decomposition of the overall problem into key ‘epic’ style tasks (linked to 1b, 1c). e. Initial object-oriented design ideas and planned phased breakdown into smaller tasks (linked to 1d). 


# 2. Development 
### a. Adoption and use of ‘good’ standards (linked to 1a, 1b, 1c). 
### b. Phase 1 development: tasks, code review and changes (linked to 1d,1e). 
### c. ..repeated for each development phase. 
### d. Phase n development: tasks, code review and changes (linked to 1d,1e). 
### e. Ensuring quality through testing and resolving bugs (linked to 1a, 1b, 2a, 2b..2c). 
### f. Reflection on key design challenges, innovations and how they were solved (with examples). 


# 3. Evaluation 
### a. Analysis with embedded examples of key code refactoring, reuse, smells. 
### b. Implementation and effective use of ‘advanced’ programming principles (with examples). 
### c. Features showcase and embedded innovations (with examples) - opportunity to ‘highlight’ best bits. d. Improved algorithms – research, design, implementation, and tested confirmation (with examples). e. Reflective review, opportunities to improve and continued professional development.
