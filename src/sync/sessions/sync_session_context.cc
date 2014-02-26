// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sync/sessions/sync_session_context.h"

#include "sync/sessions/debug_info_getter.h"
#include "sync/util/extensions_activity.h"

namespace syncer {
namespace sessions {

const unsigned int kMaxMessagesToRecord = 10;
const unsigned int kMaxMessageSizeToRecord = 5 * 1024;

SyncSessionContext::SyncSessionContext(
    ServerConnectionManager* connection_manager,
    syncable::Directory* directory,
    const std::vector<ModelSafeWorker*>& workers,
    ExtensionsActivity* extensions_activity,
    const std::vector<SyncEngineEventListener*>& listeners,
    DebugInfoGetter* debug_info_getter,
    TrafficRecorder* traffic_recorder,
    bool keystore_encryption_enabled,
    bool client_enabled_pre_commit_update_avoidance,
    const std::string& invalidator_client_id)
    : connection_manager_(connection_manager),
      directory_(directory),
      extensions_activity_(extensions_activity),
      notifications_enabled_(false),
      max_commit_batch_size_(kDefaultMaxCommitBatchSize),
      debug_info_getter_(debug_info_getter),
      traffic_recorder_(traffic_recorder),
      keystore_encryption_enabled_(keystore_encryption_enabled),
      invalidator_client_id_(invalidator_client_id),
      server_enabled_pre_commit_update_avoidance_(false),
      client_enabled_pre_commit_update_avoidance_(
          client_enabled_pre_commit_update_avoidance) {
  for (size_t i = 0u; i < workers.size(); ++i)
    workers_.push_back(workers[i]);

  std::vector<SyncEngineEventListener*>::const_iterator it;
  for (it = listeners.begin(); it != listeners.end(); ++it)
    listeners_.AddObserver(*it);
}

SyncSessionContext::~SyncSessionContext() {
}

}  // namespace sessions
}  // namespace syncer
