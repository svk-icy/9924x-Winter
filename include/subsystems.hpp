#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;

// Your motors, sensors, etc. should go here.  Below are examples

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');
inline ez::PID leverPID(0.25, 1, 1, 0, "levermotor");
inline pros::Motor levermotor(8);
inline pros::Motor intake_s1(18);
inline ez::Piston wing('F');
inline ez::Piston scraper('G');
inline ez::Piston hood('H');
inline ez::Piston lift('E');
inline pros::adi::DigitalIn bumper('A');

// functions
void lever_set(double Target);
void sepLevermacro();
void lever_lift();
void lever_pid_move(double Target);
