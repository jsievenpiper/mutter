/*
 * Copyright (C) 2019 Red Hat
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 */

#include "config.h"

#include "wayland/meta-wayland-window-configuration.h"
#include "wayland/meta-window-wayland.h"

static uint32_t global_serial_counter = 0;

MetaWaylandWindowConfiguration *
meta_wayland_window_configuration_new (MetaWindow          *window,
                                       int                  x,
                                       int                  y,
                                       int                  width,
                                       int                  height,
                                       int                  scale,
                                       MetaMoveResizeFlags  flags,
                                       MetaGravity          gravity)
{
  MetaWindowWayland *wl_window;
  MetaWaylandWindowConfiguration *configuration;

  wl_window = META_WINDOW_WAYLAND (window);

  configuration = g_new0 (MetaWaylandWindowConfiguration, 1);
  *configuration = (MetaWaylandWindowConfiguration) {
    .serial = ++global_serial_counter,

    .scale = scale,
    .gravity = gravity,
    .flags = flags,
  };

  if (flags & META_MOVE_RESIZE_MOVE_ACTION ||
      window->rect.x != x ||
      window->rect.y != y)
    {
      configuration->has_position = TRUE;
      configuration->x = x;
      configuration->y = y;
    }

  configuration->has_size = (width != 0 && height != 0);
  configuration->is_resize =
    meta_window_wayland_is_resize (wl_window, width, height);
  configuration->width = width;
  configuration->height = height;

  return configuration;
}

MetaWaylandWindowConfiguration *
meta_wayland_window_configuration_new_relative (int rel_x,
                                                int rel_y,
                                                int width,
                                                int height,
                                                int scale)
{
  MetaWaylandWindowConfiguration *configuration;

  configuration = g_new0 (MetaWaylandWindowConfiguration, 1);
  *configuration = (MetaWaylandWindowConfiguration) {
    .serial = ++global_serial_counter,

    .has_relative_position = TRUE,
    .rel_x = rel_x,
    .rel_y = rel_y,

    .has_size = TRUE,
    .is_resize = TRUE,
    .width = width,
    .height = height,

    .scale = scale,
  };

  return configuration;
}

MetaWaylandWindowConfiguration *
meta_wayland_window_configuration_new_empty (void)
{
  MetaWaylandWindowConfiguration *configuration;

  configuration = g_new0 (MetaWaylandWindowConfiguration, 1);
  *configuration = (MetaWaylandWindowConfiguration) {
    .serial = ++global_serial_counter,
    .scale = 1,
  };

  return configuration;
}

void
meta_wayland_window_configuration_free (MetaWaylandWindowConfiguration *configuration)
{
  g_free (configuration);
}
