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

#include "../../../../include/c/game_function/d2lang/d2lang_unicode_strncmp.h"

#include <pthread.h>
#include <stdint.h>

#include "../../../asm_x86_macro.h"
#include "../../backend/error_handling.h"
#include "../../backend/game_function/fastcall_function.h"
#include "../../backend/game_address_table.h"
#include "../../../../include/c/game_version.h"
#include "../../../wide_macro.h"

static pthread_once_t once_flag = PTHREAD_ONCE_INIT;
static const struct MAPI_GameAddress* game_address;

static void InitGameAddress(void) {
  game_address = GetGameAddress(
      "D2Lang.dll",
      "Unicode_strncmp"
  );
}

static int32_t D2_D2Lang_Unicode_strncmp_1_10(
    const struct D2_UnicodeChar_1_00* str1,
    const struct D2_UnicodeChar_1_00* str2,
    uint32_t count
);

int D2_D2Lang_Unicode_strncmp(
    const struct D2_UnicodeChar* str1,
    const struct D2_UnicodeChar* str2,
    size_t count
) {
  enum D2_GameVersion running_game_version = D2_GetRunningGameVersionId();

  const struct D2_UnicodeChar_1_00* actual_str1 =
      (const struct D2_UnicodeChar_1_00*) str1;
  const struct D2_UnicodeChar_1_00* actual_str2 =
      (const struct D2_UnicodeChar_1_00*) str2;

  if (running_game_version <= VERSION_1_09D) {
    return D2_D2Lang_Unicode_strncmp_1_00(
        actual_str1,
        actual_str2,
        count
    );
  } else /* if (running_game_version > VERSION_1_09D) */ {
    return D2_D2Lang_Unicode_strncmp_1_10(
        actual_str1,
        actual_str2,
        count
    );
  }
}

/**
 * This function did not exist in 1.00. It has been reconstructed to behave
 * exactly like in 1.10+.
 */
int32_t D2_D2Lang_Unicode_strncmp_1_00(
    const struct D2_UnicodeChar_1_00* str1,
    const struct D2_UnicodeChar_1_00* str2,
    uint32_t count
) {
  for (size_t i = 0; i < count; i += 1) {
    int diff = str1[i].ch - str2[i].ch;

    if (diff != 0) {
      return diff;
    }

    if (str1[i].ch == u'\0') {
      return 0;
    }
  }

  return 0;
}

int32_t D2_D2Lang_Unicode_strncmp_1_10(
    const struct D2_UnicodeChar_1_00* str1,
    const struct D2_UnicodeChar_1_00* str2,
    uint32_t count
) {
  int once_return = pthread_once(&once_flag, &InitGameAddress);

  if (once_return != 0) {
    ExitOnCallOnceFailure(__FILEW__, __LINE__);
  }

  return (int32_t) CallFastcallFunction(
      game_address->raw_address,
      3,
      str1,
      str2,
      count
  );
}
