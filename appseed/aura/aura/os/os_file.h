#pragma once



CLASS_DECL_AURA HANDLE create_file(
const char *            lpFileName,
DWORD                   dwDesiredAccess,
DWORD                   dwShareMode,
LPSECURITY_ATTRIBUTES   lpSecurityAttributes,
DWORD                   dwCreationDisposition,
DWORD                   dwFlagsAndAttributes,
HANDLE                  hTemplateFile
);



