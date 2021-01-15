/**
 * SlashGaming Diablo II Modding API for C
 * Copyright (C) 2018-2021  Mir Drualga
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

#include "file_signature.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mdc/error/exit_on_error.h>
#include <mdc/std/stdint.h>
#include <mdc/wchar_t/filew.h>
#include "../../../../include/c/game_executable.h"

/**
 * File signature struct
 */

struct FileSignatureLocation {
  const wchar_t* path;
  ptrdiff_t offset;
};

enum {
  kSignatureCount = 4
};

static int File_SignatureLocation_LoadSignature(
    const struct FileSignatureLocation* location,
    uint8_t* signature
) {
  FILE* file;

  int fseek_result;
  size_t fread_count;

  file = _wfopen(location->path, L"rb");

  fseek_result = fseek(file, location->offset, SEEK_SET);
  if (fseek_result != 0) {
    Mdc_Error_ExitOnGeneralError(
        L"Error",
        L"%s failed.",
        __FILEW__,
        __LINE__,
        L"fseek"
    );

    goto close_file;
  }

  fread_count = fread(
      signature,
      sizeof(signature[0]),
      kSignatureCount,
      file
  );

  if (fread_count < kSignatureCount) {
    Mdc_Error_ExitOnGeneralError(
        L"Error",
        L"%s failed.",
        __FILEW__,
        __LINE__,
        L"fread"
    );

    goto close_file;
  }

  fclose(file);

  return 1;

close_file:
  fclose(file);

  return 0;
}

struct FileSignatureTableEntry {
  uint8_t signature[kSignatureCount];
  enum D2_GameVersion game_version;
};

static int FileSignatureTableEntry_CompareKey(
    const struct FileSignatureTableEntry* entry1,
    const struct FileSignatureTableEntry* entry2
) {
  return memcmp(
      entry1->signature,
      entry2->signature,
      sizeof(entry1->signature)
  );
}

static int FileSignatureTableEntry_CompareKeyAsVoid(
    const void* entry1,
    const void* entry2
) {
  return FileSignatureTableEntry_CompareKey(entry1, entry2);
}

static const struct FileSignatureTableEntry
kFileSignatureSortedTable[] = {
    { { 0x00, 0x50, 0x0A, 0x00 }, D2_GameVersion_kClassic1_14D },
    { { 0x00, 0x60, 0x0A, 0x00 }, D2_GameVersion_kLod1_14D },
    { { 0x25, 0x47, 0x52, 0x39 }, D2_GameVersion_k1_01 },
    { { 0x32, 0xA6, 0xDC, 0x3A }, D2_GameVersion_k1_07Beta },
    { { 0x34, 0x81, 0xD4, 0x56 }, D2_GameVersion_kLod1_14A },
    { { 0x38, 0x81, 0xD4, 0x56 }, D2_GameVersion_kClassic1_14A },
    { { 0x43, 0x0C, 0xD6, 0x3A }, D2_GameVersion_k1_06 },
    { { 0x4D, 0xDF, 0x2C, 0x57 }, D2_GameVersion_kLod1_14C },
    { { 0x52, 0xDF, 0x2C, 0x57 }, D2_GameVersion_kClassic1_14C },
    { { 0x79, 0xBD, 0x20, 0x39 }, D2_GameVersion_kBeta1_02 },
    { { 0xA8, 0x78, 0xFC, 0x56 }, D2_GameVersion_kLod1_14B },
    { { 0xAE, 0x78, 0xFC, 0x56 }, D2_GameVersion_kClassic1_14B },
    { { 0xB5, 0x92, 0xF5, 0x3A }, D2_GameVersion_k1_07 },
    { { 0xB7, 0x70, 0xD0, 0x38 }, D2_GameVersion_kBeta1_02StressTest },
    { { 0xBC, 0xC7, 0x2E, 0x39 }, D2_GameVersion_k1_00 },
    { { 0xC1, 0x7B, 0xE0, 0x3A }, D2_GameVersion_k1_06B },
};

enum {
  kFileSignatureSortedTableCount = sizeof(kFileSignatureSortedTable)
      / sizeof(kFileSignatureSortedTable[0])
};

static int HasFileSignatureCheck(enum D2_GameVersion game_version) {
  switch (game_version) {
    case D2_GameVersion_kBeta1_02:
    case D2_GameVersion_kBeta1_02StressTest:
    case D2_GameVersion_k1_00:
    case D2_GameVersion_k1_01:
    case D2_GameVersion_k1_06:
    case D2_GameVersion_k1_06B:
    case D2_GameVersion_k1_07Beta:
    case D2_GameVersion_k1_07:
    case D2_GameVersion_kClassic1_14A:
    case D2_GameVersion_kLod1_14A:
    case D2_GameVersion_kClassic1_14B:
    case D2_GameVersion_kLod1_14B:
    case D2_GameVersion_kClassic1_14C:
    case D2_GameVersion_kLod1_14C:
    case D2_GameVersion_kClassic1_14D:
    case D2_GameVersion_kLod1_14D: {
      return 1;
    }

    default: {
      return 0;
    }
  }
}

static struct FileSignatureLocation GetFileSignatureLocation(
    enum D2_GameVersion game_version
) {
  struct FileSignatureLocation file_signature_location = { 0 };

  switch (game_version) {
    case D2_GameVersion_kBeta1_02:
    case D2_GameVersion_kBeta1_02StressTest:
    case D2_GameVersion_k1_00:
    case D2_GameVersion_k1_01:
    case D2_GameVersion_k1_06:
    case D2_GameVersion_k1_06B:
    case D2_GameVersion_k1_07Beta:
    case D2_GameVersion_k1_07: {
      file_signature_location.path = L"storm.dll";
      file_signature_location.offset = 0xF0;

      break;
    }

    case D2_GameVersion_kClassic1_14A:
    case D2_GameVersion_kLod1_14A: {
      file_signature_location.path = Mapi_GameExecutable_GetPath();
      file_signature_location.offset = 0x120;

      break;
    }

    case D2_GameVersion_kClassic1_14B:
    case D2_GameVersion_kLod1_14B:
    case D2_GameVersion_kClassic1_14C:
    case D2_GameVersion_kLod1_14C: {
      file_signature_location.path = Mapi_GameExecutable_GetPath();
      file_signature_location.offset = 0x110;

      break;
    }

    case D2_GameVersion_kClassic1_14D:
    case D2_GameVersion_kLod1_14D: {
      file_signature_location.path = Mapi_GameExecutable_GetPath();
      file_signature_location.offset = 0x140;

      break;
    }

    default: {
      Mdc_Error_ExitOnConstantMappingError(
          __FILEW__,
          __LINE__,
          game_version
      );

      goto return_bad;
    }
  }

  return file_signature_location;

return_bad:
  return file_signature_location;
}

/**
 * External functions
 */

enum D2_GameVersion Mapi_GameVersion_GetFromFileSignature(
    enum D2_GameVersion guess_game_version
) {
  struct FileSignatureLocation file_signature_location;

  struct FileSignatureTableEntry file_signature_table_search_key;
  const struct FileSignatureTableEntry* file_signature_table_search_result;

  int is_load_signature_success;

  if (!HasFileSignatureCheck(guess_game_version)) {
    return guess_game_version;
  }

  file_signature_location = GetFileSignatureLocation(guess_game_version);
  is_load_signature_success = File_SignatureLocation_LoadSignature(
      &file_signature_location,
      file_signature_table_search_key.signature
  );

  if (!is_load_signature_success) {
    return -1;
  }

  file_signature_table_search_result = bsearch(
      &file_signature_table_search_key,
      kFileSignatureSortedTable,
      kFileSignatureSortedTableCount,
      sizeof(kFileSignatureSortedTable[0]),
      &FileSignatureTableEntry_CompareKeyAsVoid
  );

  return file_signature_table_search_result->game_version;
}
