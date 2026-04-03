#ifndef PCH_H
#define PCH_H

// Common Windows headers
#include <windows.h>
#include <wincrypt.h>

// Standard C++ headers
#include <string>
#include <thread>
#include <chrono>

// Project headers (optional)
#include "sha-256.h"

// Function declarations
std::wstring getFileSHA256(const std::wstring& filePath);
void sha256_process();
void SHA256();

#endif // PCH_H
