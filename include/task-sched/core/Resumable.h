//
// Created by Darwin Yuan on 2022/9/23.
//

#ifndef TASK_SCHED_20B50057D86644BCA662887037FA88D6
#define TASK_SCHED_20B50057D86644BCA662887037FA88D6

#include <task-sched/util/ListElem.h>
#include <task-sched/core/TaskResult.h>

namespace task_sched {
    struct Resumable : ListElem<Resumable> {
        virtual ~Resumable() = default;
        virtual auto Resume() noexcept -> TaskResult = 0;
        virtual auto AddRef() noexcept -> void {}
        virtual auto Release() noexcept -> void {
            delete this;
        }
    };
}

#endif //TASK_SCHED_20B50057D86644BCA662887037FA88D6
