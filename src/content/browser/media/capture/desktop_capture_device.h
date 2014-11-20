// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_MEDIA_CAPTURE_DESKTOP_CAPTURE_DEVICE_H_
#define CONTENT_BROWSER_MEDIA_CAPTURE_DESKTOP_CAPTURE_DEVICE_H_

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "content/common/content_export.h"
#include "content/public/browser/desktop_media_id.h"
#include "media/video/capture/video_capture_device.h"
#include "ui/gfx/native_widget_types.h"

namespace base {
class SequencedTaskRunner;
class Thread;
}  // namespace base

namespace webrtc {
class DesktopCapturer;
}  // namespace webrtc

namespace content {

// DesktopCaptureDevice implements VideoCaptureDevice for screens and windows.
// It's essentially an adapter between webrtc::DesktopCapturer and
// VideoCaptureDevice.
class CONTENT_EXPORT DesktopCaptureDevice : public media::VideoCaptureDevice {
 public:
  // Creates capturer for the specified |source| and then creates
  // DesktopCaptureDevice for it. May return NULL in case of a failure (e.g. if
  // requested window was destroyed).
  static scoped_ptr<media::VideoCaptureDevice> Create(
      const DesktopMediaID& source);

  virtual ~DesktopCaptureDevice();

  // VideoCaptureDevice interface.
  virtual void AllocateAndStart(const media::VideoCaptureParams& params,
                                scoped_ptr<Client> client) OVERRIDE;
  virtual void StopAndDeAllocate() OVERRIDE;

  // Set the platform-dependent window id for the notification window.
  void SetNotificationWindowId(gfx::NativeViewId window_id);

 private:
  friend class DesktopCaptureDeviceTest;
  class Core;

  // Either |task_runner| or |thread| should be non-NULL, but not both.
  DesktopCaptureDevice(scoped_refptr<base::SequencedTaskRunner> task_runner,
                       scoped_ptr<base::Thread> thread,
                       scoped_ptr<webrtc::DesktopCapturer> desktop_capturer,
                       DesktopMediaID::Type type);

  scoped_refptr<Core> core_;

  DISALLOW_COPY_AND_ASSIGN(DesktopCaptureDevice);
};

}  // namespace content

#endif  // CONTENT_BROWSER_MEDIA_CAPTURE_DESKTOP_CAPTURE_DEVICE_H_
