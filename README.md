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
