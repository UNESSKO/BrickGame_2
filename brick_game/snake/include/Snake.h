#ifndef CPP3_BRICKGAME_V2_0_1_SNAKE_H
#define CPP3_BRICKGAME_V2_0_1_SNAKE_H

#ifdef __cplusplus

#include <vector>

#include "../../../components/GameInfo.h"

extern "C" {
#endif

#include <sys/stat.h>

#ifdef __cplusplus
}
#endif

namespace s21 {
struct Point {
  int x;
  int y;
};

class Snake {
 public:
  /**
   * Constructs a Snake object with a specified length.
   *
   * <p>This constructor initializes the snake with a given length, sets its
   * initial direction to left, reserves space for up to 201 elements in the
   * snake vector, and positions the snake segments in a horizontal line
   * starting at coordinates (5, 10) with subsequent segments increasing in the
   * x-coordinate.
   *
   * @param length the initial length of the snake
   */
  explicit Snake(int length);

  ~Snake() = default;
  /**
   * Resets the snake to its initial state.
   *
   * <p>This method resets the snake to a default length of 4 segments,
   * positions the segments in a horizontal line starting at coordinates (5, 10)
   * with subsequent segments increasing in the x-coordinate, and sets the
   * direction of the snake to left.
   */
  void reset();
  /**
   * Sets the direction of the snake based on the user's action.
   *
   * <p>This method changes the direction of the snake if the new direction is
   * not directly opposite to the current direction. The allowed directions are:
   * Right, Left, Up, and Down. The direction will only be updated if it does
   * not cause the snake to directly reverse its current trajectory.
   *
   * @param direction the new direction to set for the snake, based on user
   * action
   */
  void setDirection(UserAction_t direction);
  /**
   * Moves the snake one step in the current direction.
   *
   * <p>This method updates the position of each segment of the snake to
   * simulate movement. Each segment (except the head) takes the position of the
   * previous segment, and the head moves one step in the current direction
   * (right, left, up, or down).
   */
  void move();
  /**
   * Adds a new segment to the snake.
   *
   * <p>This method appends a new segment to the end of the snake. The new
   * segment is initialized to the position of the second-to-last segment,
   * effectively extending the length of the snake by one while keeping the new
   * segment in place until the next move.
   */
  void addSegment();
  /**
   * Returns the current size of the snake.
   *
   * <p>This method provides the number of segments that currently make up the
   * snake.
   *
   * @return the number of segments in the snake
   */
  int size();
  /**
   * Provides access to the snake segment at the specified index.
   *
   * <p>This operator allows for direct access and modification of the snake
   * segment at the given index. It returns a reference to the Point object
   * representing the segment's position.
   *
   * @param index the index of the snake segment to access
   * @return a reference to the Point object at the specified index
   * @throws std::out_of_range if the index is out of bounds
   */
  Point &operator[](int index);

  /**
   * The Snake class represents a snake in the game with its segments and
   * movement direction.
   *
   * <p>This class manages the state and behavior of the snake, including its
   * segments and the direction in which it moves.
   */
 private:
  /**
   * A vector of Points representing the segments of the snake.
   *
   * <p>Each Point object in the vector represents the (x, y) coordinates of a
   * segment of the snake. The head of the snake is at index 0, and subsequent
   * segments follow in the order of the vector.
   */
  std::vector<Point> snake_;

  /**
   * The current direction of the snake's movement.
   *
   * <p>This variable stores the current direction in which the snake is moving.
   * It can be one of the values defined in the UserAction_t enumeration: Right,
   * Left, Up, or Down.
   */
  UserAction_t direction_;
};
}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_SNAKE_H
