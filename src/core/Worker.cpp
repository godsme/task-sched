//
// Created by Darwin Yuan on 2022/9/23.
//
#include <task-sched/core/Worker.h>
#include <task-sched/core/WorkSharingQueue.h>

namespace task_sched {
    auto Worker::ScheduleTask(Resumable* task) noexcept -> void {
        while(1) {
            if(task->Resume() == TaskResult::DONE) {
                task->Release();
                return;
            } else if(!m_tasks.IsEmpty()) {
                m_tasks.Reschedule(task);
                return;
            }
        }
    }
    auto Worker::Run() noexcept -> void {
        while(1) {
            auto* task = m_tasks.Dequeue();
            if(task == nullptr) break;
            ScheduleTask(task);
        }
    }

    auto Worker::Launch() noexcept -> void {
        m_tid = std::thread([this] {
            Run();
        });
    }

    auto Worker::WaitDone() noexcept -> void {
        m_tid.join();
    }
}