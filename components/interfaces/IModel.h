#ifndef CPP3_BRICKGAME_V2_0_1_IMODEL_H
#define CPP3_BRICKGAME_V2_0_1_IMODEL_H

#ifdef __cplusplus

extern "C" {
#endif

#include "../GameInfo.h"

#ifdef __cplusplus
}
#endif

namespace s21 {

/**
 * Interface representing the model component of the game.
 *
 * <p>The IModel interface defines the contract for the model component in the
 * game's architecture. It provides virtual methods for handling user input,
 * updating the game's state, setting and getting keys, and retrieving the
 * current game state. Any class implementing this interface must provide
 * concrete implementations for these methods.
 */
class IModel {
 public:
  /**
   * Virtual destructor for the IModel interface.
   *
   * <p>This ensures that the destructor of the derived class is called when an
   * object is deleted through a pointer to IModel.
   */
  virtual ~IModel() = default;

  /**
   * Handles user input actions.
   *
   * <p>This method processes user actions and updates the game state
   * accordingly.
   *
   * @param action the user action to be processed
   * @param hold a boolean indicating whether the action is held down or not
   */
  virtual void userInput(UserAction_t action, bool hold) = 0;

  /**
   * Updates and returns the current state of the game.
   *
   * <p>This method retrieves the latest game information, such as score, level,
   * and other relevant data.
   *
   * @return the current game information encapsulated in a GameInfo_t object
   */
  virtual GameInfo_t updateCurrentState() = 0;

  /**
   * Sets a new key value for user input.
   *
   * <p>This method updates the current key used for user input processing.
   *
   * @param key the new key value to be set
   */
  virtual void setKey(int key) = 0;

  /**
   * Retrieves the last key value used for user input.
   *
   * <p>This method returns the value of the last key pressed by the user.
   *
   * @return the last key value
   */
  virtual int getLastKey() = 0;

  /**
   * Retrieves the current game state.
   *
   * <p>This method returns the current state of the game, such as playing,
   * paused, or game over.
   *
   * @return the current game state
   */
  virtual GameState_t getGameState() = 0;
};

}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_IMODEL_H
