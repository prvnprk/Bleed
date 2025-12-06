 
# BLEED

[![Android-Bleed-Build-Windows](https://github.com/prvnprk/Bleed/actions/workflows/cmake-single-platform.yml/badge.svg)](https://github.com/prvnprk/Bleed/actions/workflows/cmake-single-platform.yml)

**Bleed** is a lightweight Android dynamic instrumentation library backed by Lua. It allows reverse engineers and developers to inject code, read/write memory, and inspect process memory maps dynamically using Lua scripts.

## Features

*   **Embedded Lua Engine:** Execute Lua scripts directly inside the target process.
*   **Memory Manipulation:**
    *   `readMem`: Read raw bytes from specific memory addresses.
    *   `writeMem`: Write raw bytes to memory.
*   **Process Inspection:**
    *   `readMaps`: Dump the current memory maps.

## Usage

Injecting Bleed into a target APK:

### 1. Decompile the APK
Use `apktool` to unpack the target application.
```bash
  apktool d target.apk -o output_folder
```

### 2. Copy the Shared Library
Copy the compiled `libBleed.so` file into the appropriate library folder within the decompiled project.

*   **For 64-bit devices:**
    Copy `arm64-v8a/libBleed.so` to `output_folder/lib/arm64-v8a/`.
*   **For 32-bit devices:**
    Copy `armeabi-v7a/libBleed.so` to `output_folder/lib/armeabi-v7a/`.

> **Note:** If the `lib` or architecture folders do not exist, create them.

### 3. Locate the Entry Point
Open `output_folder/AndroidManifest.xml` and look for the main entry point.
*   Check for the `<application>` tag's `android:name` attribute (this is the Application class).
*   If that doesn't exist, look for the `<activity>` tag containing the following intent filter:
    ```xml
    <action android:name="android.intent.action.MAIN" />
    <category android:name="android.intent.category.LAUNCHER" />
    ```

### 4. Inject Smali Loading Code
Navigate to the `smali` folder matching the package path of the entry point found in Step 3. Open the `.smali` file (e.g., `MainActivity.smali`).

Locate the `onCreate` method. Paste the following Smali code at the beginning of the method to load the library:

```smali
    const-string v0, "Bleed"
    invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V
```

### 5. Repack, Sign and Install
Rebuild the APK and sign it before installing.

```bash

apktool b output_folder -o output_patched.apk

zipalign -v 4 output_patched.apk output_aligned.apk

apksigner sign --ks your_keystore.jks output_aligned.apk

adb install output_patched.apk
```

### 6. Run and Port Forward
Launch the app on your phone, forward tcp port 1628

```bash
  adb forward tcp:1628 tcp:1628
```

### 7. Inject Scripts
Run the python scripts
```bash
  python bleed.py
```
example:
```bleed
Bleed> print(readMaps())
```




## Prerequisites
1.  **CMake** (Version 3.21 or higher).
2.  **Ninja** build system.
3.  **Android NDK** (Tested with r27d).

## Building

A Windows batch script is provided to automate the build process.

1.  Open `build_all.bat`.
2.  Update the `NDK_PATH` variable to point to your local Android NDK installation:
    ```bat
    set NDK_PATH=D:/path/to/your/android-ndk-r27d
    ```
3.  Run the script:
    ```cmd
    build_all.bat
    ```

This will generate the shared libraries in:
*   `build/arm64-v8a/libBleed.so`
*   `build/armeabi-v7a/libBleed.so`

## Lua API Reference

### `readMem(size, address)`
Reads a specific number of bytes from a memory address.

*   **Parameters:**
    *   `size` (int): Number of bytes to read.
    *   `address` (number): Memory address to read from.
*   **Returns:** A string containing the raw bytes.

```lua
Example: read 4 bytes from address 0x12345678
print(readMem(4, 0x12345678))
```

### `writeMem(address, data)`
Writes raw bytes to a memory address. This function automatically calls `mprotect` to ensure the page is writable.

*   **Parameters:**
    *   `address` (number): Memory address to write to.
    *   `data` (string): Raw bytes to write.

```lua
Example: write 2 bytes (0x90 0x90) to address 0x12345678
writeMem(0x12345678, "\x90\x90")
```

### `readMaps()`
Retrieves the content of the process memory maps.

*   **Returns:** A string containing the entire `/proc/self/maps` content.

```lua
print(readMaps())
```

### `print(message)`
Sends the input string to the connected remote client.

*   **Parameters:**
    *   `message` (string): The message to send.

```lua
print("Bleed hello")
```
