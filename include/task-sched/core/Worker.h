//
// Created by Darwin Yuan on 2022/9/23.
//

#ifndef TASK_SCHED_92216D58D2554268A4F210E85EB0EB9F
#define TASK_SCHED_92216D58D2554268A4F210E85EB0EB9F

#include <thread>

namespace task_sched {
    struct WorkSharingQueue;
    struct Resumable;

    struct Worker {
        Worker(WorkSharingQueue& tasks) : m_tasks{tasks} {}

        auto Launch() noexcept -> void;
        auto WaitDone() noexcept -> void;

    private:
        auto Run() noexcept -> void;
        auto ScheduleTask(Resumable*) noexcept -> void;

    private:
        std::thread m_tid;
        WorkSharingQueue& m_tasks;
    };
}

#endif //TASK_SCHED_92216D58D2554268A4F210E85EB0EB9F
