//
// Created by Darwin Yuan on 2022/9/23.
//
#include <task-sched/core/Worker.h>
#include <task-sched/core/WorkSharingQueue.h>
#include <chrono>
#include <catch.hpp>

using namespace task_sched;

namespace {
    int ids[2] = {0, 0};
    std::size_t numOfTasks = 0;
    struct DummyTask : Resumable {
        DummyTask(int id) : id{id} {}
        auto Resume() noexcept -> TaskResult override {
            ids[id - 1] = id;
            return TaskResult::DONE;
        }

        auto operator new(std::size_t size) noexcept -> void* {
            numOfTasks++;
            return ::operator new(size);
        }

        auto operator delete(void* p) noexcept -> void {
            numOfTasks--;
            ::operator delete(p);
        }

        int id{};
    };
}

using namespace std::chrono_literals;

SCENARIO("Worker") {
    numOfTasks = 0;
    WorkSharingQueue queue;

    Worker worker1 = Worker(queue);
    Worker worker2 = Worker(queue);

    worker1.Launch();
    worker2.Launch();

    queue.Enqueue(new DummyTask{1});
    queue.Enqueue(new DummyTask{2});

    std::this_thread::sleep_for(100ms);

    REQUIRE(ids[0] + ids[1] == 3);
    REQUIRE(numOfTasks == 0);

    queue.Shutdown();

    worker1.WaitDone();
    worker2.WaitDone();
}