#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	// Setting up the hardware for our robot
	// instantiating (making an instance of) motors for x-drive
	// pros::Motor m_botLeftMotor = pros::Motor(20);
	// pros::Motor m_topLeftMotor = pros::Motor(11);
	// pros::Motor m_botRightMotor = pros::Motor(10);
	// pros::Motor m_topRightMotor = pros::Motor(1);

	Drivetrain m_drive = Drivetrain(20, 11, 10, 1);


	// instantiating a Controller object
	pros::Controller m_controller = pros::Controller(pros::E_CONTROLLER_MASTER);
	const double kDeadband = 20.0;

	while (true) {	// forces the code to run forever
		/* negative sign required since pushing the left_y stick up gives a value of -127
		so, if I want the motor to run forward, I need to give it positive values
		hence, the extra negative sign (e.g,. -(-127))
		*/
		int y_dir = m_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int x_dir = m_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
		int rot = m_controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		// m_topLeftMotor.move_velocity(y_dir + x_dir + rot);
		// m_botLeftMotor.move_velocity(y_dir - x_dir + rot);
		// m_topRightMotor.move_velocity(-y_dir + x_dir + rot);
		// m_botRightMotor.move_velocity(-y_dir - x_dir + rot);

		y_dir = okapi::deadband(y_dir, -kDeadband, kDeadband);
		x_dir = okapi::deadband(x_dir, -kDeadband, kDeadband);
		rot = okapi::deadband(rot, -kDeadband, kDeadband);


		m_drive.XDrive(y_dir, x_dir, rot);

		pros::delay(20); // Run for 20 ms then update
	}
}

// int DeadbandValue(int val, int deadband) {
// 	if (abs(val) < deadband) {
// 		return 0;
// 	}
// 	return val;
// }