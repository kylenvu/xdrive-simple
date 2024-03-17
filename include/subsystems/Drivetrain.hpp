#pragma once
#ifndef _DRIVETRAIN_HPP_
#define _DRIVETRAIN_HPP_

#include "main.h"

class Drivetrain {
 public:
  Drivetrain(int8_t bLeft, int8_t tLeft, int8_t bRight, int8_t tRight) :
    m_botLeftMotor{bLeft},
    m_topLeftMotor{tLeft},
    m_botRightMotor{bRight},
    m_topRightMotor{tRight} {
    // Pros and C++ work in a way that is not happy when we do it like this
    // m_botLeftMotor = pros::Motor(bLeft);
    // m_topLeftMotor = pros::Motor(tLeft);
    // m_botRightMotor = pros::Motor(bRight);
    // m_topRightMotor = pros::Motor(tRight);
  }

  void XDrive(int y_dir, int x_dir, int rot) {
    m_topLeftMotor.move_velocity(y_dir + x_dir + rot);
		m_botLeftMotor.move_velocity(y_dir - x_dir + rot);
		m_topRightMotor.move_velocity(-y_dir + x_dir + rot);
		m_botRightMotor.move_velocity(-y_dir - x_dir + rot);
  }


 private:
  pros::Motor m_botLeftMotor;
	pros::Motor m_topLeftMotor;
	pros::Motor m_botRightMotor;
	pros::Motor m_topRightMotor;
};

#endif