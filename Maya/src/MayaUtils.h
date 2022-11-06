/*
 *  Maya Utilities
 * Utilities useful for writing Maya plugin code.
 * 
 * ---------------------------------------------------------------------------------------
 * Copyright 2022 Denis Robert Patrut
 * This code is licensed under the MIT license, check the LICENSE.txt in the repo root.
*/
#pragma once
#include <maya/MStatus.h>

// Error-checking
#define VERIFY(x_) CHECK_MSTATUS_AND_RETURN_IT(x_)
#define VERIFY_OR_RET(x_, r_) CHECK_MSTATUS_AND_RETURN(x_, r_)
