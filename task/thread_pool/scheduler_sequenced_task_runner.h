// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_TASK_THREAD_POOL_SCHEDULER_SEQUENCED_TASK_RUNNER_H_
#define BASE_TASK_THREAD_POOL_SCHEDULER_SEQUENCED_TASK_RUNNER_H_

#include "base/base_export.h"
#include "base/callback_forward.h"
#include "base/location.h"
#include "base/task/task_traits.h"
#include "base/task/thread_pool/scheduler_task_runner_delegate.h"
#include "base/task/thread_pool/sequence.h"
#include "base/time/time.h"
#include "base/updateable_sequenced_task_runner.h"

namespace base {
namespace internal {

// A task runner that runs tasks in sequence.
class BASE_EXPORT SchedulerSequencedTaskRunner
    : public UpdateableSequencedTaskRunner {
 public:
  // Constructs a SchedulerSequencedTaskRunner which can be used to post tasks.
  SchedulerSequencedTaskRunner(
      const TaskTraits& traits,
      SchedulerTaskRunnerDelegate* scheduler_task_runner_delegate);

  // UpdateableSequencedTaskRunner:
  bool PostDelayedTask(const Location& from_here,
                       OnceClosure closure,
                       TimeDelta delay) override;

  bool PostNonNestableDelayedTask(const Location& from_here,
                                  OnceClosure closure,
                                  TimeDelta delay) override;

  bool RunsTasksInCurrentSequence() const override;

  void UpdatePriority(TaskPriority priority) override;

 private:
  ~SchedulerSequencedTaskRunner() override;

  SchedulerTaskRunnerDelegate* const scheduler_task_runner_delegate_;

  // Sequence for all Tasks posted through this TaskRunner.
  const scoped_refptr<Sequence> sequence_;

  DISALLOW_COPY_AND_ASSIGN(SchedulerSequencedTaskRunner);
};

}  // namespace internal
}  // namespace base

#endif  // BASE_TASK_THREAD_POOL_SCHEDULER_SEQUENCED_TASK_RUNNER_H_
