# SFML Project Template

This template helps you build and run SFML projects easily using Bash.

## Folder Structure

```
sfml-template/
├── include/        # SFML header files
├── lib/            # SFML libraries
├── src/            # Your .cpp files
├── header/         # Your custom .h files
├── asset/          # Textures, fonts, audio, etc.
├── bin/            # Compiled executable
├── buildsfml.sh    # Build and run script
├── buildsfml.bat   # Build script for Windows (optional)
├── .gitignore      # Git ignore file
└── README.md       # This file
```

## Requirements

* Bash (Git Bash, MSYS2, WSL, or Linux/macOS terminal)
* g++ compiler (GCC 11 or newer recommended)
* SFML 2.6.1 or newer
* SFML DLLs (on Windows) or shared libraries (.so/.dylib) in the same folder as executable

## How to build and run

1. Make the script executable (run once):

   ```bash
   chmod +x buildsfml.sh
   ```
2. Compile and run the project:

   ```bash
   ./buildsfml.sh
   ```
3. To run the executable again without recompiling:

   ```bash
   ./bin/game.exe
   ```

## Notes

* SFML DLLs or shared libraries must be in the same folder as `game.exe`.
* Empty folders (`header` or `asset`) do not cause any issues.
* This setup works reliably on any system with Bash + g++ + SFML installed.
* Users only need a compatible g++ compiler; they do not need to install SFML themselves since all necessary headers and libraries are included.
* GCC 11 or newer is recommended. Newer versions are generally compatible. Older versions may fail if your code uses newer C++ features.
