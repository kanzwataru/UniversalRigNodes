/*
 *  Common Maya include files
 * Include all the ubiquitously-used headers at once
 * to avoid having a giant include block at the beginning of the file.
 * 
 * ---------------------------------------------------------------------------------------
 * Copyright 2022 Denis Robert Patrut
 * This code is licensed under the MIT license, check the LICENSE.txt in the repo root.
*/
#pragma once
#include "MayaUtils.h"

#include <maya/MPxNode.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnCompoundAttribute.h>

#include <maya/MFloatVector.h>
#include <maya/MFloatMatrix.h>
#include <maya/MQuaternion.h>
#include <maya/MMatrix.h>
#include <maya/MVector.h>
#include <maya/MEulerRotation.h>
