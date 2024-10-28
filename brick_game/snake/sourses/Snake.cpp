#include "../include/Snake.h"

namespace s21 {

Snake::Snake(int length) : snake_(length), direction_(UserAction_t::Left) {
  snake_.reserve(201);

  for (int i = 0; i < length; ++i) {
    snake_[i].y = 10;
    snake_[i].x = 5 + i;
  }
}

void Snake::reset() {
  int length = 4;
  snake_.resize(length);

  for (int i = 0; i < length; ++i) {
    snake_[i].y = 10;
    snake_[i].x = 5 + i;
  }

  direction_ = UserAction_t::Left;
}

void Snake::setDirection(UserAction_t direction) {
  switch (direction) {
    case UserAction_t::Right:
      if (direction_ != UserAction_t::Left) direction_ = direction;
      break;
    case UserAction_t::Left:
      if (direction_ != UserAction_t::Right) direction_ = direction;
      break;
    case UserAction_t::Up:
      if (direction_ != UserAction_t::Down) direction_ = direction;
      break;
    case UserAction_t::Down:
      if (direction_ != UserAction_t::Up) direction_ = direction;
      break;
  }
}

Point &Snake::operator[](int index) { return snake_[index]; }

int Snake::size() { return snake_.size(); }

void Snake::move() {
  for (int i = snake_.size() - 1; i > 0; --i) snake_[i] = snake_[i - 1];

  switch (direction_) {
    case UserAction_t::Right:
      snake_[0].x += 1;
      break;
    case UserAction_t::Left:
      snake_[0].x -= 1;
      break;
    case UserAction_t::Up:
      snake_[0].y -= 1;
      break;
    case UserAction_t::Down:
      snake_[0].y += 1;
      break;
  }
}

void Snake::addSegment() { snake_.push_back(snake_[snake_.size() - 2]); }
}  // namespace s21