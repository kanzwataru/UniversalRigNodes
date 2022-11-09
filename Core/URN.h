/*
 *  Universal Rig Nodes Library
 * Non-software-specific core library of rig-related calculations,
 * provided as a C API for ease of integration in different languages.
 *
 * TODO: Document matrix layout
 * TODO: Document handedness
 * 
 * ---------------------------------------------------------------------------------------
 * Copyright 2022 Denis Robert Patrut
 * This code is licensed under the MIT license, check the LICENSE.txt in the repo root.
*/
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void URN_calc_twist(
	double		 *out_offset_matrix,
	const double *in_target_local_matrix,
	double		  twist_blend
);

#ifdef __cplusplus
} // extern "C"
#endif
