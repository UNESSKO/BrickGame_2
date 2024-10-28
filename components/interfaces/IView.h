//
// Created by KWAZAR_ on 07.09.2024.
//

#ifndef CPP3_BRICKGAME_V2_0_1_IVIEW_H
#define CPP3_BRICKGAME_V2_0_1_IVIEW_H

namespace s21 {
/**
 * Interface representing the view component of the game.
 *
 * <p>The IView interface defines the contract for the view component in the
 * game's architecture. It provides virtual methods for starting the event loop
 * and ensuring proper cleanup through a virtual destructor. Any class
 * implementing this interface must provide concrete implementations for these
 * methods.
 */
class IView {
 public:
  /**
   * Starts the main event loop of the view.
   *
   * <p>This method is responsible for handling user input, rendering the game
   * state, and maintaining the main loop of the view component. The specific
   * implementation will depend on the view framework being used.
   *
   * @return an integer value indicating the result of the event loop execution,
   * typically used to indicate success or an error code.
   */
  virtual int startEventLoop() = 0;

  /**
   * Virtual destructor for the IView interface.
   *
   * <p>This ensures that the destructor of the derived class is called when an
   * object is deleted through a pointer to IView.
   */
  virtual ~IView() = default;
};
}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_IVIEW_H
