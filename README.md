# File Encryptor 🔐

A simple AES-256 file encryption & decryption utility written in modern C++ using OpenSSL.
Encrypt any file using a password and decrypt it later with the same password.

---

## 📁 Project Structure

Your real project layout:

```
file-encryptor/
│── CMakeLists.txt
│── src/
│     ├── main.cpp
│     ├── Crypto.cpp
│     ├── Crypto.hpp
│     ├── FileUtil.cpp
│     ├── FileUtil.hpp
```

---

## 🛠️ Requirements (Install These First)

Before building the project, install all required build tools and libraries.

### ✔️ Update package index

```bash
sudo apt update
```

### ✔️ Install C++ compiler, Make, and CMake

```bash
sudo apt install build-essential cmake
```

### ✔️ Install pkg-config (required by this project)

```bash
sudo apt install pkg-config
```

### ✔️ Install OpenSSL development library

```bash
sudo apt install libssl-dev
```

---

## 📚 Libraries Used in This Project

This project uses the following C++ and system libraries:

| Feature                     | Library                              |
| --------------------------- | ------------------------------------ |
| AES encryption & decryption | **OpenSSL (EVP, RAND)**              |
| PBKDF2 key derivation       | **OpenSSL**                          |
| Detect OpenSSL library      | **pkg-config**                       |
| C++ file I/O                | `<fstream>`                          |
| C++ utility                 | `<iostream>`, `<vector>`, `<string>` |
| Byte operations             | `<cstring>`, `<cstdint>`             |

Crypto.hpp / Crypto.cpp use:

* `openssl/evp.h`
* `openssl/rand.h`
* `openssl/sha.h`
* `openssl/err.h`

---

## ⚙️ Build Instructions

These steps match the **exact workflow you used**.

### 1️⃣ Navigate to the project directory

```bash
cd ~/cpp/file-encryptor
```

### 2️⃣ Create a `build` folder

```bash
mkdir build
cd build
```

### 3️⃣ Run CMake

```bash
cmake ..
```

### 4️⃣ Build the executable

```bash
make
```

After building, the executable appears here:

```
build/file-encryptor
```

---

## ▶️ Usage Guide

### 🔒 Encrypt a file

```
./file-encryptor encrypt <input-file> <output-file>
```

Example:

```bash
./file-encryptor encrypt first.txt encrypted.bin
Enter password: ****
```

### 🔓 Decrypt a file

```
./file-encryptor decrypt <input-file> <output-file>
```

Example:

```bash
./file-encryptor decrypt encrypted.bin result.txt
Enter password: ****
```

If password is wrong OR file is corrupted, you will see:

```
Decryption failed: possible wrong password or corrupted file
```

---

## 🧪 Sample Workflow

Encrypt:

```bash
./file-encryptor encrypt notes.txt secure.bin
```

Decrypt:

```bash
./file-encryptor decrypt secure.bin notes_dec.txt
```

---

## 🔐 How Encryption Works Internally

* Password → derived into a 256-bit key using **PBKDF2-HMAC-SHA256**
* Random 16-byte IV generated per file
* File encrypted with **AES-256-CBC**
* Output file contains:

  * Magic header (`FENC01`)
  * Salt
  * IV
  * Encrypted data

---

## ⚠️ Important Notes

* If you lose the password, encrypted data **cannot** be recovered.
* CBC mode does NOT provide authentication (AES-GCM is safer, optional upgrade).
* Encrypted output is *binary*, cannot be opened with normal editors.

---

## 📄 License

MIT License © 2025


