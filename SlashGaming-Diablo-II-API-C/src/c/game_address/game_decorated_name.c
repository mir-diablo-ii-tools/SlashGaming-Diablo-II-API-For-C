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

#include "../../../include/c/game_address/game_decorated_name.h"

#include <windows.h>

#include <mdc/filesystem/filesystem.h>
#include <mdc/string/basic_string.h>
#include <mdc/std/wchar.h>
#include <mdc/wchar_t/wide_decoding.h>
#include "../../wide_macro.h"
#include "../backend/error_handling.h"
#include "../backend/game_library.h"

static const wchar_t* const kErrorMessageFormat =
    L"The data or function with the name %ls from %ls could not be "
    L"found.";

struct Mapi_GameAddress* Mapi_GameAddress_InitFromLibraryIdAndDecoratedName(
    struct Mapi_GameAddress* game_address,
    enum D2_DefaultLibrary library_id,
    const char* decorated_name
) {
  return Mapi_GameAddress_InitFromLibraryPathAndDecoratedName(
      game_address,
      Mapi_GetDefaultLibraryPathWithRedirect(library_id),
      decorated_name
  );
}

struct Mapi_GameAddress* Mapi_GameAddress_InitFromLibraryPathAndDecoratedName(
    struct Mapi_GameAddress* game_address,
    const wchar_t* library_path_cstr,
    const char* decorated_name
) {
  struct Mdc_Fs_Path library_path;
  struct Mdc_Fs_Path* init_library_path;

  struct Mdc_BasicString decorated_name_wide;
  struct Mdc_BasicString* init_decorated_name_wide;

  const struct Mapi_GameLibrary* game_library;
  FARPROC ordinal_address;

  init_library_path = Mdc_Fs_Path_InitFromCWStr(
      &library_path,
      library_path_cstr
  );

  if (init_library_path != &library_path) {
    ExitOnMdcFunctionFailure(
        L"Mdc_Fs_Path_InitFromCWStr",
        __FILEW__,
        __LINE__
    );

    goto return_bad;
  }

  game_library = GetGameLibrary(&library_path);
  ordinal_address = GetProcAddress(
      (HMODULE) Mapi_GameLibrary_GetBaseAddress(game_library),
      decorated_name
  );

  if (ordinal_address == NULL) {
    init_decorated_name_wide = Mdc_Wide_DecodeUtf8(
        &decorated_name_wide,
        decorated_name
    );

    ExitFormattedOnGeneralFailure(
        L"Error",
        __FILEW__,
        __LINE__,
        kErrorMessageFormat,
        Mdc_BasicString_Data(&decorated_name_wide),
        Mdc_Fs_Path_CStr(&library_path_cstr)
    );

    goto return_bad;
  }

  game_address->raw_address = (intptr_t) ordinal_address;

  Mdc_Fs_Path_Deinit(&library_path);

  return game_address;

return_bad:
  return NULL;
}
