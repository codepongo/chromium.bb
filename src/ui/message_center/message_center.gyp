# Copyright (c) 2012 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

{
  'variables': {
    'chromium_code': 1,
  },
  'targets': [
    {
      'target_name': 'message_center',
      'type': '<(component)',
      'dependencies': [
        '../../base/base.gyp:base',
        '../../base/base.gyp:base_i18n',
        '../../base/third_party/dynamic_annotations/dynamic_annotations.gyp:dynamic_annotations',
        '../../skia/skia.gyp:skia',
        '../../url/url.gyp:url_lib',
        '../base/strings/ui_strings.gyp:ui_strings',
        '../events/events.gyp:events',
        '../gfx/gfx.gyp:gfx',
        '../ui.gyp:ui',
        '../ui.gyp:ui_resources',
      ],
      'defines': [
        'MESSAGE_CENTER_IMPLEMENTATION',
      ],
      'sources': [
        'cocoa/notification_controller.h',
        'cocoa/notification_controller.mm',
        'cocoa/popup_collection.h',
        'cocoa/popup_collection.mm',
        'cocoa/popup_controller.h',
        'cocoa/popup_controller.mm',
        'cocoa/settings_controller.h',
        'cocoa/settings_controller.mm',
        'cocoa/settings_entry_view.h',
        'cocoa/settings_entry_view.mm',
        'cocoa/status_item_view.h',
        'cocoa/status_item_view.mm',
        'cocoa/tray_controller.h',
        'cocoa/tray_controller.mm',
        'cocoa/tray_view_controller.h',
        'cocoa/tray_view_controller.mm',
        'dummy_message_center.cc',
        'message_center.cc',
        'message_center.h',
        'message_center_export.h',
        'notification_delegate.cc',
        'notification_delegate.h',
        'message_center_impl.cc',
        'message_center_impl.h',
        'message_center_observer.h',
        'message_center_style.cc',
        'message_center_style.h',
        'message_center_switches.cc',
        'message_center_switches.h',
        'message_center_tray.cc',
        'message_center_tray.h',
        'message_center_tray_delegate.h',
        'message_center_types.h',
        'message_center_util.cc',
        'message_center_util.h',
        'notification.cc',
        'notification.h',
        'notification_blocker.cc',
        'notification_blocker.h',
        'notification_list.cc',
        'notification_list.h',
        'notification_types.cc',
        'notification_types.h',
        'notifier_settings.cc',
        'notifier_settings.h',
        'views/bounded_label.cc',
        'views/bounded_label.h',
        'views/message_bubble_base.cc',
        'views/message_bubble_base.h',
        'views/message_center_bubble.cc',
        'views/message_center_bubble.h',
        'views/message_center_button_bar.cc',
        'views/message_center_button_bar.h',
        'views/message_center_focus_border.h',
        'views/message_center_focus_border.cc',
        'views/message_center_view.cc',
        'views/message_center_view.h',
        'views/message_popup_collection.cc',
        'views/message_popup_collection.h',
        'views/message_view.cc',
        'views/message_view.h',
        'views/notifier_settings_view.cc',
        'views/notifier_settings_view.h',
        'views/notification_view.cc',
        'views/notification_view.h',
        'views/toast_contents_view.cc',
        'views/toast_contents_view.h',
      ],
      # TODO(jschuh): crbug.com/167187 fix size_t to int truncations.
      'msvs_disabled_warnings': [ 4267, ],
      'conditions': [
        ['toolkit_views==1', {
          'dependencies': [
            '../views/views.gyp:views',
          ],
        }, {
          'sources/': [
            ['exclude', 'views/'],
          ],
        }],
        ['use_ash==0', {
          'sources!': [
            'views/message_bubble_base.cc',
            'views/message_bubble_base.h',
            'views/message_center_bubble.cc',
            'views/message_center_bubble.h',
            'views/message_popup_bubble.cc',
            'views/message_popup_bubble.h',
          ],
        }],
        ['OS=="mac"', {
          'dependencies': [
            '../ui.gyp:ui_cocoa_third_party_toolkits',
          ],
          'include_dirs': [
            '../../third_party/GTM',
          ],
        }],
        ['toolkit_views==1', {
          'dependencies': [
            '../compositor/compositor.gyp:compositor',
          ],
        }],
        ['notifications==0', {  # Android and iOS.
          'sources/': [
            # Exclude everything except dummy impl.
            ['exclude', '\\.(cc|mm)$'],
            ['include', '^dummy_message_center\\.cc$'],
            ['include', '^message_center_switches\\.cc$'],
          ],
        }, {  # notifications==1
          'sources!': [ 'dummy_message_center.cc' ],
        }],
      ],
    },  # target_name: message_center
    {
      'target_name': 'message_center_test_support',
      'type': 'static_library',
      'dependencies': [
        '../../base/base.gyp:base',
        '../../skia/skia.gyp:skia',
        '../events/events.gyp:events',
        '../gfx/gfx.gyp:gfx',
        '../ui.gyp:ui',
        'message_center',
      ],
      'sources': [
        'fake_message_center.h',
        'fake_message_center.cc',
        'fake_notifier_settings_provider.h',
        'fake_notifier_settings_provider.cc',
      ],
    },  # target_name: message_center_test_support
  ],
}