# Serena Usage Guide for moqui_dcm_save

## Quick Start
1. Ensure Serena MCP is installed and enabled in Claude Code
2. Enable all tools (shell execution, editing, web access) for maximum value
3. Start with onboarding mode to let Serena analyze the C++ codebase
4. Use appropriate modes for different tasks

## Recommended Modes
- **Planning tasks**: `--mode planning --mode one-shot`
- **Code editing**: `--mode editing --mode interactive`
- **Development sessions**: `--mode planning --mode interactive`

## Capabilities
- **Build Management**: Serena can run CMake configuration and build commands
- **Test Execution**: Run ctest and fix test failures automatically
- **Code Quality**: Auto-fix clang-format and clang-tidy issues
- **C++ Refactoring**: Modern C++ refactoring and best practices application
- **Documentation**: Generate and update C++ documentation
- **Error Correction**: Self-correct based on compilation and test results

## Integration Notes
- Git hooks will validate Serena's changes (build, format, test)
- All changes are tracked through git for easy review
- Serena respects existing CMake and tool configuration files
- Memory system maintains C++ project context across sessions
- Works seamlessly with sccache for faster compilation

## C++ Specific Features
- **CMake Integration**: Serena can modify CMakeLists.txt files
- **Header Management**: Automatic include guard and pragma once handling
- **Modern C++**: Apply C++17 best practices
- **Template Handling**: Assist with template code generation and debugging
- **Build Optimization**: Suggest and implement build improvements

## Best Practices
- Start with clean git state when using Serena
- Review Serena's changes with `git diff` before committing
- Allow Serena to complete onboarding on first use
- Use read-only mode for code analysis only
- Keep backups of important header files
- Test builds after significant changes
