# C-Random-Class

Flexible base rng "class" in C to allow plugging in multiple generator implementations with a common simple interface.

Comes with a basic default implementation using xorshifts 64.

Currently uses 2 homebrew libraries
-export.h : can be removed, just allows toggling dllexport of functions
-oop.h : used for getSuper macro, basically just a modified version of container_of
