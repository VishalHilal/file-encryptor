# File Encryptor 🔐

*A simple AES-256-CBC file encryption & decryption tool written in C++ using OpenSSL.*

---

## 🚀 Features

* Encrypt any file using **AES-256-CBC**
* Decrypt previously encrypted files
* Password-based key derivation (PBKDF2-HMAC-SHA256)
* Uses a random IV for strong security
* Clean CMake-based build system
* Cross-platform (Linux, macOS, Windows)

---

## 📁 Project Structure

```
file-encryptor/
│── CMakeLists.txt
│── include/
│     └── FileUtil.hpp
│── src/
│     ├── main.cpp
│     └── FileUtil.cpp
```

---

## 🛠️ Requirements

Before building the project, install OpenSSL development libraries:

### **Ubuntu / Debian**

```bash
sudo apt update
sudo apt install libssl-dev
```

### **Fedora / RHEL**

```bash
sudo dnf install openssl-devel
```

### **macOS**

```bash
brew install openssl
```

---

## 🔧 Build Instructions

### **1. Clone the project**

```bash
cd ~/cpp
git clone <your-repo-url> file-encryptor
cd file-encryptor
```

### **2. Create a build directory**

```bash
mkdir build
cd build
```

### **3. Generate build files with CMake**

```bash
cmake ..
```

### **4. Build the project**

```bash
make
```

### After success, you will have:

```
build/file-encryptor
```

---

## 📌 Usage

### **Encrypt a File**

```bash
./file-encryptor encrypt <input-file> <output-file>
```

#### Example:

```bash
./file-encryptor encrypt first.txt encrypted.bin
```

You will be prompted for:

```
Enter password:
```

---

### **Decrypt a File**

```bash
./file-encryptor decrypt <input-file> <output-file>
```

#### Example:

```bash
./file-encryptor decrypt encrypted.bin decrypted.txt
```

---

## 🧪 Example Workflow

### 1️⃣ Encrypt a file

```bash
./file-encryptor encrypt notes.txt notes.secure
Enter password: ****
Encrypted -> notes.secure
```

### 2️⃣ View encrypted file (garbage output is normal)

```bash
cat notes.secure
```

### 3️⃣ Decrypt

```bash
./file-encryptor decrypt notes.secure notes_decrypted.txt
Enter password: ****
Decrypted -> notes_decrypted.txt
```

---

## 🔐 How the Encryption Works

### ✔ PBKDF2-HMAC-SHA256

Your password is converted into a 256-bit key using PBKDF2 with:

* 10,000 iterations
* Salt stored inside file
* Strong protection against brute force

### ✔ AES-256-CBC

The tool uses:

* 32-byte key
* 16-byte IV (random per file)
* Authenticated result includes header + salt + IV

---

## ⚠️ Important Notes

* **If you enter the wrong password**, decryption **will fail**.
* If the encrypted file is modified/corrupted → decryption fails.
* Password is **not stored anywhere**.
* This tool does **not** provide file integrity (AES-GCM recommended for production).
---

