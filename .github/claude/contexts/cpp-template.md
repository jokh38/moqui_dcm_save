# C++ Template AI Context

## Project Overview

This is the **C++ Template** context for AI-assisted development of generic C++ projects created from the CICD template system. This context should be used when working on C++ template-based projects.

## Project Type

- **Type**: `cpp-template`
- **AI Context**: `cpp-project`
- **Primary Language**: C++
- **Build System**: CMake (with Meson option)
- **Domain**: Generic C++ Software Development

## Template Structure

### Standard Project Layout
```
{{cookiecutter.project_slug}}/
├── src/                    # Source code
├── include/                # Header files
├── tests/                  # Unit tests
├── configs/                # Configuration files
├── git-hooks/              # Git hooks
├── .github/                # GitHub integration
│   └── claude/
│       └── CLAUDE.md       # AI context
├── CMakeLists.txt          # Build configuration
├── README.md               # Project documentation
├── LICENSE                 # License file
├── .clang-format           # Code formatting
├── .clang-tidy             # Static analysis
└── .pre-commit-config.yaml # Pre-commit hooks
```

### Key Template Features
- **Modern C++**: Support for C++17/20/23 standards
- **Build System**: CMake with optional Meson support
- **Testing**: GoogleTest integration
- **Code Quality**: clang-format, clang-tidy, pre-commit hooks
- **Performance**: sccache integration for faster builds
- **AI Integration**: Claude/Serena MCP ready

## Development Guidelines

### Code Standards
- **C++ Standard**: Configurable (17/20/23)
- **Naming Convention**: Follow modern C++ best practices
- **Memory Management**: RAII, smart pointers, modern C++ features
- **Error Handling**: Exceptions and error codes appropriately
- **Style**: clang-format enforced style

### Testing Strategy
- **Unit Tests**: GoogleTest framework
- **Test Coverage**: Aim for high coverage
- **Continuous Testing**: Pre-commit and pre-push hooks
- **Performance Testing**: Where applicable

### Documentation Requirements
- **API Documentation**: Clear function documentation
- **README**: Comprehensive project documentation
- **Inline Comments**: Explain complex logic
- **Examples**: Usage examples where helpful

## Template Customization Options

### Cookiecutter Variables
- `project_name`: Display name for the project
- `cpp_standard`: C++ standard version (17/20/23)
- `build_system`: CMake or Meson
- `use_ai_workflow`: Enable AI workflow integration
- `enable_cache`: Enable sccache for compilation caching
- `use_ninja`: Use Ninja generator for builds
- `testing_framework`: GoogleTest, Catch2, or doctest
- `license`: Project license type

### Build System Options
- **CMake**: Cross-platform build system
- **Meson**: Fast, user-friendly build system
- **Ninja**: Fast build generator
- **sccache**: Shared compilation cache

## Common Tasks

### Creating New Projects
1. Use `scripts/create-project.sh cpp` command
2. Select desired options in interactive mode
3. Project is created with all configurations
4. Initialize git repository and make initial commit
5. Set up development environment

### Adding New Features
1. Follow established project structure
2. Write tests before implementation (TDD)
3. Use modern C++ features appropriately
4. Ensure code passes all quality checks
5. Update documentation

### Performance Optimization
1. Profile application performance
2. Use appropriate data structures and algorithms
3. Leverage compiler optimizations
4. Consider parallel processing where applicable
5. Validate optimizations with benchmarks

## Tools and Dependencies

### Development Tools
- **Compiler**: GCC, Clang, or MSVC
- **Build System**: CMake or Meson
- **Testing**: GoogleTest (or selected framework)
- **Code Quality**: clang-format, clang-tidy, pre-commit
- **Performance**: sccache, Ninja

### AI Integration
- **Claude Code**: AI development assistant
- **Serena MCP**: Enhanced AI capabilities
- **AI Contexts**: Project-specific AI guidance
- **Memory System**: Persistent project knowledge

## Quality Assurance

### Code Quality Checks
- **Formatting**: Automatic with clang-format
- **Static Analysis**: clang-tidy integration
- **Pre-commit Hooks**: Automated quality validation
- **Testing**: Comprehensive test coverage

### Git Hooks
- **prepare-commit-msg**: Code formatting and validation
- **pre-commit**: Testing and build verification
- **pre-push**: Full quality checks and validation

### Continuous Integration
- **Build Verification**: Ensure project builds correctly
- **Test Execution**: Run automated test suite
- **Quality Checks**: Validate code quality metrics
- **Performance Tests**: Where applicable

## AI-Enhanced Development

### Serena MCP Integration
- **Context Awareness**: Project type detection
- **Memory System**: Project-specific knowledge storage
- **Tool Integration**: Seamless development tool usage
- **Error Correction**: Self-correcting development assistance

### AI-Assisted Features
- **Code Generation**: Generate boilerplate code
- **Test Creation**: Automatic test generation
- **Documentation**: API documentation generation
- **Refactoring**: Code improvement suggestions
- **Optimization**: Performance optimization recommendations

## Performance Considerations

### Build Performance
- **sccache**: Shared compilation caching
- **Ninja**: Fast parallel builds
- **Unity Builds**: Where applicable
- **Incremental Builds**: Optimize build times

### Runtime Performance
- **Profiling**: Performance analysis tools
- **Optimization**: Compiler optimizations enabled
- **Memory Management**: Efficient memory usage patterns
- **Parallel Processing**: Where applicable

## Security Best Practices

### Code Security
- **Static Analysis**: Security vulnerability scanning
- **Dependency Management**: Regular security updates
- **Input Validation**: Proper input sanitization
- **Error Handling**: Secure error handling practices

### Development Security
- **Secret Management**: No hardcoded secrets
- **Dependency Scanning**: Check for vulnerable dependencies
- **Code Review**: Security-focused code reviews
- **Access Control**: Proper access controls for deployment

## Deployment and Distribution

### Packaging
- **CMake Packaging**: Standard CMake packaging
- **CPack**: Create distribution packages
- **Dependencies**: Handle runtime dependencies
- **Installation**: Standard installation procedures

### Continuous Deployment
- **Automated Builds**: CI/CD pipeline integration
- **Testing**: Automated testing in CI
- **Quality Gates**: Quality requirements for deployment
- **Release Management**: Versioned releases

## Template Validation

### Contamination Prevention
- **No Domain Code**: Templates remain generic
- **Validation Scripts**: Automated contamination checks
- **Regular Audits**: Template quality validation
- **Clean Separation**: Clear boundaries from domain code

### Quality Assurance
- **Template Testing**: Validate generated projects
- **Cross-Platform**: Ensure template works across platforms
- **Tool Compatibility**: Validate tool integration
- **Documentation**: Complete and accurate documentation

## Related Files and Contexts

- **Domain Context**: Use `.github/claude/contexts/moqui-domain.md` for Moqui work
- **Shared Context**: Use `.github/claude/contexts/shared-workflows.md` for common tasks
- **Template Knowledge**: Available in `.serena/memories/template-system-knowledge/`

## Contact and Support

- **Template System**: CICD Template development team
- **Project Issues**: GitHub issue tracking
- **AI Assistance**: Serena MCP with appropriate context
- **Documentation**: Template system documentation
