/**
 * SlashGaming Diablo II Modding API for C++98
 * Copyright (C) 2018-2021  Mir Drualga
 *
 * This file is part of SlashGaming Diablo II Modding API for C++98.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Additional permissions under GNU Affero General Public License version 3
 *  section 7
 *
 *  If you modify this Program, or any covered work, by linking or combining
 *  it with Diablo II (or a modified version of that game and its
 *  libraries), containing parts covered by the terms of Blizzard End User
 *  License Agreement, the licensors of this Program grant you additional
 *  permission to convey the resulting work. This additional permission is
 *  also extended to any combination of expansions, mods, and remasters of
 *  the game.
 *
 *  If you modify this Program, or any covered work, by linking or combining
 *  it with any Graphics Device Interface (GDI), DirectDraw, Direct3D,
 *  Glide, OpenGL, or Rave wrapper (or modified versions of those
 *  libraries), containing parts not covered by a compatible license, the
 *  licensors of this Program grant you additional permission to convey the
 *  resulting work.
 *
 *  If you modify this Program, or any covered work, by linking or combining
 *  it with any library (or a modified version of that library) that links
 *  to Diablo II (or a modified version of that game and its libraries),
 *  containing parts not covered by a compatible license, the licensors of
 *  this Program grant you additional permission to convey the resulting
 *  work.
 */

#include "../../../../include/cxx98/game_function/d2common/d2common_get_global_equipment_slot_layout.hpp"

#include <sgd2mapi.h>

namespace d2 {
namespace d2common {

void GetGlobalEquipmentSlotLayout(
    unsigned int inventory_record_index,
    unsigned int inventory_arrange_mode,
    EquipmentLayout* out_equipment_slot_layout,
    unsigned int equipment_slot_index
) {
  ::D2_D2Common_GetGlobalEquipmentSlotLayout(
      inventory_record_index,
      inventory_arrange_mode,
      out_equipment_slot_layout,
      equipment_slot_index
  );
}

void GetGlobalEquipmentSlotLayout_1_00(
    uint32_t inventory_record_index,
    EquipmentLayout_1_00* out_equipment_slot_layout,
    uint32_t equipment_slot_index
) {
  ::D2_D2Common_GetGlobalEquipmentSlotLayout_1_00(
      inventory_record_index,
      out_equipment_slot_layout,
      equipment_slot_index
  );
}

void GetGlobalEquipmentSlotLayout_1_07(
    uint32_t inventory_record_index,
    uint32_t inventory_arrange_mode,
    EquipmentLayout_1_00* out_equipment_slot_layout,
    uint32_t equipment_slot_index
) {
  ::D2_D2Common_GetGlobalEquipmentSlotLayout_1_07(
      inventory_record_index,
      inventory_arrange_mode,
      out_equipment_slot_layout,
      equipment_slot_index
  );
}

} // namespace d2common
} // namespace d2