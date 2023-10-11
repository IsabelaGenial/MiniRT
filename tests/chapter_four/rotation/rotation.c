#include "tester.h"

// Scenario : Rotating a point half quarter around the x axis
#define scenario1 CYAN "\n" \
				"Given p ← point(0, 1, 0)\n" \
				"And half_quarter ← create_x_rotation_matrix(π / 4)\n"              \
				"Then half_quarter * p = point(0, 0.7071, 0.7071)\n"      \

const t_tuple p = {0, 1, 0, POINT};
const t_matrix half_quarter = create_x_rotation_matrix(M_PI / 4);
const t_matrix full_quarter = create_x_rotation_matrix(M_PI / 2);
t_tuple res;

Test(rotation, rotating_half_quarter_around_x_axis, .description = scenario1) {
	const t_tuple expected = {0, 0.7071, 0.7071};
	multiply_tuple_by_matrix(p, half_quarter, res);
	cr_expect_tuple_eq(res, expected);
}

// Scenario : Rotating a point a half and a full quarter around the x axis
#define scenario2 CYAN "\n" \
				"Given p ← point(0, 1, 0)\n" \
				"And full_quarter ← create_x_rotation_matrix(π / 2)\n"              \
				"And full_quarter * p = point(0, 0, 1)" RESET

Test(rotation, rotating_full_quarter_around_x_axis, .description = scenario2) {
	const t_tuple expected = {0, 0, 1};
	multiply_tuple_by_matrix(p, half_quarter, res);
	multiply_tuple_by_matrix(p, full_quarter, res);
	cr_expect_tuple_eq(res, expected);
}
