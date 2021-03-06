/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */
/*
 * Copyright (C) 2020 Canonical, Ltd.
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
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Marco Trevisan <marco.trevisan@canonical.com>
 */

#ifndef ORIENTATION_MANAGER_UNIT_TESTS_H
#define ORIENTATION_MANAGER_UNIT_TESTS_H

#include "backends/meta-orientation-manager.h"

void init_orientation_manager_tests (void);

void wait_for_orientation (MetaOrientationManager *orientation_manager,
                           MetaOrientation         orientation,
                           unsigned int           *times_signalled_out);
void wait_for_possible_orientation_change (MetaOrientationManager *orientation_manager,
                                           unsigned int           *times_signalled_out);

const char * orientation_to_string (MetaOrientation orientation);

#endif /* ORIENTATION_MANAGER_UNIT_TESTS_H */
