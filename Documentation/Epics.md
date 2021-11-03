# Grid Epic
- Create grid of zeros.
- Render grid.
- Test grid.
- Test accesibility to the zeros and the ability to being changed to ones.
- Get user input to change zeros to ones. Use REGEX.
- Create Tile class.
- Update grid to use 'Tile' objects instead of zeros and ones.

# Tile Epic
- Define attributes.
- Define methods.
- Test creating Tile's instances.
- Test accesing Tile's instances.
- Test changing Tile information.

# Ship Epic
- Creat ship class that connect with 'Tile' class.
- update 'Tile' class.
- Test Ship instantiation.
- Test Tiles of a ship have same shipID.
- Update parsing of player's input to create any ship in vertical or horizontal orientation.

# Fleet Epic
- Add Fleet Id to connect grid with Fleet.
- Create Fleet class, define attributes and methods.
- Update grid class, add a Fleet object as attribute.
- Create method to populate a Fleet with ships.
- Test.

# Place ship manually Epic
- what type of ship?
- check if ship is already in Fleet.
- Get ship's length.
- Go to 'Tile' (parsed with REGEX) entered by player.
- Loop/move in the orientation entered by player
- Check if the state of the 'Tiles' are 'shipTile'
- If all 'Tiles' are available then update 'ship' and 'tiles'.

# Place ship automatically Epic
- Create a vector with the unplaced ships.
- Create a vector to store the grid's indexes.
- Get random number.
- Check if random number is in the vector.
- Get random orientation.
- loop through the unplaced ships.
- get length of ship to be placed.
- Check if there are available tile in given orientation.
- if not try the other orientation.
- if there is place then update 'Tiles', 'Ship' and 'Fleet'. Also, delete tiles' indexes from the index vector so they are not picked by the random number. 
- if not get a new random number and try again.

# State Pattern Epic
- Create class 'StateMachine'
- Create abstract Base class that holds the actions to be performed by each state.
- Make class 'StateMachine' a **Singleton**.
- Refactor code.

# auto-fire Epic
- Create a vector to store the grid's indexes.
- Get random number.
- Check if random number is in the vector.
- update tile.

# Intro State Epic
- create menu.
- transition to setup game or exit the game.

# Setup State Epic
- Display human player' grid.
- create menu to ask method to place ship.
- get input from human player to place a ship if manually, validate input and place.
- if method is auto-place, place all remaining ships.
- create method to reset.
- ask after placing a ship or auto-place if user wants to reset.
- if user is happy with Fleet setup, then move to next player.
- If second player is computer then display grid and autoplace Fleet.
- If second player is human then take the same steps thatn with first player.
- finally ask if players want to play or quit?

# Play State Epic
- get Grid's.
- display opponents grid. 
- ask player to select a method to shoot.
- ask player to shoot at opponent's grid.
- check if target is available and update accordingly.
- keep track of shooted 'Tile', 'Ship' and the size of the 'Fleet'
- When one of the Fleets reaches size zero then transition to either 'victory' or 'gameover' state.

# Victory State Epic
- identify winner
- congratulate
- ask what to do next, another game or exit?
- here player can exit completely the game.

# Game Over State Epic
- Tell human the bad news.
- Reassure the human.
- ask what to do next, another game or exit?
- here player can exit completely the game.




