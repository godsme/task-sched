//
// Created by Darwin Yuan on 2022/9/23.
//
#include <task-sched/core/WorkSharingQueue.h>
#include <thread>
#include <catch.hpp>

using namespace task_sched;

namespace {
    struct DummyTask : Resumable {
        DummyTask(int id) : id{id} {}
        auto Resume() noexcept -> TaskResult override {
            return TaskResult::DONE;
        }
        int id{};
    };
}

SCENARIO("WorkSharingQueue enqueue") {
    WorkSharingQueue queue;
    int ids[2] = {0, 0};

    auto t1 = std::thread([&] {
        auto* task = queue.Dequeue();
        REQUIRE(task != nullptr);
        ids[0] = reinterpret_cast<DummyTask*>(task)->id;
        task->Release();
    });

    auto t2 = std::thread([&] {
        auto* task = queue.Dequeue();
        REQUIRE(task != nullptr);
        ids[1] = reinterpret_cast<DummyTask*>(task)->id;
        task->Release();
    });

    queue.Enqueue(new DummyTask{1});
    queue.Enqueue(new DummyTask{2});

    t1.join();
    t2.join();

    REQUIRE(ids[0] + ids[1] == 3);
}

SCENARIO("WorkSharingQueue shutdown") {
    WorkSharingQueue queue;

    auto t1 = std::thread([&] {
        auto* task = queue.Dequeue();
        REQUIRE(task == nullptr);
    });

    auto t2 = std::thread([&] {
        auto* task = queue.Dequeue();
        REQUIRE(task == nullptr);
    });

    queue.Shutdown();

    t1.join();
    t2.join();
}