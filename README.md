# Bleed

Bleed is a simple dynamic instrumentation framework for Android. It allows you to read/write memory and execute Lua scripts within a target process via a TCP connection.

## How to use

Find the main entry point in `AndroidManifest.xml`.

Open the corresponding `.smali` file and add this to the `onCreate` method:

```smali
const-string v0, "Bleed"
invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V
```

### 3. Build and Sign
Repack the APK:
```bash
apktool b workdir -o patched.apk
zipalign -v 4 patched.apk aligned.apk
apksigner sign --ks your_key.jks aligned.apk
```

### 4. Connect
Install and run the app. Then, forward the port and run the controller:

```bash
adb forward tcp:1628 tcp:1628
python bleed.py
```

## Lua API

Once connected, you can run these commands:

*   **`readMem(size, address)`**: Returns a string of bytes.
    *   `print(readMem(4, 0x12345678))`
*   **`writeMem(address, data)`**: Writes bytes to an address (handles `mprotect` automatically).
    *   `writeMem(0x12345678, "\x90\x90\x90\x90")`
*   **`readMaps()`**: Returns the contents of `/proc/self/maps`.
*   **`print(string)`**: Sends text back to your terminal.

## Building

**Requirements:**
*   Android NDK (r27d recommended)
*   CMake & Ninja

Edit `build_all.bat` to point to your NDK path, then run it:
```cmd
build_all.bat
```
The `.so` files will be generated in the `build/` directory.