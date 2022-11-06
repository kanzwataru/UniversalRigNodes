/*
 * Copyright 2022 Denis Robert Patrut
 * This code is licensed under the MIT license, check the LICENSE.txt in the repo root.
*/
#include "MayaCommon.h"
#include <maya/MFnPlugin.h>

#include "URNTwistNode.h"

MStatus initializePlugin(MObject obj)
{
	MFnPlugin plugin(obj, "kanzwataru", "1.0", "Any");

	plugin.registerNode("URNTwist", URNTwistNode::typeId, URNTwistNode::creator, URNTwistNode::initialize);

	return MStatus::kSuccess;
}

MStatus uninitializePlugin(MObject obj)
{
	MFnPlugin plugin(obj);

	plugin.deregisterNode(URNTwistNode::typeId);

	return MStatus::kSuccess;
}
