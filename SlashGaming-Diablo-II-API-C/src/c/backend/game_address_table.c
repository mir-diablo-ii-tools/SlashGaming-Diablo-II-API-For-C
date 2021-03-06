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

#include "game_address_table.h"

#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#include "error_handling.h"
#include "../../../include/c/game_version.h"
#include "game_address_table_impl.h"
#include "../../wide_macro.h"

/**
 * Table of game address entries containing game addresses.
 */
static struct MAPI_GameAddressTable* game_address_table;

/**
 * Initializes the game address table.
 */
static void InitGameAddressTable(void) {
  game_address_table = LoadGameAddressTable();
}

/**
 * Returns the compare results of game address table entries by
 * lexicographical compare of the library path, then a
 * lexicographical compare of the address name.
 */
static int CompareGameAddressTableEntryByLibraryPathThenAddressName(
    const struct MAPI_GameAddressTableEntry* entry1,
    const struct MAPI_GameAddressTableEntry* entry2
) {
  int first_compare_result = strcmp(
      entry1->library_path,
      entry2->library_path
  );

  if (first_compare_result != 0) {
    return first_compare_result;
  }

  return strcmp(entry1->address_name, entry2->address_name);
}

const struct MAPI_GameAddress* GetGameAddress(
    const char* library_path,
    const char* address_name
) {
  static pthread_once_t load_table_once = PTHREAD_ONCE_INIT;
  if (pthread_once(&load_table_once, &InitGameAddressTable) != 0) {
    ExitOnGeneralFailure(
        L"pthread_once function failed.",
        L"Initialization Failure",
        __FILEW__,
        __LINE__
    );
  }

  struct MAPI_GameAddressTableEntry key = {
    .library_path = library_path,
    .address_name = address_name
  };

  struct MAPI_GameAddressTableEntry* search_result =
      (struct MAPI_GameAddressTableEntry*) bsearch(
          (const void*) &key,
          (void*) game_address_table->entries,
          game_address_table->num_elements,
          sizeof(*(game_address_table->entries)[0]),
          (int (*)(const void*, const void*))
              &CompareGameAddressTableEntryByLibraryPathThenAddressName
      );

  return &search_result->game_address;
}
