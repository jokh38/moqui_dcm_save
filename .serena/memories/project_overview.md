# Project Memory: moqui_dcm_save
# Generated on project creation

## Project Overview
A C++ project

## Technical Stack
- **Language**: C++17
- **Build System**: CMAKE
- **Testing**: Catch2/Doctest
- **Code Formatting**: clang-format
- **Static Analysis**: clang-tidy
- **Compilation Cache**: sccache disabled
- **Build Generator**: Unix Makefiles
- **Git Hooks**: Pre-commit hooks installed and configured

## Project Structure
```
src/           - Main source code directory
include/       - Header files
tests/         - Test files using gtest
build/         - Build output directory
docs/          - Project documentation
git-hooks/     - Local CI/CD hooks
configs/       - Tool configuration files
.serena/       - Serena AI configuration and memories
```

## Development Workflow
1. **Configure Build**: `cmake -B build -G Unix Makefiles`
2. **Build Project**: `cmake --build build`
3. **Run Tests**: `ctest --test-dir build --output-on-failure`
4. **Format Code**: `clang-format -i src/**/*.cpp include/**/*.hpp`
5. **Static Analysis**: `clang-tidy src/**/*.cpp -- -I./include`
6. **Git Hooks**: Automatic on commit (formatting, build, testing)

## Quality Standards
- All code must pass clang-format formatting
- All code must pass clang-tidy static analysis
- All tests must pass before commits
- Build must succeed before commits
- Pre-commit hooks enforce quality standards
- Use `git commit --no-verify` only in emergencies

## AI Assistant Integration
This project is configured for Serena MCP integration with:
- Shell execution tools enabled for autonomous development
- File editing tools for automatic bug fixes and refactoring
- Web access for dependency research and C++ best practices
- Memory system for project-specific knowledge
- Integration with existing git hooks and testing frameworks

## Common Commands
- Configure build: `cmake -B build`
- Build project: `cmake --build build`
- Run tests: `ctest --test-dir build --output-on-failure`
- Format code: `clang-format -i src/**/*.cpp include/**/*.hpp`
- Static analysis: `clang-tidy src/**/*.cpp -- -I./include`
- Clean build: `rm -rf build && cmake -B build && cmake --build build`
- Pre-commit check: `pre-commit run --all-files`

## Build Types
- Debug: `cmake -B build -DCMAKE_BUILD_TYPE=Debug`
- Release: `cmake -B build -DCMAKE_BUILD_TYPE=Release`
- RelWithDebInfo: `cmake -B build -DCMAKE_BUILD_TYPE=RelWithDebInfo`
