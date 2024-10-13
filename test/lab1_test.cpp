#include <gtest/gtest.h>
#include <plant.h>


TEST(test_01, valid_seq) {
  // arrange 
  int growth = 100;
  int shrink = 10;
  int check = 910;

  // act
  int result = plant(growth, shrink, check);

  // assert
  assert(result == 10);
}

TEST(test_02, invalid_seq) {
  int growth = -20;
  int shrink = -10;
  int check = -5;

  int result = plant(growth, shrink, check);

  assert(result == 0);
}

TEST(test_03, shrink_faster) {
  int growth = 1;
  int shrink = 2;
  int check = 5;

  int result = plant(growth, shrink, check);

  assert(result == 0);
}

TEST(test_04, no_growth) {
  int growth = 1;
  int shrink = 1;
  int check = 5;

  int result = plant(growth, shrink, check);

  assert(result == 0);
}