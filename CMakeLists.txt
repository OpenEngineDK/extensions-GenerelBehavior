
# Project source code list
ADD_LIBRARY(Extensions_GenerelBehavior
  Logic/Waypoints.cpp
)

# Project dependencies
TARGET_LINK_LIBRARIES(Extensions_GenerelBehavior
  Extensions_BehaviorTree
)
