#include "URN.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/type_ptr.hpp"

void copy_matrix(double *to, const glm::dmat4 &from)
{
	static_assert(sizeof(from[0][0]) == sizeof(double), "Need dmat to actually use doubles");
	memcpy(to, glm::value_ptr(from), sizeof(double) * (4 * 4));
}

void URN_calc_twist(double *out_offset_matrix, const double *in_target_local_matrix, double twist_blend)
{
	// Simple implementation of lookat-based twist
	const glm::dmat4 target_mat = glm::make_mat4(in_target_local_matrix); // TODO PERF: Perhaps elide the copy assuming alignment is OK?

	const glm::dvec3 forward = { 1.0, 0.0, 0.0 };
	const glm::dvec3 up = target_mat[2];
	const glm::dvec3 across = glm::cross(up, forward);
	const glm::dvec3 up_ortho = glm::cross(forward, across);

	const glm::dmat3 lookat_matrix = {
		forward,
		across,
		up_ortho,
	};

	const glm::dvec3 lookat_rot_euler = glm::eulerAngles(glm::quat_cast(lookat_matrix)); // TODO PERF: Convert to euler without first converting to quaternion
	const double twist_rotation_angle = lookat_rot_euler.x * twist_blend;

	const glm::dmat4 offset_matrix = glm::eulerAngleX(twist_rotation_angle);
	copy_matrix(out_offset_matrix, offset_matrix); // TODO PERF: Perhaps elide the copy assuming alignment is OK?
}
