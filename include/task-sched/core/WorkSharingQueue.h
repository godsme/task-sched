//
// Created by Darwin Yuan on 2022/9/23.
//

#ifndef TASK_SCHED_5576153CC2DC4B5DB067E91E373482E5
#define TASK_SCHED_5576153CC2DC4B5DB067E91E373482E5

#include <task-sched/util/Queue.h>
#include <task-sched/core/Resumable.h>
#include <condition_variable>
#include <mutex>

namespace task_sched {
    struct WorkSharingQueue {
        WorkSharingQueue() = default;

        auto Enqueue(Resumable*) noexcept -> void;
        auto Dequeue() noexcept -> Resumable*;
        auto Reschedule(Resumable* task) noexcept -> void;
        auto Shutdown() noexcept -> void;
        auto CleanUp() noexcept -> void;
        auto IsEmpty() const noexcept -> bool;

        ~WorkSharingQueue();

    private:
        task_sched::Queue<Resumable> m_tasks{};
        std::condition_variable m_cv{};
        mutable std::mutex m_lock{};
        bool m_shutdown{};
    };
}

#endif //TASK_SCHED_5576153CC2DC4B5DB067E91E373482E5
