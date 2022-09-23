//
// Created by Darwin Yuan on 2022/9/23.
//

#ifndef TASK_SCHED_4834098B5F564F3B85DE2CA9BBD5D808
#define TASK_SCHED_4834098B5F564F3B85DE2CA9BBD5D808

#include <functional>

namespace task_sched {
    template <typename ELEM>
    struct Queue {
        using Cleaner = std::function<auto (ELEM&) -> void>;

        Queue() = default;

        auto Enqueue(ELEM* elem) noexcept -> void;
        auto PushFront(ELEM* elem) noexcept -> void;
        auto Concat(Queue& another) noexcept -> void;
        auto Dequeue() noexcept -> ELEM*;
        auto TakeAll() noexcept -> ELEM*;

        auto Empty() const noexcept -> bool {
            return m_head == nullptr;
        }

        auto CleanUp() noexcept -> void;
        auto CleanUp(Cleaner) noexcept -> void;

        ~Queue() {
            CleanUp();
        }

    private:
        ELEM* m_head{};
        ELEM* m_tail{};
    };
}

#endif //TASK_SCHED_4834098B5F564F3B85DE2CA9BBD5D808
