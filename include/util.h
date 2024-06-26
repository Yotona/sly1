/**
 * @file util.h
 *
 * @brief Declarations for utility functions.
*/
#ifndef UTIL_H
#define UTIL_H

/**
 * @brief Limits for a float
*/
struct LM
{
	float gMin, gMax;
};

/**
 * @brief Checks if a float falls within the given limit.
 *
 * @param plm Pointer to the limit
 * @param g The float to check
*/
int FCheckLm(struct LM* plm, float g);

/**
 * @brief Stubbed function, does nothing.
*/
void Force(void);

#endif // UTIL_H
