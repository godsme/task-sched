cmake_minimum_required(VERSION 3.23)
project(task_sched)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

add_library(task_sched
        include/task-sched/util/Queue.h
        include/task-sched/util/Queue.tcc
        include/task-sched/util/ListElem.h
        include/task-sched/core/TaskResult.h
        include/task-sched/core/Resumable.h
        include/task-sched/core/WorkSharingQueue.h
        src/core/WorkSharingQueue.cpp include/task-sched/core/Worker.h src/core/Worker.cpp include/task-sched/core/Coordinator.h src/core/Coordinator.cpp)
