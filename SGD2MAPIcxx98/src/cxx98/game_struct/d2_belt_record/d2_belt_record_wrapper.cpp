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

#include "../../../../include/cxx98/game_struct/d2_belt_record/d2_belt_record_wrapper.hpp"

namespace d2 {

BeltRecord_Wrapper::BeltRecord_Wrapper(
    BeltRecord* belt_record
) {
  this->belt_record_.v1_00 =
      reinterpret_cast<BeltRecord_1_00*>(
          belt_record
      );
}

BeltRecord_Wrapper::BeltRecord_Wrapper(
    BeltRecord_1_00* belt_record
) {
  this->belt_record_.v1_00 = belt_record;
}

BeltRecord_View BeltRecord_Wrapper::operator[](
    size_t index
) const {
  return ::D2_BeltRecord_AccessConst(this->Get(), index);
}

BeltRecord_Wrapper BeltRecord_Wrapper::operator[](
    size_t index
) {
  return ::D2_BeltRecord_Access(this->Get(), index);
}

BeltRecord_Wrapper::operator BeltRecord_View() const {
    return BeltRecord_View(this->Get());
}

BeltRecord* BeltRecord_Wrapper::Get() {
  const BeltRecord_Wrapper* const_this = this;

  return const_cast<BeltRecord*>(const_this->Get());
}

const BeltRecord* BeltRecord_Wrapper::Get() const {
  return reinterpret_cast<const BeltRecord*>(
      this->belt_record_.v1_00
  );
}

void BeltRecord_Wrapper::AssignMembers(BeltRecord_View src) {
  ::D2_BeltRecord_AssignMembers(this->Get(), src.Get());
}

unsigned char BeltRecord_Wrapper::GetNumSlots() const {
  BeltRecord_View view(*this);

  return view.GetNumSlots();
}

void BeltRecord_Wrapper::SetNumSlots(unsigned char num_slots) {
  this->belt_record_.v1_00->num_slots = num_slots;
}

PositionalRectangle_View BeltRecord_Wrapper::GetSlotPositions() const {
  BeltRecord_View view(*this);

  return view.GetSlotPositions();
}

PositionalRectangle_Wrapper BeltRecord_Wrapper::GetSlotPositions() {
  return PositionalRectangle_Wrapper(
      this->belt_record_.v1_00->slot_positions
  );
}

} // namespace d2
