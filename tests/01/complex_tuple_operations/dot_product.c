#include "../../tester.h"

// fun fact: the dot product of two unit vectors is the cosine of the angle between them

#define scenario1                                                                       \
    CYAN "\nGiven a ← vector(1, 2, 3)\n"                                                \
         "And b ← vector(2, 3, 4)\n"                                                    \
         "And dot(a, b)\n" 											   					\
		 "Then dot(a, b) == 20\n"RESET
#define scenario2                                                                       \
    CYAN "\nGiven a <-vector(1, 0, 0)\n"                                                \
         "And b <- vector(1, 0, 0)\n"                                                   \
         "And dot(a, b) = 1\n" 											            \
		 "Then  == 1" RESET
#define scenario3                                                                        \
    CYAN "\nGiven a <-vector(-1, 0, 0)\n"                                                \
         "And b <- vector(1, 0, 0)\n"                                                    \
         "And dot(a, b, ) = -1\n"                                                        \
		 "Then  == -1" RESET
#define scenario4                                                                        \
    CYAN "\nGiven a <-vector(1, 0, 0, 5)\n"                                              \
         "And b <- vector(-1, 0, 0, 1)\n"                                                \
         "Then dot(a, b) returns an error" RESET

Test(dot_product, dot_product_of_two_vectors, .description = scenario1) {

    const t_tuple a = {1, 2, 3, VECTOR};
	const t_tuple b = {2, 3, 4, VECTOR};
	double res = dot(a, b);
    cr_expect_eq(doubles_eq(res, 20.0), TRUE, RED"dot(a, b) should be 20"RESET);
}

Test(dot_product, dot_product_of_identical_unit_vectors, .description = scenario2) {
    const t_tuple a = {1, 0, 0, VECTOR};
	const t_tuple b = {1, 0, 0, VECTOR};
	double res = dot(a, b);
    cr_expect_eq(doubles_eq(res , 1), TRUE, RED"dot(a, b) should be 1"RESET);
}

Test(dot_product, dot_product_of_opposite_unit_vectors, .description = scenario3) {
    const t_tuple a = {1, 0, 0, VECTOR};
	const t_tuple b = {-1, 0, 0, VECTOR};
	double res = dot(a, b);
    cr_expect_eq(doubles_eq(res, -1), TRUE, RED"dot(a, b) should be -1"RESET);
}
