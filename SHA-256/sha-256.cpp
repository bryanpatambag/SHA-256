#include "sha-256.h"
#include <windows.h>
#include <wincrypt.h>
#include <thread>
#include <chrono>

// --- SHA256 checker function ---
std::wstring getFileSHA256(const std::wstring& filePath) {
    HANDLE hFile = CreateFileW(filePath.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (hFile == INVALID_HANDLE_VALUE) return L"";

    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    BYTE buffer[4096];
    DWORD bytesRead = 0;
    BYTE hash[32]; // SHA-256 = 32 bytes
    DWORD hashLen = sizeof(hash);

    if (!CryptAcquireContext(&hProv, nullptr, nullptr, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
        CloseHandle(hFile);
        return L"";
    }

    if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)) {
        CryptReleaseContext(hProv, 0);
        CloseHandle(hFile);
        return L"";
    }

    while (ReadFile(hFile, buffer, sizeof(buffer), &bytesRead, nullptr) && bytesRead > 0) {
        CryptHashData(hHash, buffer, bytesRead, 0);
    }

    std::wstring result;
    if (CryptGetHashParam(hHash, HP_HASHVAL, hash, &hashLen, 0)) {
        for (DWORD i = 0; i < hashLen; i++) {
            wchar_t hex[3];
            swprintf(hex, 3, L"%02x", hash[i]);
            result += hex;
        }
    }

    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);
    CloseHandle(hFile);
    return result;
}

// --- Loop process for SHA256 check ---
void sha256_process() {
    std::wstring gamePath = L"game.exe";
    std::wstring trustedHash = L"07C34D79B89ADCD041B61F063AE6CCF7DC93D941ACC5480795D40DD985D7F3A9";

    while (true) {
        std::wstring currentHash = getFileSHA256(gamePath);

        if (_wcsicmp(currentHash.c_str(), trustedHash.c_str()) != 0) {
            ExitProcess(0);
        }

        std::this_thread::sleep_for(std::chrono::seconds(1)); // check every 1 second
    }
}

// --- Hook function ---
void SHA256() {
    std::thread(sha256_process).detach();
}