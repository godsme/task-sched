//
// Created by Darwin Yuan on 2022/9/23.
//

#ifndef TASK_SCHED_E97581B33EE94D5B8C6D746FAB901B81
#define TASK_SCHED_E97581B33EE94D5B8C6D746FAB901B81

#include <task-sched/core/WorkSharingQueue.h>
#include <task-sched/core/Resumable.h>
#include <task-sched/core/Worker.h>
#include <vector>
#include <memory>

namespace task_sched {
    struct Coordinator {
        Coordinator() = default;

        auto StartUp(std::size_t numOfWorkers) noexcept -> void;
        auto Schedule(Resumable*) noexcept -> bool;
        auto Shutdown() noexcept -> void;

    private:
        std::unique_ptr<WorkSharingQueue> m_pendingTasks{};
        std::vector<Worker> m_workers;
        bool working{};
    };
}

#endif //TASK_SCHED_E97581B33EE94D5B8C6D746FAB901B81
