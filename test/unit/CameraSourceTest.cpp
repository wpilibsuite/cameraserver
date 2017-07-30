/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2015-2017. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "gtest/gtest.h"

#include "cameraserver.h"

namespace cs {

class CameraSourceTest : public ::testing::Test {
 protected:
  CameraSourceTest() {
  }
};

TEST_F(CameraSourceTest, HTTPCamera) {
  auto source = HTTPCamera("axis", "http://localhost:8000");
}

}  // namespace cs
