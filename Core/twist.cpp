#include "UniversalRigNodes.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/type_ptr.hpp"

void copy_matrix(float *to, const glm::mat4 &from)
{
	memcpy(to, glm::value_ptr(from), sizeof(float) * (4 * 4));
}

void URN_calc_twist(float *out_offset_matrix, const float *in_target_local_matrix, float twist_blend)
{
	// Simple implementation of lookat-based twist
	const glm::mat4 target_mat = glm::make_mat4(in_target_local_matrix); // TODO PERF: Perhaps elide the copy assuming alignment is OK?

	const glm::vec3 forward = { 1.0f, 0.0f, 0.0f };
	const glm::vec3 up = target_mat[2];
	const glm::vec3 across = glm::cross(up, forward);
	const glm::vec3 up_ortho = glm::cross(forward, across);

	const glm::mat3 lookat_matrix = {
		forward,
		across,
		up_ortho,
	};

	const glm::vec3 lookat_rot_euler = glm::eulerAngles(glm::quat_cast(lookat_matrix)); // TODO PERF: Convert to euler without first converting to quaternion
	const float twist_rotation_angle = lookat_rot_euler.x * twist_blend;

	const glm::mat4 offset_matrix = glm::eulerAngleX(twist_rotation_angle);
	copy_matrix(out_offset_matrix, offset_matrix); // TODO PERF: Perhaps elide the copy assuming alignment is OK?
}
