 
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
*   **Network Output:**
    *   Custom `print` function redirects output to `127.0.0.1:1628`.
*   **Multi-Architecture Support:**
    *   Builds for `arm64-v8a` and `armeabi-v7a`.
## Usage

TODO


## Prerequisites & Setup

To build this project, you need:

1.  **CMake** (Version 3.21 or higher).
2.  **Ninja** build system.
3.  **Android NDK** (Tested with r27d).

## Building

A Windows batch script is provided to automate the build process.

1.  Open `build_all.bat` in a text editor.
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

Once injected, you can use the following functions within your Lua scripts:

### `readMem(size, address)`
Reads a specific number of bytes from a memory address.

*   **Parameters:**
    *   `size` (int): Number of bytes to read.
    *   `address` (number): Memory address to read from.
*   **Returns:** A string containing the raw bytes.

```lua
-- Example: Read 4 bytes from address 0x12345678
local data = readMem(4, 0x12345678)
```

### `writeMem(address, data)`
Writes raw bytes to a memory address. This function automatically calls `mprotect` to ensure the page is writable.

*   **Parameters:**
    *   `address` (number): Memory address to write to.
    *   `data` (string): Raw bytes to write.

```lua
Example: Write 2 bytes (0x90 0x90) to address 0x12345678
writeMem(0x12345678, "\x90\x90")
```

### `readMaps()`
Retrieves the content of the process memory maps.

*   **Returns:** A string containing the entire `/proc/self/maps` content.

```lua
local maps = readMaps()
print(maps)
```

### `print(message)`
Sends a string to the connected remote client (BleedGUI).

*   **Parameters:**
    *   `message` (string): The message to send.

```lua
print("Hook initialized successfully!")
```
