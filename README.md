# 🔒 Simple SHA-256 Integrity Checker DLL

This project is a minimal Windows DLL written in C++ that continuously checks the SHA‑256 hash of a target file (`game.exe` by default).  
If the file’s hash does not match the trusted value, the process is terminated immediately.

---

## 📂 Project Structure
- `dllmain.cpp` → DLL entry point (kept minimal)
- `sha-256.cpp` → Implements SHA‑256 hashing and monitoring loop
- `sha-256.h` → Function declarations and export

---

## 📑 How to Get SHA‑256 of a File
You need the trusted SHA‑256 hash of your target file (`game.exe`).  
Here are simple ways to compute it:

### 🔹 Using PowerShell (Windows built‑in)
Open PowerShell and run:
```powershell
Get-FileHash "C:\path\to\game.exe" -Algorithm SHA256

---

#### 🛠️ Setting the Trusted Hash
After computing the SHA‑256 hash of your target file (`game.exe`),  
open **sha-256.cpp** and locate the following lines near the top of the file:

```cpp
// sha-256.cpp

// Path to the file being monitored
std::wstring gamePath = L"game.exe";

// Replace this with your trusted SHA-256 hash
std::wstring trustedHash = L"07C34D79B89ADCD041B61F063AE6CCF7DC93D941ACC5480795D40DD985D7F3A9";
