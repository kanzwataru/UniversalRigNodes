# UniversalRigNodes

Proof-of-concept showing how rig calculations can be split off into a library for use inside of plugins for both Unreal Engine and Maya, with the intent to ensure that procedural rig effects (such as twist bones) have the same results between software, reducing artist bug reports.

The purpose is to execute procedural rig calculations at runtime, rather than bake it into the animation data.
This allows for it to always have the final animation data as input. This way game-side procedural rigging like IK or upper-body blend spaces can be placed before the final procedural rig calculation.
As a bonus, this also reduces the size of the animation data.

Currently the plugin supports only a twist node and is mostly a proof-of-concept.
Main points:
* Written as a C++ library with a C API (for allowing use inside of Unity engine as well)
* The math library used is glm
  (may experiment with Eigen in row-major mode, in order to better match UE and Maya which both use row-major matrices)
* The source for the core library is in the same place and is shared between UE and Maya
  (for a real project, this folder structure may need to be adapted, since UE discourages having code outside the project tree)
