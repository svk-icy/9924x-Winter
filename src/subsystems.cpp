#include "subsystems.hpp"

#include "main.h"

void lever_lift() {
  lift.button_toggle(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN));
}

void lever_pid_move(double Target) {
  // sets the pid target
  leverPID.target_set(Target);

  // pidLoop
  while (true) {
    double position = levermotor.get_position();  // calculates the position of the motor before moving
    double output = leverPID.compute(position);   // calculates the voltage going to be given to the motor using the position value

    if (output > 127) {
      output = 127;
    } else if (output < -127) {
      output = -127;
    }

    levermotor.move(output);  // moves motor with output volts
    if (fabs(Target - position) < 0.25) {
      levermotor.move(0);
      break;
    }  // checks how close the motor is to the target, if its error is less than 0.25, stop motor and break while loop

    pros::delay(10);
  }
}

// macro for autos
void lever_set(double Target) {
  hood.set(true);
  lever_pid_move(Target);
  pros::delay(50);
  lever_pid_move(0);
  hood.set(false);
}

void lever_op_control() {
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
    hood.set(true);
    levermotor.move(-127);
    if (levermotor.get_position() >= 98 && fabs(levermotor.get_actual_velocity()) < 10) {
      levermotor.move(0);
    }
  } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
    hood.set(true);
    levermotor.move(-89);
    if (levermotor.get_position() >= 98 && fabs(levermotor.get_actual_velocity()) < 10) {
      levermotor.move(0);
    }
  } else {
    hood.set(false);
    levermotor.move(60);

    if (levermotor.get_position() <= 0 && fabs(levermotor.get_actual_velocity()) < 10) {
      levermotor.move(0);
    }
  }
}

/*void leverMG_op_control() {
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
    hood.set(true);
    levermotor.move(89);
    if (levermotor.get_position() >= 98 && levermotor.get_actual_velocity() < 10) {
      levermotor.move(0);
    }
  } else {
    hood.set(false);
    levermotor.move(-89);

    if (levermotor.get_position() <= 0 && fabs(levermotor.get_actual_velocity()) < 10) {
      levermotor.move(0);
    }
  }
}*/

void intake_op_control() {
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
    intake_s1.move(-127);
  } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
    intake_s1.move(127);
  }
}
