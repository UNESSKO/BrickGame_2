#ifndef CPP3_BRICKGAME_V2_0_1_SNAKEMODEL_H
#define CPP3_BRICKGAME_V2_0_1_SNAKEMODEL_H

#ifdef __cplusplus

#include <fstream>
#include <iostream>

#include "../../../components/GameInfo.h"
#include "../../../components/interfaces/IModel.h"
#include "../include/Snake.h"

extern "C" {
#endif

#include <sys/stat.h>

#ifdef __cplusplus
}
#endif

namespace s21 {
/**
 * Enum class representing the dimensions of the game field.
 *
 * <p>This enum class defines the height and width of the game field used in the
 * Snake game. These constants are used to configure the size of the playing
 * area.
 */
enum class Field : int {
  height = 21, /**< The height of the game field. */
  width = 12   /**< The width of the game field. */
};
/**
 * The SnakeModel class represents the model component of the Snake game.
 *
 * <p>This class manages the game's state, including the snake's position, the
 * game field, the apple's position, and the current game information. It
 * implements various methods to handle game logic, such as movement, collision
 * detection, and state updates. The class inherits from the IModel interface,
 * indicating that it follows a specific contract for interacting with other
 * components of the game.
 */
class SnakeModel : public IModel {
 public:
  /**
   * Constructs a SnakeModel object and initializes the game state.
   *
   * <p>This constructor initializes the game state to Launch, allocates and
   * initializes the game field matrix, sets up the initial game information,
   * and positions the snake and apple at their starting locations. It also
   * initializes the key states and loads the high score.
   */
  SnakeModel();
  /**
   * Destructor for the SnakeModel class.
   *
   * <p>This destructor cleans up the dynamically allocated memory used for the
   * game field. It ensures that each row of the field matrix is deleted,
   * followed by the deletion of the field itself.
   */
  ~SnakeModel() override;
  /**
   * Processes user input and updates the game state accordingly.
   *
   * <p>This method handles various user actions and updates the game state
   * based on the current state of the game. It processes actions such as
   * starting the game, moving the snake, spawning apples, and checking for
   * collisions. The method also handles transitions between different game
   * states like Launch, Spawn, Moving, Eating, Win, and GameOver.
   *
   * @param action the action performed by the user (e.g., Start, Terminate,
   * movement commands)
   * @param hold a boolean indicating if a key is being held down
   */
  void userInput(UserAction_t action, bool hold) override;
  /**
   * Updates and returns the current state of the game.
   *
   * <p>This method provides the latest game information by returning the
   * current state stored in the gameInfo_ member variable. It can be used to
   * retrieve the current score, level, high score, and other game-related
   * information.
   *
   * @return the current state of the game encapsulated in a GameInfo_t object
   */
  GameInfo_t updateCurrentState() override;
  /**
   * Sets a new key value.
   *
   * <p>This method updates the key used for user input processing by setting it
   * to the provided new key value.
   *
   * @param new_key the new key value to be set
   */
  void setKey(int new_key) override;
  /**
   * Retrieves the last key value.
   *
   * <p>This method returns the value of the last key used for user input
   * processing.
   *
   * @return the last key value
   */
  int getLastKey() override;
  /**
   * Retrieves the current game state.
   *
   * <p>This method returns the current state of the game. If the game is over,
   * it returns GameState_t::GameOver; otherwise, it returns the current game
   * state stored in state_.
   *
   * @return the current game state, either GameState_t::GameOver or the value
   * of state_
   */
  GameState_t getGameState() override;

 private:
  /**
   * The current state of the game.
   *
   * <p>This variable holds the current state of the game, which could be
   * playing, paused, or game over, etc. It is used to manage the game's flow
   * and transitions between different states.
   */
  GameState_t state_;

  /**
   * The game field represented as a 2D array.
   *
   * <p>This variable is a pointer to a dynamically allocated 2D array that
   * represents the game field. Each cell in the array can hold information
   * about the presence of the snake, apples, or empty spaces.
   */
  int **field_;

  /**
   * The current game information.
   *
   * <p>This variable holds various pieces of information about the current
   * game, including the score, level, and high score. It is used to keep track
   * of the player's progress and achievements.
   */
  GameInfo_t gameInfo_;

  /**
   * Indicator of whether the game is over.
   *
   * <p>This boolean variable is used to determine if the game has ended. It
   * becomes true when certain conditions are met, such as the snake colliding
   * with a wall or itself.
   */
  bool gameOver_;

  /**
   * The snake object representing the player's snake.
   *
   * <p>This variable holds an instance of the Snake class, which contains
   * information about the snake's segments, position, and movement. It is used
   * to manage the snake's behavior and interactions within the game.
   */
  Snake snake_;

  /**
   * The position of the apple on the game field.
   *
   * <p>This variable holds the coordinates of the apple within the game field.
   * It is used to determine where the apple is located and if the snake has
   * eaten it.
   */
  Point apple_;

  /**
   * The key value used for the current user input.
   *
   * <p>This variable holds the value of the key that was most recently pressed
   * by the user. It is used to control the snake's movement and other game
   * actions.
   */
  int key_;

  /**
   * The last key value used for user input.
   *
   * <p>This variable holds the value of the key that was pressed before the
   * current key. It is used to manage the snake's previous direction and ensure
   * smooth input handling.
   */
  int last_key_;
  /**
   * Initializes and returns the game information structure.
   *
   * <p>This method sets up the initial game information, including the game
   * field, score, high score, level, speed, and pause state. It prepares the
   * game for a new session by initializing these values.
   *
   * @return a GameInfo_t structure initialized with default game settings
   */
  GameInfo_t gameInfoInit();
  /**
   * Processes the given user action and updates the game state accordingly.
   *
   * <p>This method processes user actions such as changing the snake's
   * direction, pausing the game, and terminating the game. It updates the
   * snake's direction, handles the pause state, and moves the snake. If the
   * snake moves without collisions, it updates the game field; otherwise, it
   * transitions the game state to Eating.
   *
   * @param action the action performed by the user (e.g., Left, Right, Up,
   * Down, Pause, Terminate)
   * @param hold a boolean indicating if a key is being held down
   */
  void actionProcessing(UserAction_t action, bool hold);
  /**
   * Loads the high score from a file.
   *
   * <p>This method attempts to open a file named "snake_high_score.txt" to read
   * the high score. If the file exists and is opened successfully, it reads the
   * high score into the game information. If the file does not exist, it
   * creates a new file with the initial high score value.
   */
  void loadHighScore();
  /**
   * Saves the high score to a file.
   *
   * <p>This method writes the current high score to a file named
   * "snake_high_score.txt". It opens the file in output mode, writes the high
   * score from gameInfo_, and then closes the file.
   *
   * @note This method is marked as const because it does not modify any member
   * variables of the class.
   */
  void saveHighScore() const;
  /**
   * Starts a new game session.
   *
   * <p>This method resets the game state to start a new game session. It sets
   * the game over flag to false, loads the high score, and resets the score and
   * level to their initial values.
   */
  void startGame();
  /**
   * Resets the game to its initial state.
   *
   * <p>This method resets the game state to prepare for a new game session. It
   * sets the game over flag to true, loads the high score, and resets the game
   * information such as score, level, and speed. It also clears the game field,
   * resets the snake's position, and repositions the apple.
   */
  void resetGame();
  /**
   * Removes the snake from the game field.
   *
   * <p>This method iterates through the segments of the snake and clears their
   * current positions on the game field by setting the corresponding cells to
   * blank spaces (' ').
   */
  void deleteSnake();
  /**
   * Places the snake onto the game field.
   *
   * <p>This method iterates through the segments of the snake and updates the
   * game field to reflect the snake's current position. It uses different
   * characters to represent the snake's body and head.
   */
  void putSnake();
  /**
   * Removes the apple from the game field.
   *
   * <p>This method updates the game field to clear the current position of the
   * apple. It sets the cell at the apple's coordinates to a blank space (' ').
   */
  void deleteApple();
  /**
   * Places the apple onto the game field.
   *
   * <p>This method updates the game field to reflect the current position of
   * the apple. It sets the cell at the apple's coordinates to a specific
   * character to represent the apple.
   */
  void putApple();
  /**
   * Spawns the apple at a random free position on the game field.
   *
   * <p>This method identifies all free (empty) positions on the game field and
   * randomly selects one to place the apple. It ensures that the apple is
   * placed in a location that is not currently occupied by the snake or any
   * other obstacles.
   */
  void spawnApple();
  /**
   * Handles the event when the snake eats an apple.
   *
   * <p>This method updates the game state to reflect the snake eating an apple.
   * It performs the following actions: removes the apple from the game field,
   * adds a new segment to the snake, increments the score, and updates the high
   * score if necessary. It also increases the game level and adjusts the game
   * speed after every 5 points scored.
   */
  void eat();
  /**
   * Clears the game field.
   *
   * <p>This method resets the game field by filling it with blank spaces (' ')
   * except for the borders. It iterates through the field matrix and sets the
   * inner cells to ' ' while preserving any border elements.
   */
  void clearField();
  /**
   * Checks if the snake's head has collided with an apple, a wall, or its own
   * body.
   *
   * <p>This method aggregates the results of checking for collisions with an
   * apple, a wall, and the snake's own body. If any of these collisions are
   * detected, the method returns true.
   *
   * @return true if the snake's head has collided with an apple, a wall, or its
   * own body; false otherwise
   */
  bool isCollision();
  /**
   * Checks if the snake's head has collided with the apple.
   *
   * <p>This method compares the coordinates of the snake's head with the
   * coordinates of the apple. If the coordinates match, it indicates that the
   * snake has collided with the apple.
   *
   * @return true if the snake's head has collided with the apple, false
   * otherwise
   */
  bool isAppleCollision();
  /**
   * Checks if the snake's head has collided with the wall.
   *
   * <p>This method checks the coordinates of the snake's head to determine if
   * it has collided with the boundary of the game field. If the head's x or y
   * coordinates are outside the permissible range, a collision with the wall is
   * detected.
   *
   * @return true if the snake's head has collided with the wall, false
   * otherwise
   */
  bool isWallCollision();
  /**
   * Checks if the snake's head has collided with its own body.
   *
   * <p>This method iterates through the segments of the snake's body starting
   * from the second segment. It compares the coordinates of the snake's head
   * with each segment's coordinates. If a match is found, it indicates that the
   * snake has collided with itself.
   *
   * @return true if the snake's head has collided with its own body, false
   * otherwise
   */
  bool isInnerCollision();
  /**
   * Sets the game speed based on the current level.
   *
   * <p>This method calculates the game speed (time delay) based on the provided
   * level. The speed decreases as the level increases, making the game more
   * challenging.
   *
   * @param level the current level of the game
   * @return the calculated time delay for the game speed
   */
  static int setTime(int time);
  /**
   * Creates a new matrix (2D array) with the specified dimensions.
   *
   * <p>This method dynamically allocates memory for a 2D array with the given
   * height and width. Each element of the matrix is an integer, and the method
   * returns a pointer to the newly created matrix.
   *
   * @param height the number of rows in the matrix
   * @param width the number of columns in the matrix
   * @return a pointer to the newly created 2D array
   */
  static int **newMatrix(int height, int width);
};
}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_SNAKEMODEL_H
