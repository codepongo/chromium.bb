// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_SHARED_IMPL_MEDIA_STREAM_BUFFER_MANAGER_H_
#define PPAPI_SHARED_IMPL_MEDIA_STREAM_BUFFER_MANAGER_H_

#include <deque>
#include <vector>

#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/shared_memory.h"
#include "ppapi/shared_impl/ppapi_shared_export.h"

namespace ppapi {

union MediaStreamBuffer;

// This class is used by both read side and write side of a MediaStreamTrack to
// maintain a queue of buffers for reading or writing.
//
// An example:
//  1. The writer calls the writer's |buffer_manager_.Dequeue()| to get a free
//     buffer.
//  2. The writer fills data into the buffer.
//  3. The writer sends the buffer index to the reader via an IPC message.
//  4. The reader receives the buffer index and calls the reader's
//     |buffer_buffer.Enqueue()| to put the buffer into the read's queue.
//  5. The reader calls reader's |buffer_buffer_.Dequeue()| to get a received
//     buffer.
//  6. When the buffer from the step 5 is consumed, the reader sends the buffer
//     index back to writer via an IPC message.
//  7. The writer receives the buffer index and puts it back to the writer's
//     free buffer queue by calling the writer's |buffer_manager_.Enqueue()|.
//  8. Go back to step 1.
class PPAPI_SHARED_EXPORT MediaStreamBufferManager {
 public:
  class PPAPI_SHARED_EXPORT Delegate {
   public:
    virtual ~Delegate();
    // It is called when a new buffer is enqueued.
    virtual void OnNewBufferEnqueued();
  };

  // MediaStreamBufferManager doesn't own |delegate|, the caller should keep
  // it alive during the MediaStreamBufferManager's lifecycle.
  explicit MediaStreamBufferManager(Delegate* delegate);

  ~MediaStreamBufferManager();

  int32_t number_of_buffers() const { return number_of_buffers_; }

  int32_t buffer_size() const { return buffer_size_; }

  // Initializes shared memory for buffers transmission.
  bool SetBuffers(int32_t number_of_buffers,
                 int32_t buffer_size,
                 scoped_ptr<base::SharedMemory> shm,
                 bool enqueue_all_buffers);

  // Dequeues a buffer from |buffer_queue_|.
  int32_t DequeueBuffer();

  // Puts a buffer into |buffer_queue_|.
  void EnqueueBuffer(int32_t index);

  // Gets the buffer address for the given buffer index.
  MediaStreamBuffer* GetBufferPointer(int32_t index);

 private:
  Delegate* delegate_;

  // A queue of buffer indices.
  std::deque<int32_t> buffer_queue_;

  // A vector of buffer pointers. It is used for index to pointer converting.
  std::vector<MediaStreamBuffer*> buffers_;

  // The buffer size in bytes.
  int32_t buffer_size_;

  // The number of buffers in the shared memory.
  int32_t number_of_buffers_;

  // A memory block shared between renderer process and plugin process.
  scoped_ptr<base::SharedMemory> shm_;

  DISALLOW_COPY_AND_ASSIGN(MediaStreamBufferManager);
};

}  // namespace ppapi

#endif  // PPAPI_SHAERD_IMPL_MEDIA_STREAM_BUFFER_MANAGER_H_