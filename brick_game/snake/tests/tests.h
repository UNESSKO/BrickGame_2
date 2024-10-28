#ifndef CPP3_BRICKGAME_V2_0_1_TESTS_H
#define CPP3_BRICKGAME_V2_0_1_TESTS_H

#ifdef __cplusplus

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <iostream>

#include "../include/Snake.h"
#include "../include/SnakeModel.h"

extern "C" {
#endif

#ifdef __cplusplus
}
#endif

void printField(int **field);
void moveHead(s21::Point &head, UserAction_t action);
void fieldByPass(s21::SnakeModel *model, int count);

class SnakeTests : public ::testing::Test {
 protected:
  s21::SnakeModel *model;

  void SetUp() override { model = new s21::SnakeModel(); }
  void TearDown() override { delete model; }
};

#endif  // CPP3_BRICKGAME_V2_0_1_TESTS_H
