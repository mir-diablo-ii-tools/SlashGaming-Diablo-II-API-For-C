/**
 * SlashGaming Diablo II Modding API for C
 * Copyright (C) 2018-2020  Mir Drualga
 *
 * This file is part of SlashGaming Diablo II Modding API for C.
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

#include "../../../include/c/game_constant/d2_draw_effect.h"

#include "../../../include/c/game_version.h"

#include "../backend/encoding.h"
#include "../backend/error_handling.h"
#include "../../wide_macro.h"

static enum D2_DrawEffect_1_00 ToGameValue_1_00(
    enum D2_DrawEffect api_value
) {
  switch (api_value) {
    case DRAW_EFFECT_ONE_FOURTH_OPAQUE: {
      return DRAW_EFFECT_1_00_ONE_FOURTH_OPAQUE;
    }

    case DRAW_EFFECT_HALF_OPAQUE: {
      return DRAW_EFFECT_1_00_HALF_OPAQUE;
    }

    case DRAW_EFFECT_THREE_FOURTHS_OPAQUE: {
      return DRAW_EFFECT_1_00_THREE_FOURTHS_OPAQUE;
    }

    case DRAW_EFFECT_UNKNOWN_03: {
      return DRAW_EFFECT_1_00_UNKNOWN_03;
    }

    case DRAW_EFFECT_UNKNOWN_04: {
      return DRAW_EFFECT_1_00_UNKNOWN_04;
    }

    case DRAW_EFFECT_NONE: {
      return DRAW_EFFECT_1_00_NONE;
    }

    case DRAW_EFFECT_UNKNOWN_06: {
      return DRAW_EFFECT_1_00_UNKNOWN_06;
    }

    case DRAW_EFFECT_UNKNOWN_07: {
      return DRAW_EFFECT_1_00_UNKNOWN_07;
    }

    default: {
      ExitOnConstantMappingMissing(
          api_value,
          __FILEW__,
          __LINE__
      );

      return 0;
    }
  }
}

static enum D2_DrawEffect ToApiValue_1_00(
    enum D2_DrawEffect_1_00 game_value
) {
  switch (game_value) {
    case DRAW_EFFECT_1_00_ONE_FOURTH_OPAQUE: {
      return DRAW_EFFECT_ONE_FOURTH_OPAQUE;
    }

    case DRAW_EFFECT_1_00_HALF_OPAQUE: {
      return DRAW_EFFECT_HALF_OPAQUE;
    }

    case DRAW_EFFECT_1_00_THREE_FOURTHS_OPAQUE: {
      return DRAW_EFFECT_THREE_FOURTHS_OPAQUE;
    }

    case DRAW_EFFECT_1_00_UNKNOWN_03: {
      return DRAW_EFFECT_UNKNOWN_03;
    }

    case DRAW_EFFECT_1_00_UNKNOWN_04: {
      return DRAW_EFFECT_UNKNOWN_04;
    }

    case DRAW_EFFECT_1_00_NONE: {
      return DRAW_EFFECT_NONE;
    }

    case DRAW_EFFECT_1_00_UNKNOWN_06: {
      return DRAW_EFFECT_UNKNOWN_06;
    }

    case DRAW_EFFECT_1_00_UNKNOWN_07: {
      return DRAW_EFFECT_UNKNOWN_07;
    }

    default: {
      ExitOnConstantMappingMissing(
          game_value,
          __FILEW__,
          __LINE__
      );

      return 0;
    }
  }
}

int D2_DrawEffect_ToGameValue(enum D2_DrawEffect api_value) {
  return ToGameValue_1_00(api_value);
}

enum D2_DrawEffect D2_DrawEffect_ToApiValue(int game_value) {
  return ToApiValue_1_00(game_value);
}
